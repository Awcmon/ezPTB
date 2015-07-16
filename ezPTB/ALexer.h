#pragma once

#include "AToken.h"
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <iterator>

class ALexer
{
public:
	ALexer();
	~ALexer();

	std::vector<AToken> tokenize(std::string input);

	int getTypeFromString(std::string val);
	int findTypeEndPos(std::string input, std::vector<int> typeWhitelist);
	std::string getSubstrOfType(std::string input, std::vector<int> typeWhitelist);
	//void vectorPushToken(std::vector<AToken> &vec, AToken &token);

	void add(std::string val, int type);
	void addSingle(std::string val, int type);

	std::map< int, std::vector<std::string> > stringmap;

private:
	std::map<std::string, int> tokenmap;

};

