#include "Common.h"

#include "Dot.h"
#include "MultiStateSearcher.h"
#include "RegularExpressionParser.h"
#include "FiniteAuto.h"
#include "Vertex.h"
#include "Edge.h"

void main()
{
	wcout.imbue( locale( "rus_rus.866" ) );
	wcin.imbue( locale( "rus_rus.866" ) );

	RegularExpressionParser parser;
	auto s = parser.Parse( "(a | b | c | 1 | 2 | 3) (a | b | c | 1 | 2 | 3)*" );
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
		fa->SaveImage( "C:/Program Files (x86)/Graphviz/bin/dot.exe",
			"./../tests/FiniteAuto.dot",
			"./../tests/FiniteAuto.png" );

		MultiStateSearcher M(fa);

		vector<string> tests = { "ab1231cccc32aaaaabbabbbbcccccccbbbbbaa123212122233333" };

		for (auto i : tests)
		{
			bool test = M.TestMatching(i);

			if (test)
			{
				cout << setw(50) << left << i << "+" << endl;
			}
			else
			{
				cout << setw(50) << left << i << "-" << endl;
			}
		}

		_getch();
	}
	else
	{
		WriteLine( "FAIL" );
	}

	/*FiniteAuto A;

	A.AddVertex("start", VertexStatus::Start);
	A.AddVertex("finish", VertexStatus::Final);
	A.AddVertex("q1");

	A.AddEdge("start", "q1", "a");
	A.AddEdge("q1", "q1", "a");
	A.AddEdge("q1", "finish", "");

	A.SaveImage("C:/Program Files (x86)/Graphviz/bin/dot.exe", "./../tests/FiniteAuto.dot", "./../tests/FiniteAuto.png");

	MultiStateSearcher M(&A);

	vector<string> tests = { "abaaaa" };

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
