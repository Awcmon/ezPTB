//e^z Shunting Yard + RPN evaluator 05.09.15
//Add variable and function support
//Add multiprecision support

#include <iostream>
#include <stack>
#include <map>
#include "ALexer.h"

struct Operator
{
	int precedence;
	int associativity;
	int numargs;
};

std::map<std::string, Operator> operators;

std::vector<AToken> Inline2RPN(std::vector<AToken> tokens)
{
	//Shunting Yard
	std::vector<AToken> output;		//RPN output
	std::stack<AToken> opstack;		//operator stack
	for (int i = 0; i < (int)tokens.size(); i++)
	{
		AToken token = tokens[i];
		//std::cout << token.getStr() << "\n";
		switch (token.getType())
		{
		case TOKEN_NUMBER:
			std::cout << "Pushed number " << token.getStr() << " onto output.\n";
			output.push_back(token);
			break;
		case TOKEN_FUNCTION:
			opstack.push(token);
			break;
			//case function seperator needed here
		case TOKEN_OPERATOR:
			/*	while there is an operator token, o2, at the top of the operator stack, and either
			o1 is left - associative and its precedence is less than or equal to that of o2, or
			o1 is right associative, and has precedence less than that of o2,	*/
			while (!opstack.empty())
			{
				//if (operators[token.getStr()] != NULL){}
				if (((operators[token.getStr()].associativity == 0) && (operators[token.getStr()].precedence <= operators[opstack.top().getStr()].precedence)) || ((operators[token.getStr()].associativity == 1) && (operators[token.getStr()].precedence < operators[opstack.top().getStr()].precedence)))
				{
					std::cout << "Pushed operator " << opstack.top().getStr() << " onto output and popped from stack.\n";
					output.push_back(opstack.top());
					opstack.pop();
				}
				else
				{
					break;
				}
			}
			opstack.push(token);
			std::cout << "Pushed operator " << opstack.top().getStr() << " onto stack.\n";
			break;
		case TOKEN_LEFT_PAREN:
			std::cout << "Pushed ( onto stack.\n";
			opstack.push(token);
			break;
		case TOKEN_RIGHT_PAREN:
			bool loop = true;
			while (loop)
			{
				if (opstack.empty())
				{
					std::cout << "Mismatched parenthesis!\n";
					loop = false;
					break;
				}
				if (opstack.top().getType() != TOKEN_LEFT_PAREN)
				{
					std::cout << "Pushed operator " << opstack.top().getStr() << " onto output and popped from stack.\n";
					output.push_back(opstack.top());
					opstack.pop();
				}
				else
				{
					std::cout << "Popped " << opstack.top().getStr() << " from stack.\n";
					opstack.pop();
					loop = false;
					break;
				}
			}
			break;
		}	//end switch
	}	//end for loop
	std::cout << "Current output: ";
	for (int i = 0; i < (int)output.size(); i++)
	{
		std::cout << output[i].getStr() << " ";
	}
	std::cout << "\n";

	std::cout << "No tokens left to read, pushing remaining operators from stack onto output.\n";
	while (!opstack.empty())
	{
		if ((opstack.top().getType() == TOKEN_LEFT_PAREN) || (opstack.top().getType() == TOKEN_RIGHT_PAREN))
		{
			std::cout << "Mismatched parenthesis with character " << opstack.top().getStr() << "!\n";
			break;
		}
		std::cout << "Pushed operator " << opstack.top().getStr() << " onto output and popped from stack.\n";
		output.push_back(opstack.top());
		opstack.pop();
	}

	//Read output
	for (int i = 0; i < (int)output.size(); i++)
	{
		std::cout << output[i].getStr() << " ";
	}

	return output;
}

float RPNEvaulate(std::vector<AToken> input)
{
	std::stack<AToken> evstack;		//evaluation stack
	for (int i = 0; i < (int)input.size(); i++)
	{
		AToken token = input[i];
		switch (token.getType())
		{
		case TOKEN_NUMBER:
			evstack.push(token);
			break;
		case TOKEN_OPERATOR:
			int numargs = operators[token.getStr()].numargs;
			if (evstack.size() < numargs)
			{
				std::cout << "Insufficient values in the expression.\n";
				break;
			}
			else
			{
				std::vector<float> args;
			}
			break;
		}
	}
}

int main()
{
	//Set up lexer
	ALexer lexer;
	lexer.add("1234567890", TOKEN_NUMBER);
	lexer.add("+-*/^", TOKEN_OPERATOR);
	lexer.addSingle("(", TOKEN_LEFT_PAREN);
	lexer.addSingle(")", TOKEN_RIGHT_PAREN);
	lexer.addSingle(" ", TOKEN_SPACE);

	//Set up operators so Shunting Yard can deal with them
	operators["^"] = { 4, 1, 2 };
	operators["*"] = { 3, 0, 2 };
	operators["/"] = { 3, 0, 2 };
	operators["+"] = { 2, 0, 2 };
	operators["-"] = { 2, 0, 2 };

	//Handle input
	std::string input;
	std::cout << "Input: ";
	std::cin >> input;

	//Tokenize input
	std::vector<AToken> rpn = Inline2RPN(lexer.tokenize(input));

	std::cout << RPNEvaulate(rpn);

	return 0;
}