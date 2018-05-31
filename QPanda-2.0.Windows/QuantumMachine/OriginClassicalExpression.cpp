#include "OriginClassicalExpression.h"
#include "Factory.h"
#include <functional>


static map<int, function<bool(bool, bool)>> _Binary_Operation =
{
    {PLUS,[](bool a,bool b) {return a + b; }},
{MINUS,[](bool a,bool b) {return a - b; } },
{ AND,[](bool a,bool b) {return a && b; } },
{ OR,[](bool a,bool b) {return a || b; } },
};

static map<int, function<bool(bool)>> _Unary_Operation=
{
    {NOT,[](bool a) {return !a; }}
};

OriginCExpr::OriginCExpr(CBit* cbit)
{
	content.cbit = cbit;
	contentSpecifier = CBIT;
}

OriginCExpr::OriginCExpr(CExpr * _leftExpr, 
	CExpr * _rightExpr, int op)
{
	leftExpr = _leftExpr;
	rightExpr = _rightExpr;
	contentSpecifier = OPERATOR;
	content.iOperatorSpecifier = op;
}

CExpr * OriginCExpr::getLeftExpr() const
{
	return leftExpr;
}

CExpr * OriginCExpr::getRightExpr() const
{
	return rightExpr;
}

string OriginCExpr::getName() const
{
	switch (contentSpecifier)
	{
	case CBIT:
		return this->content.cbit->getName();
	case OPERATOR:
		switch (content.iOperatorSpecifier)
		{
		case AND:
			return "&&";
		case OR:
			return "||";
		case PLUS:
			return "+";
		case MINUS:
			return "-";
		case NOT:
			return "!";
		default:
			throw(exception());
		}
	}
    return NULL;
}

CBit * OriginCExpr::getCBit() const
{
	switch (contentSpecifier)
	{
	case CBIT:
		return content.cbit;
	case OPERATOR:
		return nullptr;
	default:
		throw(exception());
	}
}

void OriginCExpr::setLeftExpr(CExpr *leftexpr)
{
	leftExpr = leftexpr;
}

void OriginCExpr::setRightExpr(CExpr* rightexpr)
{
	rightExpr = rightexpr;
}

bool OriginCExpr::eval(map<string, bool> _Val_Map)
const
{
    if (contentSpecifier == CBIT)
    {
        auto iter = _Val_Map.find(this->content.cbit->getName());
        if (iter == _Val_Map.end())
        {
            throw(exception());
        }
        return iter->second;
    }
    else if (this->contentSpecifier==OPERATOR)
    {
        if (this->contentSpecifier <= OR)
        {
            return _Binary_Operation[OPERATOR](this->leftExpr->eval(_Val_Map), this->rightExpr->eval(_Val_Map));
        }
        else if (this->contentSpecifier <= NOT)
        {
            return _Unary_Operation[OPERATOR](this->leftExpr->eval(_Val_Map));
        }
        else
        {
            throw(exception());
        }
    }
    else
    {
        throw(exception());
    }
}

CExpr * OriginCExpr::deepcopy() const
{
	if (contentSpecifier == CBIT)
	{
		return
			Factory::CExprFactory
			::GetCExprByCBit(this->content.cbit);
	}
	if (contentSpecifier == OPERATOR)
	{
		return
			Factory::CExprFactory::
			GetCExprByOperation(
				this->leftExpr->deepcopy(),
				this->rightExpr->deepcopy(),
				this->content.iOperatorSpecifier
			);
	}
	else
	{
		throw(exception());
	}
}

bool OriginCExpr::checkValidity() const
{
    if (contentSpecifier == OPERATOR)
    {
        bool leftValidity, rightValidity;
        if (leftExpr == nullptr)
        {
            leftValidity = true;
        }
        else
        {
            leftValidity = leftExpr->checkValidity();
        }
        if (rightExpr == nullptr)
        {
            rightValidity = true;
        }
        else
        {
            rightValidity = rightExpr->checkValidity();
        }
        return leftValidity && rightValidity;
    }
    else if (contentSpecifier == CBIT)
    {
        return content.cbit->getOccupancy();
    }
    else
    {
        throw exception();
    }

}

OriginCExpr::~OriginCExpr()
{
	delete leftExpr;
	delete rightExpr;
}

REGISTER_CEXPR(OriginCExpr)
