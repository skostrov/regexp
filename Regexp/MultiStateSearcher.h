#pragma once
#include "Common.h"

class FiniteAuto;
class FiniteAutoState;

class MultiStateSearcher
{
public:

	MultiStateSearcher(FiniteAuto* _auto, string _string);
	~MultiStateSearcher();

	const FiniteAuto* GetAuto() const;
	const string& GetTestString() const;

	void AddState(const FiniteAutoState& _state);
	void RemoveState(const FiniteAutoState& _state);

	void NextState();

private:

	FiniteAuto* automaton;
	string testString;
	size_t testStringPos;
	list<FiniteAutoState> stateList;
};

