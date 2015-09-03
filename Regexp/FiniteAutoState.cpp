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

bool FiniteAutoState::GoEdgesLabeledAs(const string& _label, list<FiniteAutoState>& _stateList)
{
	bool result = false;

	if (autoPos->GetOutEdges().size())
	{
		result = true;

		for (auto i = autoPos->GetOutEdges().begin(); i != autoPos->GetOutEdges().end(); ++i)
		{
			if ((*i)->GetLabel() == _label)
			{
				_stateList.push_back(FiniteAutoState((*i)->GetReceiver()));
			}
			else
			{
				result = false;
			}
		}
	}

	return result;
}

