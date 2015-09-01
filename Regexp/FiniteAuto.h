#include "Common.h"

class Vertex;
class Edge;

class FiniteAuto
{
public:
	FiniteAuto();
	FiniteAuto(const FiniteAuto& _auto);
	~FiniteAuto();

	void AddVertex(const Vertex& _vertex);

	const list<Vertex>& GetVertexList() const;

private:
	list<Vertex> vertexList;
};

