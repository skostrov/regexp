#pragma once

#include "Common.h"

#include "Parsing\Parser.h"

using namespace RegexpParsing;

class RegularExpressionParser
{
public:

	typedef Parser::PToken* TreeVertex;
	typedef shared_ptr<Parser::PToken> ParseTree;

						RegularExpressionParser();
						~RegularExpressionParser();

	ParseTree			Parse( string expression );

	void				DepthFirstSearchOnParseTree( TreeVertex root, function<void(TreeVertex)> visitor );

	void				PlotDotForParseTree( TreeVertex root, const string& dotExe, const string& dotFile, const string& pngFile );
};

