#include "Vertex.h"

#include "Edge.h"

Vertex::Vertex(const string& _name, const Status& _status) : name(_name), status(_status)
{
}

Vertex::Vertex(const Vertex& _copy) : name(_copy.name), inEdges(_copy.inEdges), outEdges(_copy.outEdges), status(_copy.status)
{
}

Vertex::~Vertex()
{
	for (auto i = outEdges.begin(); i != outEdges.end(); i++)
	{
		delete *i;
	}
}

const string& Vertex::GetName() const
{
	return name;
}

void Vertex::SetName(const string& _name)
{
	name = _name;
}

void Vertex::AddOutEdge(Edge* _edge)
{
	if (find(outEdges.cbegin(), outEdges.cend(), _edge) == outEdges.cend())
	{
		outEdges.push_back(_edge);
	}
}

void Vertex::RemoveOutEdge(Edge* _edge)
{
	outEdges.remove(_edge);
}

void Vertex::AddInEdge(Edge* _edge)
{
	if (find(inEdges.cbegin(), inEdges.cend(), _edge) == inEdges.cend())
	{
		inEdges.push_back(_edge);
	}
}

void Vertex::RemoveInEdge(Edge* _edge)
{
	inEdges.remove(_edge);
}

const list<Edge*>& Vertex::GetOutEdges() const
{
	return outEdges;
}

const list<Edge*>& Vertex::GetInEdges() const
{
	return inEdges;
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
	return ((status == _vertex.status) && (outEdges == _vertex.outEdges) && (inEdges == _vertex.inEdges));
}

