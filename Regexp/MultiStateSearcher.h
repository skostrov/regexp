#pragma once
#include "Common.h"

class FiniteAuto;
class FiniteAutoState;

class MultiStateSearcher
{
public:

	MultiStateSearcher(FiniteAuto* _auto);
	MultiStateSearcher(const MultiStateSearcher& _searcher);
	~MultiStateSearcher();

	FiniteAuto* GetAuto() const;

	const string& GetTestString() const;

	const size_t& GetTestStringPos() const;

	list<FiniteAutoState>& GetStateList();

	const bool& GetStringMatched() const;
	void SetStringMatched(const bool& _value);

	void AddState(const FiniteAutoState& _state);
	void RemoveState(const FiniteAutoState& _state);

	void Initialize(const string& _testString);
	bool TestMatching(const string& _testString);

private:

	FiniteAuto* automaton;
	string testString;
	size_t testStringPos;
	list<FiniteAutoState> stateList;
	bool stringMatched;
};

