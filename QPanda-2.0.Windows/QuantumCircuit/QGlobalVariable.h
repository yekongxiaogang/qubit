#ifndef _QGlobalVariable_H_
#define _QGlobalVariable_H_
enum NodeType
{
    NODE_UNDEFINED = -1,
    GATE_NODE,
    CIRCUIT_NODE,
    PROG_NODE,
    MEASURE_GATE,
    WHILE_START_NODE,
    QIF_START_NODE
};

enum GateType
{
    GATE_UNDEFINED = -1,
    H_GATE,
    RX_GATE,
    RY_GATE,
    RZ_GATE,
    S_GATE,
    CNOT_GATE,
    CZ_GATE,


};

enum Operatortype
{
    OP_AND = 1,
    OP_OR,
    OP_NOT,
    OP_ADD,
    OP_MINUS,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_MODE,
    OP_EQUAL,
    OP_LESS,
    OP_MORE,
    OP_NO_MORE,
    OP_NO_LESS,
};
enum OperatorType
{
    TYPE_OPERATOR_NODE,
    TYPE_CBIT_NODE,
    TYPE_CINT_NODE,
    /*TYPE_CINT8_NODE,
    TYPE_CINT16_NODE,
    TYPE_CVEC_NODE,*/
};
//const map<int, string> Operator_String_Map
//{
//    { OP_AND,"&&"},
//    { OP_OR,"||" },
//    { OP_NOT,"!" },
//    { OP_ADD,"+" },
//    { OP_MINUS,"-" },
//    { OP_MULTIPLY,"*" },
//    { OP_DIVIDE,"/" },
//    { OP_MODE,"%" },
//    { OP_EQUAL,"==" },
//    { OP_LESS,"<" },
//    { OP_MORE,">" },
//    { OP_NO_MORE,"<=" },
//    { OP_NO_LESS,">=" }
//};

constexpr double SQRT2 = 1.4142135623730950488016887242097;
#endif
