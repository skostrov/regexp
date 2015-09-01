#include "RegularExpressionParser.h"

#include "Parsing\Parser.h"
#include "Parsing\Scanner.h"

using namespace RegexpParsing;

RegularExpressionParser::RegularExpressionParser()
{
}

RegularExpressionParser::~RegularExpressionParser()
{
}

bool RegularExpressionParser::Parse( string expression )
{
	Scanner* scanner = new Scanner( ( const unsigned char* )expression.c_str(), expression.length() );
	Parser* parser = new Parser( scanner );
	parser->Parse();
	bool success = parser->errors->count == 0;

	delete scanner;
	delete parser;

	return success;
}