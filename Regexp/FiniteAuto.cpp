#include "FiniteAuto.h"
#include "Edge.h"


FiniteAuto::FiniteAuto()
{
}

FiniteAuto::~FiniteAuto()
{
	for (auto& i : vertexList)
	{
		delete i;
	}

	vertexList.clear();
	finalList.clear();
	start = nullptr;
}

Vertex* FiniteAuto::GetStart() const
{
	return start;
}

Vertex* FiniteAuto::AddVertex(const VertexStatus& _status)
{
	Vertex* newVertex = new Vertex(_status);

	vertexList.push_back(newVertex);

	if (_status == VertexStatus::Start)
	{
		start = newVertex;
	}

	if (_status == VertexStatus::Final)
	{
		finalList.push_back(newVertex);
	}

	return newVertex;
}

void FiniteAuto::RemoveVertex(Vertex* _vertex)
{
	auto i = _vertex->InEdgesBegin();

	while (i != _vertex->InEdgesEnd())
	{
		auto previous = i;
		++i;
		RemoveEdge(*previous);
	}

	vertexList.remove(_vertex);

	delete _vertex;
}

Edge* FiniteAuto::AddEdge(Vertex* _sender, Vertex* _receiver, const string& _label)
{
	Edge* newEdge = new Edge(_sender, _receiver, _label);

	_sender->AddOutEdge(newEdge);
	_receiver->AddInEdge(newEdge);

	return newEdge;
}

void FiniteAuto::RemoveEdge(Vertex* _sender, Vertex* _receiver, const string& _label)
{
	Edge* pEdge = *find_if(_sender->COutEdgesBegin(), _sender->COutEdgesEnd(), [_label](const Edge* _edge) { return _edge->GetLabel() == _label; });

	_sender->RemoveOutEdge(pEdge);
	_receiver->RemoveInEdge(pEdge);

	delete pEdge;
}

void FiniteAuto::RemoveEdge(Edge* _edge)
{
	_edge->GetSender()->RemoveOutEdge(_edge);
	_edge->GetReceiver()->RemoveInEdge(_edge);

	delete _edge;
}

const list<Vertex*>& FiniteAuto::GetVertexList() const
{
	return vertexList;
}

const list<Vertex*>& FiniteAuto::GetFinalList() const
{
	return finalList;
}

