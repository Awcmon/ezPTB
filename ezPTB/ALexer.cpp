#include "ALexer.h"

ALexer::ALexer()
{
}

ALexer::~ALexer()
{
}

std::vector<AToken> ALexer::tokenize(std::string input)
{
	std::vector<AToken> tokens;

	int start = 0;
	int end = 0;

	std::string lastChar;
	int lastType;
	std::string curChar;
	int curType;
	std::string curString;

	for (int i = 0; i <= (int)input.size(); i++)
	{
		//first run
		if (i == 0)
		{
			lastChar = input.substr(i, 1);
			lastType = getTypeFromString(lastChar);
		}
		else
		{
			lastChar = curChar;
			lastType = curType;
		}

		curChar = input.substr(i, 1);
		curType = getTypeFromString(curChar);

		//If the types change, or if the current type is a parenthesis, store what we have as a token.
		if ((curType != lastType) || (curType == TOKEN_LEFT_PAREN) || (curType == TOKEN_RIGHT_PAREN))
		{
			end = i;
			tokens.push_back(AToken(input.substr(start, end-start), lastType));
			start = i;
		}
		else
		{
			//keep going, but if we have reached the end of the string, store what we have as a token.
			end = i;
			if (i == (int)input.size())
			{
				tokens.push_back(AToken(input.substr(start, end - start), lastType));
			}
		}
	}
	return tokens;
}

int ALexer::getTypeFromString(std::string val)
{
	if (tokenmap[val] != NULL)
	{
		return tokenmap[val];
	}
	return NULL;
}

void ALexer::addSingle(std::string val, int type)
{
	tokenmap.insert(std::pair<std::string , int>(val, type));
}

void ALexer::add(std::string val, int type)
{
	for (int i = 0; i < (int)val.size(); i++)
	{
		addSingle(val.substr(i, 1), type);
	}
}
