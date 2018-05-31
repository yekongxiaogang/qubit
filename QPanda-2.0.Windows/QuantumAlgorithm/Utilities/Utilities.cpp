#include "Utilities.h"

QProg& Reset_Qubit(QuantumMachine* qm,Qubit* q, bool reset_val)
{
    auto &prog = createQProg();
    CBit* c = qm->Allocate_CBit();
    prog << Measure(q, c);
    ClassicalCondition s(c);
    auto &tempProg = createQProg();
    tempProg << RX(q, PI / 2);
    prog << createIfProg(&s, &tempProg);
    qm->Free_CBit(c);
    return prog;
}

QProg & Reset_All(QuantumMachine *qm, vector<Qubit*> qubit_vector,bool reset_val)
{
    auto &m = createQProg();
    for (auto iter = qubit_vector.begin(); iter != qubit_vector.end(); ++iter)
    {
        m << Reset_Qubit(qm, (*iter), reset_val);
    }

}
