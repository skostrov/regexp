#pragma once

#include "Common.h"

#include "Parsing\Parser.h"
#include "Parsing\Scanner.h"

using namespace RegexpParsing;

class RegularExpressionParser
{
public:

	RegularExpressionParser();
	~RegularExpressionParser();

	Parser::PToken* Parse( string expression );
};

