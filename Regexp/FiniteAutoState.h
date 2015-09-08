#pragma once
#include "Common.h"

class MultiStateSearcher;
class Vertex;

class FiniteAutoState
{
public:

	FiniteAutoState(Vertex* _vertex);
	FiniteAutoState(const FiniteAutoState& _state);
	~FiniteAutoState();

	Vertex* GetAutoPos() const;
	void SetAutoPos(Vertex* _vertex);

	bool operator ==(const FiniteAutoState& _state) const;

	bool GoEdgesLabeledAs(const string& _label, list<FiniteAutoState>& _stateList);

private:
	
	Vertex* autoPos;

};

