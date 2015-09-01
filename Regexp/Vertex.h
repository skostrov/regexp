#include "Common.h"

class Edge;

enum class Status
{ 
	Start,
	Final,
	Normal 
};

class Vertex
{
public:

	Vertex(const string& _name, const Status& _status = Status::Normal);
	Vertex(const Vertex& _copy);
	~Vertex();

	const string& GetName() const;
	void SetName(const string& _name);

	void AddEdge(Edge* _edge);
	void RemoveEdge(Edge* _edge);

	const list<Edge*>& GetEdges() const;

	const Status& GetStatus() const;
	void SetStatus(const Status& _status);

	bool operator ==(const Vertex& _vertex) const;

private:

	string name;
	list<Edge*> outEdges;
	Status status;
};

