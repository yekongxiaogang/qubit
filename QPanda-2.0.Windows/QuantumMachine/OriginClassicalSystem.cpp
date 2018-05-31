#include "OriginQuantumMachine.h"

#include <sstream>
using namespace std;

OriginCBit::OriginCBit(string name)
	:name(name)
{
	bOccupancy = false;
}

REGISTER_CBIT_NAME_(OriginCBit)

template<typename _Ty>
static string obj2str(_Ty& obj)
{
	stringstream ss;
	ss << obj;
	return ss.str();
}

OriginCMem::OriginCMem(size_t maxMem)
{	
	for (auto i = 0U; i < maxMem; ++i)
	{		
		auto _New_CBit =
			Factory::CBitFactory::CreateCBitFromName("c"+obj2str(i));
		vecBit.push_back(_New_CBit);
	}
}

IMPLEMENTATION CBit * OriginCMem::Allocate_CBit()
{
	for (auto iter = vecBit.begin(); iter!=vecBit.end(); ++iter)
	{
		if (!(*iter)->getOccupancy())
		{
			(*iter)->setOccupancy(true);
			return *iter;
		}
	}
	return nullptr;
}

IMPLEMENTATION size_t OriginCMem::getMaxMem() const
{
	return vecBit.size();
}

IMPLEMENTATION size_t OriginCMem::getIdleMem() const
{
	size_t idlenum = 0;
	for (auto iter = vecBit.begin(); iter != vecBit.end(); ++iter)
	{
		if (!(*iter)->getOccupancy())
		{
			idlenum++;
		}
	}
	return idlenum;
}

IMPLEMENTATION void OriginCMem::Free_CBit(CBit *cbit)
{
	for (auto iter = vecBit.begin(); iter != vecBit.end(); ++iter)
	{
		if ((*iter)==cbit)
		{
			if (!(*iter)->getOccupancy())
			{
				// if duplicate free
				throw(exception());
			}
			else
			{
				((*iter)->setOccupancy(false));
                return;
			}
		}
	}
	// if not any matched
	throw(exception());
}

IMPLEMENTATION void OriginCMem::clearAll()
{
	for (auto iter = vecBit.begin();
		iter != vecBit.end();
		++iter
		)
	{
		delete (*iter);
		*iter = nullptr;
	}
}
OriginCMem::~OriginCMem()
{
    for_each(vecBit.begin(), vecBit.end(), [](CBit* _s) {delete _s; });
}
REGISTER_CMEM_SIZE_(OriginCMem)

