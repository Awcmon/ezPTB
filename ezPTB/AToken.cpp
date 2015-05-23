#include "AToken.h"


AToken::AToken()
{
}

AToken::AToken(std::string _str, int _type)
{
	str = _str;
	type = _type;
}

AToken::~AToken()
{
}

void AToken::setStr(std::string _str)
{
	str = _str;
}

void AToken::setType(int _type)
{
	type = _type;
}

std::string AToken::getStr()
{
	return str;
}

int AToken::getType()
{
	return type;
}
