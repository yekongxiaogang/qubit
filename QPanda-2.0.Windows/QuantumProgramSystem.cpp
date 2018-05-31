// QuantumProgramSystem.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include<iostream>
#include "QPanda.h"
#include "QuantumAlgorithm\test\test.h"

using namespace std;

int main()
{
    int time0 = 0;
    int time1 = 0;
    for (size_t i = 0; i < 100; i++)
    {
        /* if (DJalgorithm())
        {
        time1++;
        }
        else
        {
        time0++;
        }
        */
        HHL_Algorithm1();
        //cout << Grover(3) << endl;
        //controlandDagger();
    }
    cout << 1 << ":\t" << time1 << endl;
    cout << 0 << ":\t" << time0 << endl;

    getchar();
    return 0;

}

