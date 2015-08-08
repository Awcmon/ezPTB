#include "Function.h"

Function::Function()
{
}

Function::Function(int _precedence, int _associativity, int _numargs)
{
	precedence = _precedence;
	associativity = _associativity;
	numargs = _numargs;
}

Function::~Function()
{
}

void Function::setPAN(int _precedence, int _associativity, int _numargs)
{
	precedence = _precedence;
	associativity = _associativity;
	numargs = _numargs;
}
