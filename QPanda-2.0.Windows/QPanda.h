#ifndef _QPANDA_H
#define _QPANDA_H
#include"QuantumCircuit/QGate.h"
#include"QuantumCircuit/QException.h"
#include"QuantumCircuit/QProgram.h"
#include "QuantumMachine/OriginQuantumMachine.h"

extern QNodeVector _G_QNodeVector;

extern QProg & createQProg();
extern QWhileNode &createWhileProg(
    ClassicalCondition *,
    QNode * trueNode);

extern QIfNode &createIfProg(
    ClassicalCondition *,
    QNode *trueNode);

extern QIfNode &createIfProg(
    ClassicalCondition *,
    QNode *trueNode,
    QNode *falseNode);

extern OriginQCircuit & createQCircuit();


extern QMeasureNode& Measure(Qubit * targetQuBit, CBit * targetCbit);
extern OriginQGateNode & RX(Qubit* qbit);
extern OriginQGateNode & RX(Qubit*, double angle);
extern OriginQGateNode & RY(Qubit* qbit);
extern OriginQGateNode & RY(Qubit*, double angle);
extern OriginQGateNode & RZ(Qubit* qbit);
extern OriginQGateNode & RZ(Qubit*, double angle);
extern OriginQGateNode & S(Qubit* qbit);
extern OriginQGateNode & H(Qubit* qbit);
extern OriginQGateNode & CNOT(Qubit* targetQBit, Qubit* controlQBit);
extern OriginQGateNode & CZ(Qubit* targetQBit, Qubit* controlQBit);
extern OriginQGateNode & QSingle(double alpha, double beta, double gamma, double delta, Qubit *);
extern OriginQGateNode & QDouble(double alpha, double beta, double gamma, double delta, Qubit *, Qubit *);

#endif // !_QPANDA_H

