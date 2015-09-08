#pragma once

#include "Common.h"

class Edge;

enum class VertexStatus
{ 
	Start,
	Final,
	Normal 
};

class Vertex
{
public:

	Vertex(const VertexStatus& _status = VertexStatus::Normal);
	Vertex(const Vertex& _copy);
	~Vertex();

	void AddOutEdge(Edge* _edge);
	void RemoveOutEdge(Edge* _edge);

	void AddInEdge(Edge* _edge);
	void RemoveInEdge(Edge* _edge);

	const list<Edge*> GetInEdges() const;
	const list<Edge*> GetOutEdges() const;

	list<Edge*>::const_iterator CInEdgesBegin() const;
	list <Edge*>::const_iterator CInEdgesEnd() const;

	list <Edge*>::iterator InEdgesBegin();
	list <Edge*>::iterator InEdgesEnd();
	
	list<Edge*>::const_iterator COutEdgesBegin() const;
	list <Edge*>::const_iterator COutEdgesEnd() const;

	list <Edge*>::iterator OutEdgesBegin();
	list <Edge*>::iterator OutEdgesEnd();

	const VertexStatus& GetStatus() const;
	void SetStatus(const VertexStatus& _status);

	bool operator ==(const Vertex& _vertex) const;
	bool operator !=(const Vertex& _vertex) const;

private:

	list<Edge*> inEdges;
	list<Edge*> outEdges;
	VertexStatus status;

};

