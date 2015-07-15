#pragma once

#include <string>

enum TokenType
{
	TOKEN_NULL,
	TOKEN_UNKNOWN,
	TOKEN_SPACE,
	TOKEN_NUMBER,
	TOKEN_LETTER,
	TOKEN_VARIABLE,
	TOKEN_CONSTANT,
	TOKEN_FUNCTION,
	TOKEN_SYMBOL,
	TOKEN_OPERATOR,
	TOKEN_LEFT_PAREN,
	TOKEN_RIGHT_PAREN
};

class AToken
{
public:
	AToken();
	AToken(std::string _str, int _type);
	~AToken();

	void setStr(std::string _str);
	void setType(int _type);
	std::string getStr();
	int getType();
	void reset();

private:
	std::string str;
	int type;
};

