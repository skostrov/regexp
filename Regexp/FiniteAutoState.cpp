#include "FiniteAutoState.h"
#include "Vertex.h"
#include "Edge.h"
#include "MultiStateSearcher.h"


FiniteAutoState::FiniteAutoState(Vertex* _vertex) : autoPos(_vertex)
{
}

FiniteAutoState::FiniteAutoState(const FiniteAutoState& _state) : autoPos(_state.autoPos)
{

}

FiniteAutoState::~FiniteAutoState()
{
}

Vertex* FiniteAutoState::GetAutoPos() const
{
	return autoPos;
}

void FiniteAutoState::SetAutoPos(Vertex* _vertex)
{
	autoPos = _vertex;
}

bool FiniteAutoState::operator ==(const FiniteAutoState& _state) const
{
	return autoPos == _state.autoPos;
}

void FiniteAutoState::GoNextState(const char& _symbol, list<FiniteAutoState>& _stateList, MultiStateSearcher* _searcher)
{
	if ((_searcher->GetTestString().size() == _searcher->GetTestStringPos()) && (autoPos->GetStatus() == Status::Final))
	{
		_searcher->SetStringMatched(true);
	}
	else
	{
		for (auto i = autoPos->GetOutEdges().begin(); i != autoPos->GetOutEdges().end(); ++i)
		{
			if ((*i)->GetLabel() == string(1, _symbol))
			{
				_stateList.push_back(FiniteAutoState((*i)->GetReceiver()));
			}
			else if ((*i)->GetLabel() == "")
			{
				_searcher->GetStateList().push_back(FiniteAutoState((*i)->GetReceiver()));
				_searcher->GetStateList().insert(_searcher->GetStateList().end(), _stateList.begin(), _stateList.end());
				_stateList.clear();
			}
		}
	}
}

