#include "RegularExpression.h"

RegularExpression::RegularExpression( string expression, bool lazy ):
	lazyCompilation( lazy ),
	isCompiled( false )
{
}

RegularExpression::~RegularExpression()
{
}

bool RegularExpression::IsMatch( string inputString )
{
	if ( !isCompiled )
	{
		Compile();
	}
}

void RegularExpression::Compile()
{
	isCompiled = true;
}
