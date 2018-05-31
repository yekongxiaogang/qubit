#ifndef _QEXCEPTION_H_

#if ! (_QEXCEPTION_VER_ > 20180411)

#define _QEXCEPTION_H_
#define _QEXCEPTION_VER_ 20180411

#include <exception>

using namespace std;

class QException : public exception
{

};
class QubitException : public QException
{

};
class MappingException : public QubitException
{

};
class Not_Implemented_Exception : public QException
{

};
class NoFreeQubitException : public QubitException
{

};
class RepeatFreeException : public QubitException
{

};
class QGateException : public QException
{

};
class NoUnitaryException : public QGateException
{

};
class QProgramException : public QException
{

};
class ErrorNodeTypeException : public QProgramException
{

};

#endif
#endif