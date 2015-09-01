#include "Common.h"

#include "Dot.h"
#include "RegularExpressionParser.h"
#include "FiniteAuto.h"
#include "Vertex.h"
#include "Edge.h"

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

void main()
{
	wcout.imbue( locale( "rus_rus.866" ) );
	wcin.imbue( locale( "rus_rus.866" ) );

	RegularExpressionParser parser;
	auto s = parser.Parse( "((a|b)*ab(a|b)*)*|a" );
	if ( s )
	{
		WriteLine( "OK" );

		int vn = 0;
		Dot d;

		VisitStack( s, vn, d );

		d.Plot();
		d.SaveDot( "./../tests/test.dot" );
		d.SaveImage( "C:/Program Files (x86)/Graphviz/bin/dot.exe", "./../tests/test.dot", "./../tests/test.png" );
	}
	else
	{
		WriteLine( "FAIL" );
	}

	//
	//d.AddVertex( "V0", "Xor", "gray67" );
	//d.AddVertex( "V1", "And" );
	//d.AddVertex( "V2", "a" );
	//d.AddVertex( "V3", "b" );
	//d.AddVertex( "V4", "False", "gray93" );
	//
	//d.AddEdge( "V1", "V2", "a" );
	//d.AddEdge( "V1", "V3", "b" );
	//d.AddEdge( "V0", "V1", "c" );
	//d.AddEdge( "V0", "V4", "d" );
	

	/*Dot d;

	d.AddVertex( "V0", "Xor", "gray67" );
	d.AddVertex( "V1", "And" );
	d.AddVertex( "V2", "a" );
	d.AddVertex( "V3", "b" );
	d.AddVertex( "V4", "False", "gray93" );

	d.AddEdge( "V1", "V2", "a" );
	d.AddEdge( "V1", "V3", "b" );
	d.AddEdge( "V0", "V1", "c" );
	d.AddEdge( "V0", "V4", "d" );

	d.Plot();
	d.SaveDot( "./../tests/test.dot" );
	d.SaveImage( "C:/Program Files (x86)/Graphviz/bin/dot.exe", "./../tests/test.dot", "./../tests/test.png" );*/

	//WriteLine( "Tests" );
	//
	//string inputLine = ReadLine();
	//WriteLine( inputLine );
	//
	//ReadLine();

	//Vertex start("Start", Status::Start), finish("Finish", Status::Final), q("q");
	//
	//Edge es1(&start, &finish, "b"), es2(&start, &q, "a");
	//Edge ef(&finish, &finish, "a");
	//Edge eq1(&q, &q, "b"), eq2(&q, &finish, "b");
	//Edge es3(&start, &q, "b");
	//
	//FiniteAuto A;
	//
	//A.AddVertex(start);
	//A.AddVertex(finish);
	//A.AddVertex(q);
	//
	//A.SaveImage("C:/Program Files (x86)/Graphviz/bin/dot.exe", "./../tests/FiniteAuto.dot", "./../tests/FiniteAuto.png");
	//
	//ReadLine();
}
