/*

 Declaration of quantum machine (implement the interface)

 Author: Agony
 CreateDate: 20180516

*/
#ifndef ORIGIN_QUANTUM_MACHINE_H
#define ORIGIN_QUANTUM_MACHINE_H
#include "QuantumMachineInterface.h"
#include "../QuantumInstructionHandle/QCircuitParse.h"
#include "Factory.h"
//#include "../QuantumInstructionHandle/QCircuitParse.h"
//#define implements : public
#define UNIQUE // To mark the function is not existed in interface
#define IMPLEMENTATION // To mark it is an implementation
#define CONSTRUCTOR

class OriginPhysicalQubit : public PhysicalQubit
{
	// implementation of the PhysicalQubit
private:
	size_t addr;
	bool bIsOccupied;
	//vector<PhysicalQubit*> adjacentQubit;
public:
	CONSTRUCTOR OriginPhysicalQubit(); 
	IMPLEMENTATION inline size_t getQubitAddr() { return addr; }
	IMPLEMENTATION inline void setQubitAddr(size_t addr) { this->addr = addr; }
	//IMPLEMENTATION void setAdjacentQubit(const vector<PhysicalQubit*>&);
	//IMPLEMENTATION vector<PhysicalQubit*> getAdjacentQubit() const;
	IMPLEMENTATION bool getOccupancy() const;
	IMPLEMENTATION void setOccupancy(bool);
};

class OriginQubit : public Qubit
{
private:
	PhysicalQubit * ptPhysicalQubit;
public:

	CONSTRUCTOR OriginQubit(PhysicalQubit*);

	inline PhysicalQubit* getPhysicalQubitPtr()	const
	{
		return ptPhysicalQubit;
	}
};

class OriginQubitPool : public QubitPool
{
	// implementation of the QubitPool
private:
	vector<PhysicalQubit*> vecQubit;

public:

	CONSTRUCTOR OriginQubitPool(size_t maxQubit);

	IMPLEMENTATION void clearAll();
	IMPLEMENTATION size_t getMaxQubit() const;
	IMPLEMENTATION size_t getIdleQubit() const;

	IMPLEMENTATION Qubit*  Allocate_Qubit();
	IMPLEMENTATION void Free_Qubit(Qubit*);
	//IMPLEMENTATION void init(size_t iMaxQubit);
	IMPLEMENTATION size_t getPhysicalQubitAddr(Qubit*);
    ~OriginQubitPool();
};

class OriginCBit : public CBit
{
	string name;
	bool bOccupancy;
	
public:
	CONSTRUCTOR OriginCBit(string name);
	IMPLEMENTATION inline bool getOccupancy() const
	{
		return bOccupancy;
	}
	IMPLEMENTATION inline void setOccupancy(bool _bOc)
	{
		bOccupancy = _bOc;
	}
	IMPLEMENTATION inline string getName() const {return name;}
};

class OriginCMem : public CMem
{
	vector<CBit*> vecBit;

public:

	CONSTRUCTOR OriginCMem(size_t maxMem);

	IMPLEMENTATION CBit * Allocate_CBit();
	IMPLEMENTATION size_t getMaxMem() const;
	IMPLEMENTATION size_t getIdleMem() const;
	IMPLEMENTATION void Free_CBit(CBit*);
	IMPLEMENTATION void clearAll();
    ~OriginCMem();
};

class OriginQResult : public QResult
{
private:
	map<string, bool> _Result_Map;

	//friend class Factory::QResultFactory;

public:

	CONSTRUCTOR OriginQResult();

	IMPLEMENTATION inline 
		map<string, bool> getResultMap() const	
	{
		return _Result_Map;
	}
	IMPLEMENTATION void append(pair<string, bool>);

    ~OriginQResult() {}
};

class OriginQMachineStatus : public QMachineStatus
{
private:
	int iStatus = -1;

	CONSTRUCTOR OriginQMachineStatus();

public:

	friend class Factory::QMachineStatusFactory;

	IMPLEMENTATION inline int getStatusCode() const
	{
		return iStatus;
	}
	IMPLEMENTATION inline void setStatusCode(int iStatus)
	{
		iStatus = iStatus;
	}
};

class OriginQVM : public QuantumMachine
{
private:
	QubitPool * _Qubit_Pool = nullptr;
	CMem * _CMem = nullptr;
    int _QProgram = -1;;
	QResult* _QResult = nullptr;
	QMachineStatus* _QMachineStatus = nullptr;	
    QuantumGateParam * _pParam;
    QuantumGates     * _pGates;
	struct Configuration
	{
		size_t maxQubit=32;
		size_t maxCMem=256;
	};
	Configuration _Config;
	
	//friend class Factory::QuantumMachineFactory;

public:
	CONSTRUCTOR OriginQVM();
	void init();
	Qubit* Allocate_Qubit();
	CBit* Allocate_CBit();
    void Free_Qubit(Qubit*);
    void Free_CBit(CBit*);
	void load(QProg &);
	void append(QProg&);
	void run();
	QMachineStatus* getStatus() const;
	QResult* getResult();
	void finalize();
};

#endif