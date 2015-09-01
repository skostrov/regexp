#include "Common.h"

void main()
{
	wcout.imbue( locale( "rus_rus.866" ) );
	wcin.imbue( locale( "rus_rus.866" ) );

	WriteLine( "Tests" );

	string inputLine = ReadLine();
	WriteLine( inputLine );

	ReadLine();
}
