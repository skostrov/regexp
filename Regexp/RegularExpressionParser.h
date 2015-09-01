#pragma once

#include "Common.h"

class RegularExpressionParser
{
public:

	struct Token
	{
	};

	struct Operator : public Token
	{
	};

	struct MonoOperator : public Operator
	{
		Token *P;
	};

	struct BinaryOperator : public Operator
	{
		Token *P1, *P2;
	};

	struct Union : public BinaryOperator
	{
	};

	struct Concatenation : public BinaryOperator
	{
	};

	struct Closure : public MonoOperator
	{
	};

	struct Terminal : public Token
	{
		string Symbol;
	};

	RegularExpressionParser();
	~RegularExpressionParser();

	bool Parse( string expression );

private:

	stack<Token*> stack;
};

