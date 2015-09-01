#include "Vertex.h"


Vertex::Vertex(const Status& _status) : status(_status)
{
}

Vertex::Vertex(const Vertex& _copy) : outEdges(_copy.outEdges), status(_copy.status)
{
}

Vertex::~Vertex()
{
}

void Vertex::AddEdge(Edge* _edge)
{
	if (find(outEdges.cbegin(), outEdges.cend(), _edge) == outEdges.cend())
	{
		outEdges.push_back(_edge);
	}
}

void Vertex::RemoveEdge(Edge* _edge)
{
	outEdges.remove(_edge);
}

const Status& Vertex::GetStatus() const
{
	return status;
}

void Vertex::SetStatus(const Status& _status)
{
	status = _status;
}

