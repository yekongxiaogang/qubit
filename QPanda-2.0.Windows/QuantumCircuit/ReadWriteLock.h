#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

class SharedMutex
{
private:
    mutex m_mutex;
    condition_variable m_cond;

    bool m_is_w = false;

    size_t m_read_c = 0;

    bool read_cond() const
    {
        return false == m_is_w;
    }
  
    bool write_cond() const
    {
        return false == m_is_w && 0 == m_read_c;
    }

public:
    void read()
    {
        unique_lock<mutex> lck(m_mutex);
  
        m_cond.wait(lck, bind(&SharedMutex::read_cond, this));
        m_read_c++;
    }

    void unread()
    {
        unique_lock<mutex> lck(m_mutex);
        m_read_c--;
        m_cond.notify_all();
    }

    void write()
    {
        unique_lock<mutex> lck(m_mutex);

        m_cond.wait(lck, bind([](const bool *is_w, const size_t *read_c) -> bool
        {
            return false == *is_w && 0 == *read_c;
        }, &m_is_w, &m_read_c));
        m_is_w = true;
    }

    void unwrite()
    {
        unique_lock<mutex> lck(m_mutex);
        m_is_w = false;
        m_cond.notify_all();
    }
};

class ReadLock
{
private:
    SharedMutex * m_sm;
public:
    ReadLock(SharedMutex &sm)
    {
        m_sm = &sm;
        m_sm->read();
    }
    ~ReadLock()
    {
        m_sm->unread();
    }
};

class WriteLock
{
private:
    SharedMutex * m_sm;
public:
    WriteLock(SharedMutex &sm)
    {
        m_sm = &sm;
        m_sm->write();
    }
    ~WriteLock()
    {
        m_sm->unwrite();
    }
};
