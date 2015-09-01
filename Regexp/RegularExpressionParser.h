#pragma once

#include "Common.h"

#include "Parsing\Parser.h"

using namespace RegexpParsing;

class RegularExpressionParser
{
public:

	typedef Parser::PToken* ParseTree;

						RegularExpressionParser();
						~RegularExpressionParser();

	ParseTree			Parse( string expression );

	void				DepthFirstSearchOnParseTree( ParseTree root, function<void(ParseTree)> visitor );

	void				PlotDotForParseTree( ParseTree root, const string& dotExe, const string& dotFile, const string& pngFile );
};

