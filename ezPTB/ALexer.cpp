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

	AToken curToken;

	while (input.size() > 0)
	{
		std::string curChar = input.substr(0, 1);
		int curType = getTypeFromString(curChar);

		if (curToken.getType() == TOKEN_NULL)
		{
			curToken.setType(curType);
			
			//See if the next token will be a constant or function
			std::vector<std::string> constVec = stringmap[TOKEN_CONSTANT];
			for (int i = 0; i < (int)constVec.size(); i++)
			{
				if (input.find(constVec[i]) == 0)
				{
					curToken.setType(TOKEN_CONSTANT);
					curToken.setStr(input.substr(0, constVec[i].size()));
					input.erase(0, constVec[i].size());
				}
			}

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
		else if (curType == TOKEN_LETTER && curToken.getType() != TOKEN_FUNCTION && curToken.getType() != TOKEN_CONSTANT && (curToken.getType() == TOKEN_LETTER || curToken.getType() == TOKEN_VARIABLE)) //I am so sorry for this monstrous condition.
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
