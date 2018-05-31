#ifndef _QCIRCUIT_PARSE_H
#define _QCIRCUIT_PARSE_H
#include <map>
#include <functional>
#include "../QuantumInstructionHandle/QuantumGates.h"
#include "../QuantumCircuit/QProgram.h"


using std::function;
using std::map;

class AbstractQNodeParse
{
public:
    virtual bool executeAction() = 0;
    virtual bool verify() = 0;
    virtual ~AbstractQNodeParse() {};
};

class QCirCuitParse :public AbstractQNodeParse
{
private:
    OriginQCircuit * m_pNode;
    QuantumGateParam * m_pParam;
    QuantumGates * m_pGates;
public:
    QCirCuitParse(OriginQCircuit * pNode, QuantumGateParam * pParam, QuantumGates* pGates);
    ~QCirCuitParse() {};
    bool executeAction();
    bool verify();
private:
    QCirCuitParse();
};

class QIfParse :public AbstractQNodeParse
{
private:
    QIfNode * m_pNode;
    QuantumGateParam * m_pParam;
    QuantumGates* m_pGates;
public:
    QIfParse(QIfNode * pNode, QuantumGateParam * pParam, QuantumGates* pGates);
    ~QIfParse() {};
    bool executeAction();
    bool verify();
private:
    QIfParse();
};
class QWhileNode;
class QWhileParse :public AbstractQNodeParse
{
private:
    QWhileNode * m_pNode;
    QuantumGateParam * m_pParam;
    QuantumGates* m_pGates;
public:
    QWhileParse(QWhileNode * pNode, QuantumGateParam * pParam, QuantumGates* pGates);
    ~QWhileParse() {};
    bool executeAction();
    bool verify();
private:
    QWhileParse();
};

class MeasureParse :public AbstractQNodeParse
{
private:
    QMeasureNode * m_pNode;
    QuantumGateParam * m_pParam;
    QuantumGates* m_pGates;
public:
    MeasureParse(QMeasureNode * pNode, QuantumGateParam * pParam, QuantumGates* pGates);
    ~MeasureParse() {};
    bool executeAction();
    bool verify();
private:
    MeasureParse();
};


class QProgParse :public AbstractQNodeParse
{
private:
    QProg * m_pNode;
    QuantumGateParam * m_pParam;
    QuantumGates* m_pGates;
public:
    QProgParse(QProg * pNode, QuantumGateParam * pParam, QuantumGates* pGates);
    ~QProgParse() {};
    bool executeAction();
    bool verify();
private:
    QProgParse();
};

class QGateParse :public AbstractQNodeParse
{
private:
    QNode * m_pNode;
    QuantumGates* m_pGates;
    bool m_isDagger;
    vector<Qubit *> m_controlQubitVector;
public:
    QGateParse(QNode * pNode, QuantumGates* pGates, bool isDagger, vector<Qubit *> & controlQubitVector);
    ~QGateParse() {};
    bool executeAction();
    bool verify();
    static void singleGateAngletoNum(double alpha, double beta, double gamma, double delta, QStat &matrix);
    static void DoubleGateAngletoNum(double alpha, double beta, double gamma, double delta, QStat &matrix);
private:
    QGateParse();

};




class QNodeAgency :public AbstractQNodeParse
{
public:
    QNodeAgency(OriginQCircuit * pNode, QuantumGateParam * pParam, QuantumGates* pGates);
    QNodeAgency(QIfNode * pNode, QuantumGateParam * pParam, QuantumGates* pGates);
    QNodeAgency(QWhileNode * pNode, QuantumGateParam * pParam, QuantumGates* pGates);
    QNodeAgency(QMeasureNode * pNode, QuantumGateParam * pParam, QuantumGates* pGates);
    QNodeAgency(QProg * pNode, QuantumGateParam * pParam, QuantumGates* pGates);
    QNodeAgency(OriginQGateNode * pNode, QuantumGates* pGates, bool isDagger, vector<Qubit *> & controlQubitVector);
    ~QNodeAgency();
    bool executeAction();
    bool verify();
private:
    QNodeAgency();
    AbstractQNodeParse * m_pQNodeParse;

};


typedef void(*QGATE_FUN)(QGate *,vector<Qubit * > &, QuantumGates*, bool, vector<Qubit *> &) ;
typedef map<int, QGATE_FUN> QGATE_FUN_MAP;
class QGateParseMap
{
 
    static QGATE_FUN_MAP m_QGateFunctionMap;
public:

    static void insertMap(int iOpNum,QGATE_FUN pFunction)
    {
        m_QGateFunctionMap.insert(pair<int, QGATE_FUN>(iOpNum, pFunction));
    }

    static QGATE_FUN getFunction(int iOpNum)
    {
       auto aiter = m_QGateFunctionMap.find(iOpNum);
       if (aiter == m_QGateFunctionMap.end() )
       {
           return nullptr;
       }

       return aiter->second;
    }
    

};





#endif // !_QCIRCUIT_PARSE_H