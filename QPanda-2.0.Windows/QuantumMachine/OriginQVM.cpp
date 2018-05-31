#include "OriginQuantumMachine.h"
#include "Factory.h"

#include "../QuantumInstructionHandle/X86QuantumGates.h"

REGISTER_QUANTUM_MACHINE(OriginQVM)

OriginQVM::OriginQVM()
{
	return;
}

void OriginQVM::init()
{
	_Qubit_Pool = 
		Factory::
		QubitPoolFactory::
		GetPoolWithoutTopology(_Config.maxQubit);
	_CMem = 
		Factory::
		CMemFactory::
		GetInstanceFromSize(_Config.maxCMem);
    QProg & temp = createQProg();
    _QProgram = temp.getPosition();
	_QResult =
		Factory::
		QResultFactory::
		GetEmptyQResult();
	_QMachineStatus =
		Factory::
		QMachineStatusFactory::
		GetQMachineStatus();
    _pGates = new X86QuantumGates();
}

Qubit * OriginQVM::Allocate_Qubit()
{
	if (_Qubit_Pool == nullptr)
	{
		// check if the pointer is nullptr
		// Before init
		// After finalize
		throw(exception());
	}
	else
	{
		return _Qubit_Pool->Allocate_Qubit();
	}
		
}

CBit * OriginQVM::Allocate_CBit()
{
	if (_CMem == nullptr)
	{
		// check if the pointer is nullptr
		// Before init
		// After finalize
		throw(exception());
	}
	else
	{
		return _CMem->Allocate_CBit();
	}
}

void OriginQVM::Free_Qubit(Qubit *qubit)
{
    this->_Qubit_Pool->Free_Qubit(qubit);
}

void OriginQVM::Free_CBit(CBit *cbit)
{
    this->_CMem->Free_CBit(cbit);
}

void OriginQVM::load(QProg &loadProgram)
{
    QNodeAgency temp(&loadProgram, nullptr, nullptr);
    if (!temp.verify())
    {
        throw exception();
    }
    _QProgram = loadProgram.getPosition();
}

void OriginQVM::append(QProg & prog)
{
    QNodeAgency tempAgency(&prog, nullptr, nullptr);
    if (!tempAgency.verify())
    {
        throw exception();
    }
    auto aiter = _G_QNodeVector.getNode(_QProgram);
    QProg * temp = dynamic_cast<QProg *>(*aiter);
    temp->operator<<(prog);
}

void OriginQVM::run()
{
    if (_QProgram < 0)
    {
        return;
    }
    
    auto aiter =_G_QNodeVector.getNode(_QProgram);
    QProg * pNode = (QProg *)*aiter;
    _pParam = new QuantumGateParam();
    _pParam->mQuantumBitNumber = _Qubit_Pool->getMaxQubit() - _Qubit_Pool->getIdleQubit();
    _pGates->initState(_pParam);
    QNodeAgency temp(pNode, _pParam, _pGates);
    if (temp.executeAction())
    {
        for (auto aiter : _pParam->mReturnValue)
        {
            _QResult->append(aiter);
        }
    }
    delete _pParam;
    _pParam = nullptr;
    return ;

}

QMachineStatus * OriginQVM::getStatus() const
{
	return _QMachineStatus;
}

QResult * OriginQVM::getResult()
{
	return _QResult;
}

void OriginQVM::finalize()
{
	delete _Qubit_Pool;
	delete _CMem;
	delete _QResult;
	delete _QMachineStatus;
    delete _pGates;
}


