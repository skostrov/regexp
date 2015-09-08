#include "RegularExpressionParser.h"

#include "Dot.h"
#include "GraphicFiniteAuto.h"

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

ParseTreeToFAConverter::ParseTreeToFAConverter( RegularExpressionParser::ParseTree t ):
	tree( t ),
	fa( nullptr ),
	s( nullptr ),
	f( nullptr )
{
}

ParseTreeToFAConverter::E::E( V* sv, V* fv, R *l, string c ):
	Vs( sv ),
	Vf( fv ),
	L( l ),
	C( c )
{
	Vs->Out.push_back( this );
	Vf->In.push_back( this );
}

void ParseTreeToFAConverter::PlotFA()
{
	s = new V();
	f = new V();

	AppednRuleToE( new E( s, f, tree.get() ) );

	fa = new GraphicFiniteAuto();

	auto q = stack<V*>();
	auto qm = unordered_map<V*,bool>();
	auto em = unordered_map<E*,bool>();
	auto tt = unordered_map<V*,Vertex*>();

	q = stack<V*>();
	qm.clear();
	em.clear();
	q.push( s );

	while ( !q.empty() )
	{
		auto item = q.top();
		q.pop();

		if ( qm.find( item ) != qm.end() )
			continue;

		qm[item] = true;

		// visit
		
		auto st = VertexStatus::Normal;
		if ( item == s )
		{
			st = VertexStatus::Start;
		}
		else if ( item == f )
		{
			st = VertexStatus::Final;
		}

		auto nv = fa->AddVertex( st );
		tt[item] = nv; 

		// childs
	
		for ( const auto& it : item->Out )
		{
			q.push( it->Vf );
		}
	}

	q = stack<V*>();
	qm.clear();
	em.clear();
	q.push( s );

	while ( !q.empty() )
	{
		auto item = q.top();
		q.pop();

		if ( qm.find( item ) != qm.end() )
			continue;

		qm[item] = true;

		// visit

		// childs
	
		for ( const auto& it : item->Out )
		{
			if ( em.find( it ) == em.end() )
			{
				em[it] = true;

				fa->AddEdge( tt[item], tt[it->Vf], it->C );
			}
			
			q.push( it->Vf );
		}

		for ( const auto& it : item->In )
		{
			if ( em.find( it ) == em.end() )
			{
				em[it] = true;

				fa->AddEdge( tt[it->Vs], tt[item], it->C );
			}
		}
	}
}

void ParseTreeToFAConverter::AppednRuleToE( E* e )
{
	if ( e->L == nullptr
		|| !e->C.empty() )
		return;

	switch ( e->L->Type )
	{
		case R::Union: 
			
			{
				auto s1 = new V();
				auto f1 = new V();
				auto e1 = new E( s1, f1, e->L->P1 );

				auto s2 = new V();
				auto f2 = new V();
				auto e2 = new E( s2, f2, e->L->P2 );
			
				auto e1s = new E( e->Vs, s1, nullptr );
				auto e1f = new E( f1, e->Vf, nullptr );

				auto e2s = new E( e->Vs, s2, nullptr );
				auto e2f = new E( f2, e->Vf, nullptr );

				RemoveE( e );

				AppednRuleToE( e1 );
				AppednRuleToE( e2 );
			}

			break;

		case R::Concatenation:
			
			{
				auto n = new V();
				auto e1 = new E( e->Vs, n, e->L->P1 );
				auto e2 = new E( n, e->Vf, e->L->P2 );
			
				RemoveE( e );

				AppednRuleToE( e1 );
				AppednRuleToE( e2 );
			}
			
			break;

		case R::Closure: 
			
			{
				auto sn = new V();
				auto fn = new V();
				auto en = new E( sn, fn, e->L->P );
				auto enl = new E( fn, sn, nullptr );
				auto es = new E( e->Vs, sn, nullptr );
				auto ef = new E( fn, e->Vf, nullptr );

				AppednRuleToE( en );
			}
			
			break;

		case R::Terminal:

			e->C = e->L->Symbol;
			e->L = nullptr;

			break;
	}
}

void ParseTreeToFAConverter::RemoveE( E* e )
{
	e->Vs->Out.remove( e );
	e->Vf->In.remove( e );
	delete e;
}

void ParseTreeToFAConverter::PlotDotForGeneratedFA( const string& dotExe, const string& dotFile, const string& pngFile )
{
	int vertexNum = 0;
	Dot dot;

	auto q = stack<V*>();
	auto qm = unordered_map<V*,bool>();
	auto em = unordered_map<E*,bool>();
	q.push( s );

	while ( !q.empty() )
	{
		auto item = q.top();
		q.pop();

		if ( qm.find( item ) != qm.end() )
			continue;

		qm[item] = true;

		// visit
		
		dot.AddVertex( "V" + to_string( ( int )item ), " " );

		// childs
	
		for ( const auto& it : item->Out )
		{
			if ( em.find( it ) == em.end() )
			{
				em[it] = true;

				dot.AddEdge( "V" + to_string( ( int )item ),
					"V" + to_string( ( int )( it->Vf ) ),
					it->C );
			}
			
			q.push( it->Vf );
		}

		for ( const auto& it : item->In )
		{
			if ( em.find( it ) == em.end() )
			{
				em[it] = true;

				dot.AddEdge( "V" + to_string( ( int )( it->Vs ) ),
					"V" + to_string( ( int )item ),
					it->C  );
			}
		}
	}

	dot.Plot();
	dot.SaveDot( dotFile );
	dot.SaveImage( dotExe, dotFile, pngFile );
}