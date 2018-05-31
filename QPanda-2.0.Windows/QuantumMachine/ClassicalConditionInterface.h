/*

Declaration and definition of the interface virtual class 
of the classical condition.

Author: Agony
CreateDate: 20180516

*/

#ifndef CLASSICAL_CONDITION_INTERFACE_H
#define CLASSICAL_CONDITION_INTERFACE_H

#include <string>
#include "QuantumMachineInterface.h"

using namespace std;

const enum ContentSpecifier
{
	CBIT,
	OPERATOR
};

const enum OperatorSpecifier
{
	PLUS,
	MINUS,
	AND,
	OR,
	NOT,
};

class CExpr
{
	// classical expression interface	
public:
    
	virtual CExpr* getLeftExpr() const = 0;
	virtual CExpr* getRightExpr() const = 0;
	virtual void setLeftExpr(CExpr*) = 0;
	virtual void setRightExpr(CExpr*) = 0;
	virtual string getName() const = 0;
	virtual CBit* getCBit() const = 0;
    virtual bool checkValidity() const = 0;
	virtual ~CExpr() {}
    virtual bool eval(map<string , bool>) const = 0;
	virtual CExpr* deepcopy() const = 0;
};

class ClassicalCondition
{
	CExpr* expr;
public:
	inline CExpr * getExprPtr() const { return expr; }
	bool eval(map<string, bool>);
    bool checkValidity() const;
	ClassicalCondition(CBit*);
	ClassicalCondition(CExpr*);
	ClassicalCondition(const ClassicalCondition&);
	friend ClassicalCondition operator+(ClassicalCondition, ClassicalCondition);
	friend ClassicalCondition operator-(ClassicalCondition, ClassicalCondition);
	friend ClassicalCondition operator&&(ClassicalCondition, ClassicalCondition);
	friend ClassicalCondition operator||(ClassicalCondition, ClassicalCondition);
	friend ClassicalCondition operator!(ClassicalCondition);
    ~ClassicalCondition();
};

#endif