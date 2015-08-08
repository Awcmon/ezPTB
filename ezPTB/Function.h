#pragma once

#include "Globals.h"
#include <vector>

class Function
{
public:
	Function();
	Function(int _precedence, int _associativity, int _numargs);
	~Function();

	void setPAN(int _precedence, int _associativity, int _numargs);

	mpnum(*func)(std::vector<mpnum>);

	int precedence;
	int associativity;
	int numargs;
};
