#pragma once

#include "AToken.h"
#include <vector>
#include <map>
#include <iostream>

class ALexer
{
public:
	ALexer();
	~ALexer();

	std::vector<AToken> tokenize(std::string input);
	int getTypeFromString(std::string val);
	void add(std::string val, int type);
	void addSingle(std::string val, int type);

private:
	std::map<std::string, int> tokenmap;
};

