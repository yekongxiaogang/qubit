#include "OriginQuantumMachine.h"

/*
Factory::PhysicalQubitFactory::constructor_t
_Constructor = OriginPhysicalQubit_Constructor;
*/

OriginPhysicalQubit::OriginPhysicalQubit()
{
	bIsOccupied = false;
}



bool OriginPhysicalQubit::getOccupancy() const
{
	return bIsOccupied;
}

void OriginPhysicalQubit::setOccupancy(bool bStat)
{
	bIsOccupied = bStat;
}

REGISTER_PHYSICAL_QUBIT(OriginPhysicalQubit)

