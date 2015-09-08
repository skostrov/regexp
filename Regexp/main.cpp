#include "Common.h"

#include "Dot.h"
#include "MultiStateSearcher.h"
#include "RegularExpressionParser.h"
#include "FiniteAuto.h"
#include "GraphicFiniteAuto.h"
#include "Vertex.h"
#include "Edge.h"

void main()
{
	wcout.imbue( locale( "rus_rus.866" ) );
	wcin.imbue( locale( "rus_rus.866" ) );

	RegularExpressionParser parser;
	auto s = parser.Parse( "(a | b)*" );
	//auto s = parser.Parse( "(ab)*" );
	if ( s )
	{
		WriteLine( "OK" );

		parser.PlotDotForParseTree( s.get(), 
			"C:/Program Files (x86)/Graphviz/bin/dot.exe", 
			"./../tests/test.dot",
			"./../tests/test.png" );

		auto converter = ParseTreeToFAConverter( s );
		converter.PlotFA();

		converter.PlotDotForGeneratedFA( "C:/Program Files (x86)/Graphviz/bin/dot.exe", 
			"./../tests/testfa.dot",
			"./../tests/testfa.png" );

		auto fa = converter.GetFA();
		//fa->SaveImage( "C:/Program Files (x86)/Graphviz/bin/dot.exe",
		//	"./../tests/FiniteAuto.dot",
		//	"./../tests/FiniteAuto.png" );

		MultiStateSearcher M(fa);

		vector<string> tests = { "ab1231cccc32" };

		for (auto i : tests)
		{
			bool test = M.TestMatching(i);

			if (test)
			{
				cout << setw(30) << left << i << "+" << endl;
			}
			else
			{
				cout << setw(30) << left << i << "-" << endl;
			}
		}

		_getch();
	}
	else
	{
		WriteLine( "FAIL" );
	}

	/*GraphicFiniteAuto A;

	Vertex* start = A.AddVertex(VertexStatus::Start);
	Vertex* q = A.AddVertex();
	Vertex* finish = A.AddVertex(VertexStatus::Final);

	A.AddEdge(start, q, "");
	A.AddEdge(q, q, "b");
	A.AddEdge(q, finish, "");

	A.SaveImage();

	MultiStateSearcher M(&A);

	vector<string> tests = { "bbbbbb", "aba", "abba", "abbbbbbba", "abbbb", "bbbba", "" };

	for (auto i : tests)
	{
		bool test = M.TestMatching(i);

		if (test)
		{
			cout << setw(20) << left << i << "+" << endl;
		}
		else
		{
			cout << setw(20) << left << i << "-" << endl;
		}
	}

	_getch();*/

}
