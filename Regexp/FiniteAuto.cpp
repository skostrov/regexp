#include "FiniteAuto.h"
#include "Vertex.h"
#include "Edge.h"

namespace
{
	string GetColor(const Vertex* _vertex)
	{
		switch (_vertex->GetStatus())
		{
		case VertexStatus::Final:
			return "gray67";
		case VertexStatus::Start:
			return "gray93";
		}

		return "";
	}

	/*class SearchVertexByName
	{
	public:

		SearchVertexByName(const string& _name) : name(_name) {}
		bool operator ()(const Vertex* operand)
		{
			return operand->GetName() == name;
		}

	private:

		string name;
	};

	class SearchEdgeBySenderNameAndLabel
	{
	public:

		SearchEdgeBySenderNameAndLabel(const string& _name, const string& _label) : name(_name), label(_label) {}
		bool operator ()(const Edge* operand)
		{
			return ((operand->GetSender()->GetName() == name) && (operand->GetLabel() == label));
		}

	private:

		string name;
		string label;
	};*/
}

FiniteAuto::FiniteAuto()
{
}

FiniteAuto::~FiniteAuto()
{
	for (auto i = vertexList.cbegin(); i != vertexList.cend(); i++)
	{
		delete *i;
	}
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
	
	auto i = _vertex->GetOutEdges().begin();
	while (i != _vertex->GetOutEdges().end())
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

void FiniteAuto::SetDrawer(const Dot& _drawer)
{
	drawer = _drawer;
}

const Dot& FiniteAuto::GetDrawer() const
{
	return drawer;
}

void FiniteAuto::SaveImage(const string& dotExe, const string& dotFile, const string& pngFile)
{
	for (auto i : vertexList)
	{
		drawer.AddVertex(i, "", GetColor(i));
		for (list<Edge*>::const_iterator j = i->GetOutEdges().cbegin(); j != i->GetOutEdges().cend(); j++)
		{
			drawer.AddEdge((*j)->GetSender()->GetName(), (*j)->GetReceiver()->GetName(), (*j)->GetLabel());
		}
	}

	drawer.Plot();
	drawer.SaveDot(dotFile);
	drawer.SaveImage(dotExe, dotFile, pngFile);
}

