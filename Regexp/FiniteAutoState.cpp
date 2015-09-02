#include "FiniteAutoState.h"


FiniteAutoState::FiniteAutoState(Vertex* _vertex, const size_t& _stringPos) : autoPos(_vertex), stringPos(_stringPos)
{
}

FiniteAutoState::FiniteAutoState(const FiniteAutoState& _state) : autoPos(_state.autoPos), stringPos(_state.stringPos)
{

}

FiniteAutoState::~FiniteAutoState()
{
}

const Vertex* FiniteAutoState::GetAutoPos() const
{
	return autoPos;
}

void FiniteAutoState::SetAutoPos(Vertex* _vertex)
{
	autoPos = _vertex;
}

const size_t& FiniteAutoState::GetStringPos() const
{
	return stringPos;
}

void FiniteAutoState::SetStringPos(const size_t& _stringPos)
{
	stringPos = _stringPos;
}

bool FiniteAutoState::operator ==(const FiniteAutoState& _state) const
{
	return ((autoPos == _state.autoPos) && (stringPos == _state.stringPos));
}

