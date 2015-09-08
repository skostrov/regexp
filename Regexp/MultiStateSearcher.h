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

	list<FiniteAutoState>& GetStateList();

	void AddState(const FiniteAutoState& _state);
	void RemoveState(const FiniteAutoState& _state);

	void Initialize(const string& _testString);
	bool TestMatching(const string& _testString);
	bool CheckFinalState() const;
	void PassUnlabeledEdges(list<FiniteAutoState>& _newStates, list<FiniteAutoState>& _oldStates);

private:

	FiniteAuto* automaton;
	list<FiniteAutoState> stateList;

};

