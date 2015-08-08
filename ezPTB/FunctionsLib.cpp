#include "FunctionsLib.h"
#include <math.h>

mpnum add(std::vector<mpnum> args)
{
	return args[0] + args[1];
}

mpnum subtract(std::vector<mpnum> args)
{
	return args[0] - args[1];
}

mpnum multiply(std::vector<mpnum> args)
{
	return args[0] * args[1];
}

mpnum divide(std::vector<mpnum> args)
{
	return args[0] / args[1];
}

mpnum pow(std::vector<mpnum> args)
{
	return pow(args[0], args[1]);
}
