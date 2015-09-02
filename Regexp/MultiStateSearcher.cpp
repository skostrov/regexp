#include "MultiStateSearcher.h"
#include "FiniteAuto.h"
#include "FiniteAutoState.h"


MultiStateSearcher::MultiStateSearcher(FiniteAuto* _auto, string _string) : automaton(_auto), testString(_string), testStringPos(0)
{
	stateList.push_back(FiniteAutoState(automaton->GetStart(), size_t(0)));
}

MultiStateSearcher::MultiStateSearcher(const MultiStateSearcher& _searcher) : automaton(_searcher.automaton), testString(_searcher.testString), stateList(_searcher.stateList)
{
}

MultiStateSearcher::~MultiStateSearcher()
{
}

const FiniteAuto* MultiStateSearcher::GetAuto() const
{
	return automaton;
}

const string& MultiStateSearcher::GetTestString() const
{
	return testString;
}

void  MultiStateSearcher::AddState(const FiniteAutoState& _state)
{
	stateList.push_back(_state);
}

void MultiStateSearcher::RemoveState(const FiniteAutoState& _state)
{
	stateList.remove(_state);
}

