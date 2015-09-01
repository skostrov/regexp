#include "RegularExpressionParser.h"

RegularExpressionParser::RegularExpressionParser()
{
}

RegularExpressionParser::~RegularExpressionParser()
{
}

Parser::PToken* RegularExpressionParser::Parse( string expression )
{
	Scanner* scanner = new Scanner( ( const unsigned char* )expression.c_str(), expression.length() );
	Parser* parser = new Parser( scanner );
	parser->Parse();

	auto result = parser->S;
	bool success = parser->errors->count == 0
		&& result.size() == 1;

	delete scanner;
	delete parser;

	return ( success ) ? result.top() : nullptr;
}