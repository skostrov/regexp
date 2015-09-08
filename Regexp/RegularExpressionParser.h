#pragma once

#include "Common.h"

#include "Parsing\Parser.h"

using namespace RegexpParsing;

class GraphicFiniteAuto;

class RegularExpressionParser
{
public:

	typedef Parser::PToken* TreeVertex;
	typedef shared_ptr<Parser::PToken> ParseTree;

	RegularExpressionParser();
	~RegularExpressionParser();

	ParseTree Parse(string expression);

	void DepthFirstSearchOnParseTree(TreeVertex root, function<void(TreeVertex)> visitor);

	void PlotDotForParseTree(TreeVertex root, const string& dotExe, const string& dotFile, const string& pngFile);
};

class ParseTreeToFAConverter
{
public:

	ParseTreeToFAConverter(RegularExpressionParser::ParseTree tree);

	void PlotFA();
	void PlotDotForGeneratedFA(const string& dotExe, const string& dotFile, const string& pngFile);


	GraphicFiniteAuto* GetFA() const;

private:

	typedef Parser::PToken R;
	struct V;

	struct E
	{
		V* Vs;
		V* Vf;
		R* L;
		string C;

		E(V* sv, V* fv, R *l, string c = "");
	};

	struct V
	{
		list<E*> In, Out;
	};

	RegularExpressionParser::ParseTree tree;
	V* s;
	V* f;
	GraphicFiniteAuto* fa;

	void AppednRuleToE(E* e);
	void RemoveE(E* e);
};
