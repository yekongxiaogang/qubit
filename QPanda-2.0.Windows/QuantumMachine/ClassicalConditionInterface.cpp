#include "ClassicalConditionInterface.h"
#include "Factory.h"


bool ClassicalCondition::eval(map<string, bool>
_Value_Map)
{
	return expr->eval(_Value_Map);
}

ClassicalCondition::ClassicalCondition(CBit *cbit)
{
	expr=
		Factory::
		CExprFactory::
		GetCExprByCBit(cbit);
}

ClassicalCondition::ClassicalCondition(CExpr *_Expr)
{
	expr = _Expr;
}

ClassicalCondition::ClassicalCondition
(const ClassicalCondition &cc)
{
	expr = cc.expr->deepcopy();
}

ClassicalCondition::~ClassicalCondition()
{
    delete expr;
}

ClassicalCondition operator+(
	ClassicalCondition leftcc,
	ClassicalCondition rightcc)
{
	return
		Factory::CExprFactory::GetCExprByOperation
		(
			leftcc.expr->deepcopy(),
			rightcc.expr->deepcopy(),
			PLUS);
}

ClassicalCondition operator-(
	ClassicalCondition leftcc,
	ClassicalCondition rightcc)
{
	return
		Factory::CExprFactory::GetCExprByOperation
		(
			leftcc.expr->deepcopy(),
			rightcc.expr->deepcopy(),
			MINUS);
}


ClassicalCondition operator&&(
	ClassicalCondition leftcc,
	ClassicalCondition rightcc)
{
	return
		Factory::CExprFactory::GetCExprByOperation
		(
			leftcc.expr->deepcopy(),
			rightcc.expr->deepcopy(),
			AND);
}

ClassicalCondition operator||(
	ClassicalCondition leftcc,
	ClassicalCondition rightcc)
{
	return
		Factory::CExprFactory::GetCExprByOperation
		(
			leftcc.expr->deepcopy(),
			rightcc.expr->deepcopy(),
			OR);
}

ClassicalCondition operator!(
	ClassicalCondition leftcc)
{
	return
		Factory::CExprFactory::GetCExprByOperation
		(
			leftcc.expr->deepcopy(),
			nullptr,
			NOT);
}