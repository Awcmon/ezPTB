#pragma once
class Function
{
public:
	Function();
	~Function();

	int precedence;
	int associativity;
	int numargs;
};

