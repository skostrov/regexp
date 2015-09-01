

#if !defined(RegexpParsing_COCO_PARSER_H__)
#define RegexpParsing_COCO_PARSER_H__



#include "Scanner.h"

namespace RegexpParsing {


class Errors {
public:
	int count;			// number of errors detected

	Errors();
	void SynErr(int line, int col, int n);
	void Error(int line, int col, const wchar_t *s);
	void Warning(int line, int col, const wchar_t *s);
	void Warning(const wchar_t *s);
	void Exception(const wchar_t *s);

}; // Errors

class Parser {
private:
	enum {
		_EOF=0,
		_Union=1,
		_Closure=2,
		_Symbol=3,
		_LeftRoundBracket=4,
		_RightRoundBracket=5
	};
	int maxT;

	Token *dummyToken;
	int errDist;
	int minErrDist;

	void SynErr(int n);
	void Get();
	void Expect(int n);
	bool StartOf(int s);
	void ExpectWeak(int n, int follow);
	bool WeakSeparator(int n, int syFol, int repFol);

public:
	Scanner *scanner;
	Errors  *errors;

	Token *t;			// last recognized token
	Token *la;			// lookahead token

	struct PToken
	{
		enum
		{
			Union,
			Concatenation,
			Closure,
			Terminal
		} Type;

		union
		{
			struct { PToken *P; };
			struct { PToken *P1, *P2; };
			struct { std::string Symbol; };
		};

		PToken() { memset( this, 0, sizeof( PToken ) ); }

		~PToken()
		{
			delete P1;
			delete P2;
		}
	};

	std::stack<PToken*> S;

	void PushUnion()
	{
		auto t = new PToken();
		t->Type = PToken::Union;

		t->P1 = S.top(); 
		S.pop();

		t->P2 = S.top(); 
		S.pop();

		S.push( t );
	}

	void PushConcatenation()
	{
		auto t = new PToken();
		t->Type = PToken::Concatenation;

		t->P1 = S.top(); 
		S.pop();

		t->P2 = S.top(); 
		S.pop();

		S.push( t );
	}

	void PushClosure()
	{
		auto t = new PToken();
		t->Type = PToken::Closure;

		t->P = S.top(); 
		S.pop();

		S.push( t );
	}

	void PushTerminal( wchar_t* w )
	{
		auto t = new PToken();
		t->Type = PToken::Terminal;

		std::wstring ws( w );
		std::string str( ws.begin(), ws.end() );

		t->Symbol = str;

		S.push( t );
	}



	Parser(Scanner *scanner);
	~Parser();
	void SemErr(const wchar_t* msg);

	void Regexp();
	void UnionExpression();
	void ConcatenationExpression();
	void ClosureExpression();
	void Expression();

	void Parse();

}; // end Parser

} // namespace


#endif

