#include "FiniteAuto.h"
#include "Vertex.h"
#include "Edge.h"

namespace
{
	string GetColor(const Vertex& _vertex)
	{
		switch (_vertex.GetStatus())
		{
		case Status::Final:
			return "gray67";
		case Status::Start:
			return "gray93";
		}

		return "";
	}

	class SearchByName
	{
	public:

		SearchByName(const string& _name) : name(_name) {}
		bool operator ()(const Vertex* operand)
		{
			return operand->GetName() == name;
		}

	private:

		string name;
	};
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

void FiniteAuto::AddVertex(const string& _name, const Status& _status)
{
	if (find_if(vertexList.cbegin(), vertexList.cend(), SearchByName(_name)) == vertexList.cend())
	{
		Vertex* newVertex = new Vertex(_name, _status);
		vertexList.push_back(newVertex);
		if (_status == Status::Start)
		{
			start = newVertex;
		}
	}
}

void FiniteAuto::AddEdge(const string& _sender, const string& _receiver, const string& label)
{
	Vertex* senderVertex = *find_if(vertexList.cbegin(), vertexList.cend(), SearchByName(_sender));
	Edge* newEdge = new Edge(senderVertex, *find_if(vertexList.cbegin(), vertexList.cend(), SearchByName(_receiver)), label);
	senderVertex->AddEdge(newEdge);
}

const list<Vertex*>& FiniteAuto::GetVertexList() const
{
	return vertexList;
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
		drawer.AddVertex(i->GetName(), "", GetColor(*i));
		for (list<Edge*>::const_iterator j = i->GetEdges().cbegin(); j != i->GetEdges().cend(); j++)
		{
			drawer.AddEdge((*j)->GetSender()->GetName(), (*j)->GetReceiver()->GetName(), (*j)->GetLabel());
		}
	}

	drawer.Plot();
	drawer.SaveDot(dotFile);
	drawer.SaveImage(dotExe, dotFile, pngFile);
}

