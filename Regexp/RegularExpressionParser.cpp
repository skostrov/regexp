#include "RegularExpressionParser.h"

#include "Dot.h"

namespace
{
	void VisitStack( Parser::PToken* vertex, int& vertexNum, Dot& dot )
	{
		int vn;
	
		switch ( vertex->Type )
		{
			case Parser::PToken::Union: 
				
				vn = vertexNum;
				vertexNum++;
	
				dot.AddEdge( "V" + to_string( vn ), "V" + to_string( vertexNum ) );
				VisitStack( vertex->P1, vertexNum, dot );
	
				dot.AddEdge( "V" + to_string( vn ), "V" + to_string( vertexNum ) );
				VisitStack( vertex->P2, vertexNum, dot );
	
				dot.AddVertex( "V" + to_string( vn ), "Union " + to_string( vn ) );
	
				break;
	
			case Parser::PToken::Concatenation: 
				
				vn = vertexNum;
				vertexNum++;
	
				dot.AddEdge( "V" + to_string( vn ), "V" + to_string( vertexNum ) );
				VisitStack( vertex->P1, vertexNum, dot );
	
				dot.AddEdge( "V" + to_string( vn ), "V" + to_string( vertexNum ) );
				VisitStack( vertex->P2, vertexNum, dot );
	
				dot.AddVertex( "V" + to_string( vn ), "Concatenation " + to_string( vn ) );
	
				break;
	
			case Parser::PToken::Closure: 
				
				vn = vertexNum;
				vertexNum++;
	
				dot.AddEdge( "V" + to_string( vn ), "V" + to_string( vertexNum ) );
				VisitStack( vertex->P, vertexNum, dot );
	
				dot.AddVertex( "V" + to_string( vn ), "Closure " + to_string( vn ) );
	
				break;
			
			case Parser::PToken::Terminal:
	
				vn = vertexNum;
				vertexNum++;
	
				dot.AddVertex( "V" + to_string( vn ), vertex->Symbol + to_string( vn )  );
	
				break;
		}
	}
}

RegularExpressionParser::RegularExpressionParser()
{
}

RegularExpressionParser::~RegularExpressionParser()
{
}

RegularExpressionParser::ParseTree RegularExpressionParser::Parse( string expression )
{
	Scanner* scanner = new Scanner( ( const unsigned char* )expression.c_str(), expression.length() );
	Parser* parser = new Parser( scanner );
	parser->Parse();

	auto result = parser->S;
	bool success = parser->errors->count == 0
		&& result.size() == 1;

	delete scanner;
	delete parser;

	return ParseTree( ( success ) ? result.top() : nullptr );
}

void RegularExpressionParser::DepthFirstSearchOnParseTree( RegularExpressionParser::TreeVertex root,
	function<void(RegularExpressionParser::TreeVertex)> visitor )
{
	auto q = stack<RegularExpressionParser::TreeVertex>();
	q.push( root );
	
	while ( !q.empty() )
	{
		auto item = q.top();
		q.pop();

		if ( visitor )
		{
			visitor( item );
		}
	
		switch ( item->Type )
		{
			case Parser::PToken::Union: 
			case Parser::PToken::Concatenation: 
				
				q.push( item->P1 );
				q.push( item->P2 );

				break;

			case Parser::PToken::Closure: 
				
				q.push( item->P );

				break;
		}
	}
}

void RegularExpressionParser::PlotDotForParseTree( TreeVertex root, const string& dotExe, const string& dotFile, const string& pngFile )
{
	int vertexNum = 0;
	Dot dot;

	VisitStack( root, vertexNum, dot );

	dot.Plot();
	dot.SaveDot( dotFile );
	dot.SaveImage( dotExe, dotFile, pngFile );
}
