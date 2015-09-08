#pragma once

#include "Common.h"
#include "Vertex.h"

class Edge;

class FiniteAuto
{
public:

	FiniteAuto();
	virtual ~FiniteAuto();

	Vertex* GetStart() const;

	Vertex* AddVertex(const VertexStatus& _status = VertexStatus::Normal);
	void RemoveVertex(Vertex* _veretex);

	Edge* AddEdge(Vertex* _sender, Vertex* _receiver, const string& _label);
	void RemoveEdge(Vertex* _sender, Vertex* _receiver, const string& _label);
	void RemoveEdge(Edge* _edge);

	const list<Vertex*>& GetVertexList() const;
	const list<Vertex*>& GetFinalList() const;

protected:

	list<Vertex*> vertexList;
	Vertex* start;
	list<Vertex*> finalList;

};

