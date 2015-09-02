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

	/*RegularExpressionParser parser;
	auto s = parser.Parse( "((a|b)*ab(a|b)*)*|a" );
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

		vector<string> tests = { "a", "ab", "aaaaabbbb", "bbab" };

		for (auto i : tests)
		{
			bool test = M.TestMatching(i);

			if (test)
			{
				cout << setw(10) << left << i << "+" << endl;
			}
			else
			{
				cout << setw(10) << left << i << "-" << endl;
			}
		}

		_getch();
	}
	else
	{
		WriteLine( "FAIL" );
	}*/

	FiniteAuto A;

	A.AddVertex("start", Status::Start);
	A.AddVertex("finish", Status::Final);
	A.AddVertex("q");

	A.AddEdge("start", "finish", "");
	A.AddEdge("start", "q", "");
	A.AddEdge("q", "q", "a");
	A.AddEdge("q", "finish", "b");
	A.AddEdge("finish", "finish", "a");

	A.SaveImage("C:/Program Files (x86)/Graphviz/bin/dot.exe", "./../tests/FiniteAuto.dot", "./../tests/FiniteAuto.png");

	MultiStateSearcher M(&A);

	vector<string> tests = { "b", "ba", "baaaa", "ab", "abaaaa", "abbbb", "abbbbaaa", "aaaa", "bab", "babbbb"};

	for (auto i : tests)
	{
		bool test = M.TestMatching(i);

		if (test)
		{
			cout << setw(10) << left << i << "+" << endl;
		}
		else
		{
			cout << setw(10) << left << i << "-" << endl;
		}
	}

	_getch();

}
