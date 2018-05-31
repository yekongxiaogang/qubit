#include "OriginQuantumMachine.h"
#include "Factory.h"

OriginQResult::OriginQResult()
{

}

void OriginQResult::append(pair<string, bool> pairResult)
{
	// first search in map to find if CBit is existed
	
	auto iter=_Result_Map.find(pairResult.first);

	if (iter == _Result_Map.end())
	{	// if not existed
		_Result_Map.insert(pairResult);
	}
	else
	{	// if already existed
		_Result_Map[pairResult.first] = pairResult.second;
	}
}