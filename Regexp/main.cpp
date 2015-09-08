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
	auto s = parser.Parse( "(ab)*" );
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

		vector<string> tests = { "abba" };

		for ( const auto& i : tests )
		{
			bool test = M.TestMatching(i);

			if ( test )
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
}
