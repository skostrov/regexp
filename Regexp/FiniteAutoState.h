#pragma once
#include "Common.h"

class Vertex;

class FiniteAutoState
{
public:
	FiniteAutoState(Vertex* _vertex, const size_t& _stringPos);
	FiniteAutoState(const FiniteAutoState& _state);
	~FiniteAutoState();

	const Vertex* GetAutoPos() const;
	void SetAutoPos(Vertex* _vertex);

	const size_t& GetStringPos() const;
	void SetStringPos(const size_t& _stringPos);

	bool operator ==(const FiniteAutoState& _state) const;

private:
	
	Vertex* autoPos;
	size_t stringPos;
};

