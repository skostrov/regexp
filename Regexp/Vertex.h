#include "Common.h"

class Edge;

enum class Status { Start, Final, Normal };

class Vertex
{
public:
	Vertex(const Status& _status = Status::Normal);
	Vertex(const Vertex& _copy);
	~Vertex();

	void AddEdge(Edge* _edge);
	void RemoveEdge(Edge* _edge);

	const Status& GetStatus() const;
	void SetStatus(const Status& _status);

private:
	list<Edge*> outEdges;
	Status status;
};

