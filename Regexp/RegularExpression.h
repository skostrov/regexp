#pragma once

#include "Common.h"

class RegularExpression
{
public:

						RegularExpression( string expression, bool lazyCompilation = false );
						~RegularExpression();

	bool				IsMatch( string inputString );

private:

	string				expression;
	bool				lazyCompilation;
	bool				isCompiled;

	void				Compile();
};
