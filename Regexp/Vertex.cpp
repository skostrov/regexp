#include "Vertex.h"

#include "Edge.h"

Vertex::Vertex(const VertexStatus& _status) : status(_status)
{
}

Vertex::Vertex(const Vertex& _copy) : inEdges(_copy.inEdges), outEdges(_copy.outEdges), status(_copy.status)
{
}

Vertex::~Vertex()
{
	for (auto i = outEdges.begin(); i != outEdges.end(); i++)
	{
		delete *i;
	}
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

const list<Edge*>& Vertex::GetInEdges() const
{
	return inEdges;
}

const list<Edge*>& Vertex::GetOutEdges() const
{
	return outEdges;
}

list<Edge*>::const_iterator& Vertex::CInEdgesBegin() const
{
	return inEdges.cbegin();
}

list <Edge*>::const_iterator& Vertex::CInEdgesEnd() const
{
	return inEdges.cend();
}

#pragma region Setters/Getters for inEdges and outEdges lists

list <Edge*>::iterator& Vertex::InEdgesBegin()
{
	return inEdges.begin();
}

list <Edge*>::iterator& Vertex::InEdgesEnd()
{
	return inEdges.end();
}

list<Edge*>::const_iterator& Vertex::COutEdgesBegin() const
{
	return outEdges.cbegin();
}

list <Edge*>::const_iterator& Vertex::COutEdgesEnd() const
{
	return outEdges.cend();
}

list <Edge*>::iterator& Vertex::OutEdgesBegin()
{
	return outEdges.begin();
}

list <Edge*>::iterator& Vertex::OutEdgesEnd()
{
	return outEdges.end();
}

#pragma endregion

const VertexStatus& Vertex::GetStatus() const
{
	return status;
}

void Vertex::SetStatus(const VertexStatus& _status)
{
	status = _status;
}

bool Vertex::operator ==(const Vertex& _vertex) const
{
	return ((status == _vertex.status) && (outEdges == _vertex.outEdges) && (inEdges == _vertex.inEdges));
}

bool Vertex::operator !=(const Vertex& _vertex) const
{
	return ((status != _vertex.status) || (outEdges != _vertex.outEdges) || (inEdges != _vertex.inEdges));
}

