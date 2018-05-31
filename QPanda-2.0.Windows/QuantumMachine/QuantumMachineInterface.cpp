#include "QuantumMachineInterface.h"

int QubitAddr::getX() const
{
	return x;
}

int QubitAddr::getY() const
{
	return y;
}

void QubitAddr::setX(int x)
{
	x = x;
}

void QubitAddr::setY(int y)
{
	y = y;
}

QubitAddr::QubitAddr(int x, int y)
	:x(
        
        x), y(y)
{
}
