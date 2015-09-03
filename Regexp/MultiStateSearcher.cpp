#include "MultiStateSearcher.h"
#include "FiniteAuto.h"
#include "FiniteAutoState.h"


MultiStateSearcher::MultiStateSearcher(FiniteAuto* _auto) : automaton(_auto)
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

list<FiniteAutoState>& MultiStateSearcher::GetStateList()
{
	return stateList;
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
	stateList.clear();
	stateList.push_back(FiniteAutoState(automaton->GetStart()));
}

void MultiStateSearcher::PassUnlabeledEdges(list<FiniteAutoState>& _newStates, list<FiniteAutoState>& _oldStates)
{
	do
	{
		_oldStates = stateList;
		_newStates.clear();
		auto i = stateList.begin();
		while (i != stateList.end())
		{
			if (i->GoEdgesLabeledAs("", _newStates))
			{
				auto j = i++;
				stateList.erase(j);
			}
			else
			{
				++i;
			}
		}
		stateList.insert(stateList.end(), _newStates.begin(), _newStates.end());

	} while (stateList != _oldStates);
}

bool MultiStateSearcher::TestMatching(const string& _testString)
{
	Initialize(_testString);

	list<FiniteAutoState> newStates;
	list<FiniteAutoState> oldStates;

	PassUnlabeledEdges(newStates, oldStates);

	for (int strIndex = 0; strIndex != _testString.length(); ++strIndex)
	{
		newStates.clear();
		oldStates.clear();

		auto i = stateList.begin();
		while (i != stateList.end())
		{
			i->GoEdgesLabeledAs(string(1, _testString[strIndex]), newStates);
			auto j = i++;
			stateList.erase(j);
		}
		stateList.insert(stateList.end(), newStates.begin(), newStates.end());

		PassUnlabeledEdges(newStates, oldStates);
	}

	return CheckFinalState();
}

bool MultiStateSearcher::CheckFinalState() const
{
	for (auto i : stateList)
	{
		if (i.GetAutoPos()->GetStatus() == Status::Final)
		{
			return true;
		}
	}

	return false;
}

