#include "OriginQuantumMachine.h"

OriginQubit::OriginQubit(PhysicalQubit *_Physical_Qubit)
{
	ptPhysicalQubit = _Physical_Qubit;
}

REGISTER_QUBIT(OriginQubit)