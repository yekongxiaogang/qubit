#include "OriginQuantumMachine.h"
#include <algorithm>

OriginQubitPool::OriginQubitPool(size_t maxQubit)
{
	for (auto i = 0U; i < maxQubit; ++i)
	{
		auto _New_Physical_Qubit =
			Factory::PhysicalQubitFactory::GetInstance();
		vecQubit.push_back(_New_Physical_Qubit);
        _New_Physical_Qubit->setQubitAddr(i);
	}
}

IMPLEMENTATION void OriginQubitPool::clearAll()
{
	for (auto iter = vecQubit.begin(); iter != vecQubit.end();)
	{
		delete *iter;
		iter = vecQubit.erase(iter);
	}
}

IMPLEMENTATION size_t OriginQubitPool::getMaxQubit() const
{
	return vecQubit.size();
}

IMPLEMENTATION size_t OriginQubitPool::getIdleQubit() const
{
	size_t retIdle = 0;
	for (auto iter = vecQubit.begin(); iter != vecQubit.end(); ++iter)
	{
		if (!(*iter)->getOccupancy())
		{
			retIdle++;
		}
	}
	return retIdle;
}

IMPLEMENTATION Qubit * OriginQubitPool::Allocate_Qubit()
{
	for (auto iter = vecQubit.begin(); iter != vecQubit.end(); ++iter)
	{
		if (!(*iter)->getOccupancy())
		{
            (*iter)->setOccupancy(true);
			return Factory::QubitFactory::GetInstance(*iter);
            
		}
	}
	return nullptr;
}

IMPLEMENTATION void OriginQubitPool::Free_Qubit(Qubit* _Qubit)
{
	auto ptPhysQ = _Qubit->getPhysicalQubitPtr();
	auto iter = find(vecQubit.begin(), vecQubit.end(), ptPhysQ);
	if (iter == vecQubit.end())
	{
		throw(exception());
	}
	else
	{
		(*iter)->setOccupancy(false);
	}
}

IMPLEMENTATION size_t OriginQubitPool::getPhysicalQubitAddr(Qubit *qubit)
{
	for (auto iter = vecQubit.begin(); iter != vecQubit.end(); ++iter)
	{
		auto physAddr = qubit->getPhysicalQubitPtr();
		if (*iter == physAddr)
		{
			//_ASSERT(false);

            return (*iter)->getQubitAddr();
		}
	}
    throw exception();
 }
OriginQubitPool::~OriginQubitPool()
{
    for_each(vecQubit.begin(), vecQubit.end(), [](PhysicalQubit* _s) {delete _s; });
}
REGISTER_QUBIT_POOL_SIZE_(OriginQubitPool)



