#include "MultiStateSearcher.h"
#include "FiniteAuto.h"
#include "FiniteAutoState.h"


MultiStateSearcher::MultiStateSearcher(FiniteAuto* _auto) : automaton(_auto), testStringPos(0)
{
	stateList.push_back(FiniteAutoState(automaton->GetStart()));
}

MultiStateSearcher::MultiStateSearcher(const MultiStateSearcher& _searcher) : automaton(_searcher.automaton), stateList(_searcher.stateList)
{
}

MultiStateSearcher::~MultiStateSearcher()
{
}

FiniteAuto* MultiStateSearcher::GetAuto() const
{
	return automaton;
}

const string& MultiStateSearcher::GetTestString() const
{
	return testString;
}

const size_t& MultiStateSearcher::GetTestStringPos() const
{
	return testStringPos;
}

list<FiniteAutoState>& MultiStateSearcher::GetStateList()
{
	return stateList;
}

const bool& MultiStateSearcher::GetStringMatched() const
{
	return stringMatched;
}

void MultiStateSearcher::SetStringMatched(const bool& _value)
{
	stringMatched = _value;
}

void  MultiStateSearcher::AddState(const FiniteAutoState& _state)
{
	stateList.push_back(_state);
}

void MultiStateSearcher::RemoveState(const FiniteAutoState& _state)
{
	stateList.remove(_state);
}

void MultiStateSearcher::Initialize(const string& _testString)
{
	testString = _testString;
	testStringPos = size_t(0);

	stateList.clear();
	stateList.push_back(FiniteAutoState(automaton->GetStart()));

	stringMatched = false;
}

bool MultiStateSearcher::TestMatching(const string& _testString)
{
	Initialize(_testString);

	while (stateList.size() && (!stringMatched))
	{
		list<FiniteAutoState> newStates;

		auto i = stateList.begin();
		while ((i != stateList.end()) && (!stringMatched))
		{
			i->GoNextState(_testString[testStringPos], newStates, this);
			auto j = i++;
			stateList.erase(j);
		}

		stateList.insert(stateList.end(), newStates.begin(), newStates.end());
		newStates.clear();
		testStringPos++;
	}

	return stringMatched;
}

