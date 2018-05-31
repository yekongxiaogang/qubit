#pragma once

#include "ClassicalConditionInterface.h"
#include "../QuantumMachine/QuantumMachineInterface.h"



class OriginCExpr : public CExpr
{
public:
	union content_u
	{
		CBit* cbit;
		int iOperatorSpecifier;
	};
private:
	CExpr* leftExpr = nullptr;
	CExpr* rightExpr = nullptr;
	int contentSpecifier;
	content_u content;
public:
	OriginCExpr(CBit* cbit);
	OriginCExpr(CExpr* leftExpr, CExpr* rightExpr, int);
	CExpr * getLeftExpr() const;
	CExpr *getRightExpr() const;
	string getName() const;
	CBit* getCBit() const;
	void setLeftExpr(CExpr*);
	void setRightExpr(CExpr*);
    bool eval(map<string, bool>) const;
	CExpr* deepcopy() const;
    bool checkValidity() const;
	~OriginCExpr();
};

