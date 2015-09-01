#include "Vertex.h"


Vertex::Vertex(const string& _name, const Status& _status) : name(_name), status(_status)
{
}

Vertex::Vertex(const Vertex& _copy) : name(_copy.name), outEdges(_copy.outEdges), status(_copy.status)
{
}

Vertex::~Vertex()
{
}

const string& Vertex::GetName() const
{
	return name;
}

void Vertex::SetName(const string& _name)
{
	name = _name;
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

const list<Edge*>& Vertex::GetEdges() const
{
	return outEdges;
}

const Status& Vertex::GetStatus() const
{
	return status;
}

void Vertex::SetStatus(const Status& _status)
{
	status = _status;
}

bool Vertex::operator ==(const Vertex& _vertex) const
{
	return ((status == _vertex.status) && (outEdges == _vertex.outEdges));
}

