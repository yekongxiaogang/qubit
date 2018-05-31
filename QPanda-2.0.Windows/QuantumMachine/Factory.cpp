#include "Factory.h"
#include "OriginQuantumMachine.h"


/* 1. static variable initialization start */

#if true
Factory::QuantumMachineFactory::constructor_map_t
Factory::QuantumMachineFactory::
_Quantum_Machine_Constructor=
{
	// empty
	// constructor map of quantum machine
	// realize the Reflection
};

Factory::PhysicalQubitFactory::constructor_stack_t
Factory::PhysicalQubitFactory::
_Physical_Qubit_Constructor;

Factory::QubitFactory::constructor_stack_t
Factory::QubitFactory::
_Qubit_Constructor;

Factory::QubitPoolFactory::size_constructor_stack_t
Factory::QubitPoolFactory::_Qubit_Pool_Constructor;

Factory::CBitFactory::name_constructor_stack_t
Factory::CBitFactory::
_CBit_Constructor;

Factory::CMemFactory::size_constructor_stack_t
Factory::CMemFactory::
_CMem_Constructor;

Factory::QResultFactory::constructor_stack_t
Factory::QResultFactory::
_QResult_Constructor;

Factory::CExprFactory::cbit_constructor_stack_t
Factory::CExprFactory::_CExpr_CBit_Constructor;

Factory::CExprFactory::operator_constructor_stack_t
Factory::CExprFactory::_CExpr_Operator_Constructor;

#endif

/* 1. static variable initialization end */

/* 2. Quantum Machine Status Factory */

QMachineStatus * Factory::QMachineStatusFactory::GetQMachineStatus()
{
	return new OriginQMachineStatus();
}

/* 2. Quantum Machine Status Factory End*/

/* 3. Quantum Machine Factory*/

/* Factory Helper class */
FactoryHelper::QuantumMachineFactoryHelper::
QuantumMachineFactoryHelper(
	string _Classname,
	constructor_t _Constructor
)
{
	// create a static variable of the helper class
	// can execute the constructor code
	
	// Here we insert the classname and constructor pair
	// into the map of _Quantum_Machine_Constructor
	Factory::QuantumMachineFactory::
	_Quantum_Machine_Constructor.insert(
		pair<string, constructor_t>(_Classname, _Constructor)
	);
}

/* Factory Method */
QuantumMachine * Factory::QuantumMachineFactory::
	CreateByName(string _Name)
{
	// create a Quantum Machine by its name string
	return Factory::QuantumMachineFactory::
		_Quantum_Machine_Constructor[_Name]();
}

/* 3. Quantum Machine Factory End*/

/* 4. Physical Qubit Factory*/

/* Factory Get Instance */
PhysicalQubit * Factory::PhysicalQubitFactory::GetInstance()
{
	// I think the last Constructor that user push
	// to the top of the stack is the user defined
	// class. So only Get the top is ok
	return _Physical_Qubit_Constructor.top()();
}

/* Factory Helper Class */
FactoryHelper::PhysicalQubitFactoryHelper::PhysicalQubitFactoryHelper(constructor_t _Constructor)
{
	// Only push the Constructor to the top
	Factory::PhysicalQubitFactory::_Physical_Qubit_Constructor.push(_Constructor);
}

/* 4. Physical Qubit Factory End */

/* 5. Qubit Factory */

/* Factory Helper Class */
FactoryHelper::QubitFactoryHelper::QubitFactoryHelper(constructor_t _Constructor)
{
	// Only push the Constructor to the top
	Factory::QubitFactory::_Qubit_Constructor.push(_Constructor);
}

/* Factory Get Instance */
Qubit * Factory::QubitFactory::GetInstance(PhysicalQubit *_physQ)
{
	// I think the last Constructor that user push
	// to the top of the stack is the user defined
	// class. So only Get the top is ok
	return _Qubit_Constructor.top()(_physQ);
}

/* 6. Qubit Pool Factory */

/* Factory Get Instance */
QubitPool * Factory::QubitPoolFactory::GetPoolWithoutTopology(size_t size)
{
	// I think the last Constructor that user push
	// to the top of the stack is the user defined
	// class. So only Get the top is ok
	return _Qubit_Pool_Constructor.top()(size);
}

/* Factory Helper Class */
FactoryHelper::QubitPoolFactoryHelper::QubitPoolFactoryHelper(
	size_constructor_t constructor)
{
	// Only push the Constructor to the top
	Factory::QubitPoolFactory::_Qubit_Pool_Constructor
		.push(constructor);
}

/* 6. Qubit Pool Factory End*/

/* 7. CBit Factory */

CBit * Factory::CBitFactory::CreateCBitFromName(string name)
{
	return _CBit_Constructor.top()(name);
}

FactoryHelper::CBitFactoryHelper::CBitFactoryHelper(name_constructor_t _Constructor)
{
	Factory::CBitFactory::_CBit_Constructor.push(_Constructor);
}

/* 7. CBit Factory End*/

/* 8. CMem Factory*/

CMem * Factory::CMemFactory::GetInstanceFromSize(size_t _Size)
{
	return _CMem_Constructor.top()(_Size);
}

FactoryHelper::CMemFactoryHelper::CMemFactoryHelper(size_constructor_t _Constructor)
{
	Factory::CMemFactory::_CMem_Constructor.push(_Constructor);
}

/* 8. CMem Factory End*/

/* 10. QResult Factory */

QResult * Factory::QResultFactory::GetEmptyQResult()
{
	return _QResult_Constructor.top()();
}

FactoryHelper::QResultFactoryHelper::QResultFactoryHelper(constructor_t _Constructor)
{
	Factory::QResultFactory::_QResult_Constructor.push(_Constructor);
}

/* 10. QResult Factory End */

/* 11. CExpr Factory */

CExpr * Factory::CExprFactory::GetCExprByCBit(CBit *bit)
{
	return 
	_CExpr_CBit_Constructor.top()(bit);
}

CExpr * Factory::CExprFactory::GetCExprByOperation(
	CExpr *leftexpr, 
	CExpr *rightexpr, 
	int op)
{
	return
	_CExpr_Operator_Constructor.top()
		(leftexpr, rightexpr, op);
}

FactoryHelper::CExprFactoryHelper::CExprFactoryHelper(
	cbit_constructor_t _Constructor
)
{
	Factory::CExprFactory::_CExpr_CBit_Constructor
		.push(_Constructor);
}

FactoryHelper::CExprFactoryHelper::CExprFactoryHelper(
	operator_constructor_t _Constructor
)
{
	Factory::CExprFactory::_CExpr_Operator_Constructor
		.push(_Constructor);
}




