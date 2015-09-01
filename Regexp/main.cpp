#include "Common.h"

#include "Dot.h"

void main()
{
	wcout.imbue( locale( "rus_rus.866" ) );
	wcin.imbue( locale( "rus_rus.866" ) );

	Dot d;

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
	d.SaveImage( "C:/Program Files (x86)/Graphviz/bin/dot.exe", "./../tests/test.dot", "./../tests/test.png" );

	//WriteLine( "Tests" );
	//
	//string inputLine = ReadLine();
	//WriteLine( inputLine );
	//
	//ReadLine();
}
