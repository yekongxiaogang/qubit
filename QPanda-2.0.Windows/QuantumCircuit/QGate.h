﻿#ifndef _QGATE_H_
#define _QGATE_H_

#include <map>
#include "../QuantumCircuit/QException.h"
#include <functional>
#define PI 3.14159265358979
using namespace std;

class QGate
{
protected:
	int qOpNum;
public:
	QGate();
    virtual double getAlpha() const = 0;
    virtual double getBeta() const = 0;
    virtual double getGamma() const = 0;
    virtual double getDelta() const = 0;
    virtual int getOpNum() const = 0;
};


typedef QGate* (*CreateGate)(void);
typedef QGate* (*CreateAngleGate)(double);
typedef QGate* (*CreateUnknownGate)(double, double, double, double);

class QGateFactory
{
public:
    void registClass(string name, CreateGate method);
    void registClass(string name, CreateAngleGate method);
    void registClass(string name, CreateUnknownGate method);
    QGate * getGateNode(std::string &);
    QGate * getGateNode(std::string &, double angle);
    QGate * getGateNode(std::string &, double alpha, double beta, double gamma, double delta);

    static QGateFactory * getInstance()
    {
        static QGateFactory  s_Instance;
        return &s_Instance;
    }
private:
private:
    map<string, CreateGate> m_gateMap;
    map<string, CreateAngleGate> m_angleGateMap;
    map<string, CreateUnknownGate> m_unknowGateMap;
    QGateFactory() {};

};

class RegisterAction {
public:
    RegisterAction(string className, CreateGate ptrCreateFn) {
        QGateFactory::getInstance()->registClass(className, ptrCreateFn);
    }
    RegisterAction(string className, CreateAngleGate ptrCreateFn) {
        QGateFactory::getInstance()->registClass(className, ptrCreateFn);
    }
    RegisterAction(string className, CreateUnknownGate ptrCreateFn) {
        QGateFactory::getInstance()->registClass(className, ptrCreateFn);
    }
};


class QSingleGate : public QGate
{
protected:
    double alpha;
    double beta;
    double gamma;
    double delta;

public:
	QSingleGate(QSingleGate&);
	QSingleGate();
	QSingleGate(double,double,double,double);

    inline double getAlpha()const
    {
        return alpha;
    }

    inline double getBeta() const
    {
        return this->beta;
    }
    inline double getGamma() const
    {
        return this->gamma;
    }
    inline double getDelta() const
    {
        return this->delta;
    }

    inline int getOpNum() const
    {
        return this->qOpNum;
    }
	//QSingleGate(double, double, double);
};

class XGate : public QSingleGate
{
public:
	XGate();
	XGate(double angle);
};


class YGate : public QSingleGate
{
public:
    YGate();
    YGate(double angle);
};
class ZGate : public QSingleGate
{
public:
    ZGate();
    ZGate(double angle);
};
class SGate : public QSingleGate
{
public:
    SGate();
};
class HadamardGate : public QSingleGate
{
public:
    HadamardGate();
};
//double quantum gates,contain CNOT ,CZ gates
class QDoubleGate : public QGate
{

protected:
    double alpha;
    double beta;
    double gamma;
    double delta;
public:
    QDoubleGate(QDoubleGate&);
    QDoubleGate();
    QDoubleGate(double, double, double,double);

    inline double getAlpha() const
    {
        return alpha;
    }

    inline double getBeta() const
    {
        return this->beta;
    }
    inline double getGamma() const
    {
        return this->gamma;
    }
    inline double getDelta() const
    {
        return this->delta;
    }

    inline int getOpNum() const
    {
        return this->qOpNum;
    }
    //QSingleGate(double, double, double);
};
class CNOTGate : public QDoubleGate
{
public:
    CNOTGate();
};
class CZGate : public QDoubleGate
{
public:
    CZGate();
};
#endif
