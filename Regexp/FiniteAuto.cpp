#include "FiniteAuto.h"


FiniteAuto::FiniteAuto()
{
}

FiniteAuto::FiniteAuto(const FiniteAuto& _auto) : vertexList(_auto.vertexList)
{
}

FiniteAuto::~FiniteAuto()
{
}

void FiniteAuto::AddVertex(const Vertex& _vertex)
{
	if (find(vertexList.cbegin(), vertexList.cend(), _vertex) == vertexList.cend())
	{
		vertexList.push_back(_vertex);
	}
}

const list<Vertex>& FiniteAuto::GetVertexList() const
{
	return vertexList;
}

