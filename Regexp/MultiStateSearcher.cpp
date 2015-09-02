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

bool MultiStateSearcher::TestMatching(const string& _testString)
{
	Initialize(_testString);

	for (int strIndex = 0; strIndex != _testString.length(); ++strIndex)
	{
		list<FiniteAutoState> newStates;
		list<FiniteAutoState> checkUpStates;

#pragma region Pass all unlabeled edges

		do
		{
			checkUpStates = stateList;
			newStates.clear();
			auto i = stateList.begin();
			while (i != stateList.end())
			{
				if (i->GoEdgesLabeledAs("", newStates))
				{
					auto j = i++;
					stateList.erase(j);
				}
				else
				{
					++i;
				}
			}
			stateList.insert(stateList.end(), newStates.begin(), newStates.end());

		} while (stateList != checkUpStates/*newStates.size()*/);

#pragma endregion


		auto i = stateList.begin();
		while (i != stateList.end())
		{
			i->GoEdgesLabeledAs(string(1, _testString[strIndex]), newStates);
			auto j = i++;
			stateList.erase(j);
		}
		stateList.insert(stateList.end(), newStates.begin(), newStates.end());


#pragma region Pass all unlabeled edges

		do
		{
			checkUpStates = stateList;
			newStates.clear();
			auto i = stateList.begin();
			while (i != stateList.end())
			{
				if (i->GoEdgesLabeledAs("", newStates))
				{
					auto j = i++;
					stateList.erase(j);
				}
				else
				{
					++i;
				}
			}
			stateList.insert(stateList.end(), newStates.begin(), newStates.end());

		} while (stateList != checkUpStates/*newStates.size()*/);

#pragma endregion
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

