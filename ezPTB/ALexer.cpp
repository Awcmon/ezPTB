#include "ALexer.h"

ALexer::ALexer()
{
}

ALexer::~ALexer()
{
}

/*deprecated 06.30.15
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
*/

std::vector<AToken> ALexer::tokenize(std::string input)
{
	std::vector<AToken> tokens;

	AToken curToken;

	while (input.size() > 0)
	{
		std::string curChar = input.substr(0, 1);
		int curType = getTypeFromString(curChar);

		if (curToken.getType() == TOKEN_NULL)
		{
			curToken.setType(curType);
			
			//See if the next token will be a function
			std::vector<std::string> funcVec = stringmap[TOKEN_FUNCTION];
			for (int i = 0; i < (int)funcVec.size(); i++)
			{
				if (input.find(funcVec[i]) == 0)
				{
					curToken.setType(TOKEN_FUNCTION);
					curToken.setStr(input.substr(0, funcVec[i].size()));
					input.erase(0, funcVec[i].size());
				}
			}
			
		}

		if (curType == TOKEN_NUMBER && curToken.getType() == TOKEN_NUMBER)
		{
			curToken.setStr(curToken.getStr() + curChar);
			input.erase(0, 1);
		}
		else if (curType == TOKEN_LETTER && curToken.getType() != TOKEN_FUNCTION && (curToken.getType() == TOKEN_LETTER || curToken.getType() == TOKEN_VARIABLE))
		{
			if (curToken.getType() == TOKEN_LETTER)
			{
				curToken.setType(TOKEN_VARIABLE);
			}
			curToken.setStr(curToken.getStr() + curChar);
			input.erase(0, 1);
		}
		else if (curType != curToken.getType())
		{
			tokens.push_back(curToken);
			curToken.reset();
		}
		else
		{
			curToken.setStr(curChar);
			input.erase(0, 1);
			tokens.push_back(curToken);
			curToken.reset();
		}
	}

	//If there is still a token, then put it in the vector
	if (curToken.getType() != TOKEN_NULL)
	{
		tokens.push_back(curToken);
		curToken.reset();
	}

	return tokens;
}


int ALexer::getTypeFromString(std::string val)
{
	if (tokenmap[val] != NULL)
	{
		return tokenmap[val];
	}
	else
	{
		return TOKEN_UNKNOWN;
	}
	return NULL;
}

void ALexer::addSingle(std::string val, int type)
{
	tokenmap.insert(std::pair<std::string , int>(val, type));
	stringmap[type].push_back(val);
}

void ALexer::add(std::string val, int type)
{
	for (int i = 0; i < (int)val.size(); i++)
	{
		addSingle(val.substr(i, 1), type);
	}
}
