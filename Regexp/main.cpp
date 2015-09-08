#include "Common.h"

#include "Dot.h"
#include "MultiStateSearcher.h"
#include "RegularExpressionParser.h"
#include "GraphicFiniteAuto.h"
#include "Vertex.h"
#include "Edge.h"

void main()
{
	string regexp = "(ab | b)*";
	RegularExpressionParser parser;
	auto s = parser.Parse(regexp);
	if (s)
	{
		WriteLine("Regular expression " + regexp + " accepted");
		WriteLine();

		parser.PlotDotForParseTree(s.get(), 
			"C:/Program Files (x86)/Graphviz/bin/dot.exe", 
			"./../tests/test.dot",
			"./../tests/test.png");

		auto converter = ParseTreeToFAConverter(s);
		converter.PlotFA();

		auto fa = converter.GetFA();
		fa->SaveImage("C:/Program Files (x86)/Graphviz/bin/dot.exe",
			"./../tests/FiniteAuto.dot",
			"./../tests/FiniteAuto.png");

		MultiStateSearcher M(fa);

		vector<string> tests = { "abab", "abbb", "baba", "aaaa", "bbbb" };

		for (const auto& i : tests)
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
		WriteLine("Parser failed while parsing input regular expression " + regexp);

		_getch();
	}
}
