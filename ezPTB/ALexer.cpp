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

		//Set the type of the current token if it is blank/null.
		if (curToken.getType() == TOKEN_NULL) { curToken.setType(curType); }

		//If the curToken is a number, try to find the whole number. Delimiters are any non-number token.
		if (curToken.getType() == TOKEN_NUMBER)
		{
			std::string sub = getSubstrOfType(input, { TOKEN_NUMBER });
			curToken.setStr(sub);
			input.erase(0, sub.length());
			tokens.push_back(curToken);
			curToken.reset();
		}
		//If the curToken is a letter, try to find whether or not it is a constant, function, or a user-definable variable in that priority. Letters and numbers are included. Delimiters are everything else.
		else if (curToken.getType() == TOKEN_LETTER)
		{
			std::string sub = getSubstrOfType(input, { TOKEN_LETTER, TOKEN_NUMBER } );
			curToken.setStr(sub);

			if (curToken.getType() == TOKEN_LETTER)
			{
				std::vector<std::string> constVec = stringmap[TOKEN_CONSTANT];
				for (int i = 0; i < (int)constVec.size(); i++)
				{
					if (sub == constVec[i])
					{
						curToken.setType(TOKEN_CONSTANT);
						break;
					}
				}
			}

			if (curToken.getType() == TOKEN_LETTER)
			{
				std::vector<std::string> funcVec = stringmap[TOKEN_FUNCTION];
				for (int i = 0; i < (int)funcVec.size(); i++)
				{
					if (sub == funcVec[i])
					{
						curToken.setType(TOKEN_FUNCTION);
						break;
					}
				}
			}

			if (curToken.getType() == TOKEN_LETTER)
			{
				curToken.setType(TOKEN_VARIABLE);
			}

			input.erase(0, sub.length());
			tokens.push_back(curToken);
			curToken.reset();
		}
		else if (curToken.getType() == TOKEN_OPERATOR || TOKEN_LEFT_PAREN || TOKEN_RIGHT_PAREN)
		{
			curToken.setStr(curChar);
			input.erase(0, 1);
			tokens.push_back(curToken);
			curToken.reset();
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
	else
	{
		return TOKEN_UNKNOWN;
	}
	return NULL;
}

//Note: This starts from the beginning of the string only.
int ALexer::findTypeEndPos(std::string input, std::vector<int> typeWhitelist)
{
	for (int i = 0; i < (int)input.size(); i++)
	{
		std::string curChar = input.substr(i, 1);
		//Check if the curChar matches anything in the whitelist.
		bool match = false;
		for (int k = 0; k < (int)typeWhitelist.size(); k++)
		{
			if (getTypeFromString(curChar) == typeWhitelist[k])
			{
				match = true;
			}
		}
		if (!match)
		{
			//If it does not match, this is the endpoint.
			return i;
		}
	}

	return (int)input.size();
}

//Note: This starts from the beginning of the string only.
std::string ALexer::getSubstrOfType(std::string input, std::vector<int> typeWhitelist)
{
	return input.substr(0, findTypeEndPos(input, typeWhitelist));
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
