#pragma once

#include "Common.h"

class Edge;

class Vertex
{
public:

	enum class EStatus
	{ 
		Start,
		Final,
		Normal 
	};

	typedef list<Edge*> EdgeList;

					Vertex( const EStatus& status = EStatus::Normal );
					Vertex( const Vertex& copy );
					~Vertex();
					
	void			AddEdge( Edge* edge );
	void			RemoveEdge( Edge* edge );

	const EdgeList& GetEdges() const { return outEdges; }

	const EStatus&	GetStatus() const { return status; }
	void			SetStatus( const EStatus& status );

	bool			operator ==( const Vertex& vertex ) const;

private:

	EdgeList		outEdges;
	EStatus			status;
};

