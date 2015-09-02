#pragma once

#include "Common.h"

#include "Vertex.h"
#include "Edge.h"

class FiniteAuto
{
public:

	typedef list<Vertex*> VertexList;

					FiniteAuto();
					FiniteAuto( const FiniteAuto& _auto );
	virtual			~FiniteAuto();

	Vertex*			AddVertex( const Vertex::EStatus& vertexStatus );
	Edge*			AddEdge( Vertex* sender, Vertex* receiver, const Edge::Tag& tag );

	const VertexList& GetVertexList() const { return vertexList; }
	Vertex*			GetStartVertex() const { return startVertex; }
	Vertex*			GetFinalVertex() const { return finalVertex; }
	
private:

	VertexList		vertexList;
	Vertex*			startVertex;
	Vertex*			finalVertex;
};
