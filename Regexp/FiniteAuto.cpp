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

	class SearchVertexByName
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
	if (find_if(vertexList.cbegin(), vertexList.cend(), SearchVertexByName(_name)) == vertexList.cend())
	{
		Vertex* newVertex = new Vertex(_name, _status);
		vertexList.push_back(newVertex);
		if (_status == Status::Start)
		{
			start = newVertex;
		}
	}
}

void FiniteAuto::RemoveVertex(const string& _name)
{
	Vertex* pVertex = *find_if(vertexList.cbegin(), vertexList.cend(), SearchVertexByName(_name));

	auto i = pVertex->GetInEdges().begin();
	while (i != pVertex->GetInEdges().end())
	{
		auto j = i;
		++i;
		RemoveEdge((*j)->GetSender()->GetName(), _name, (*j)->GetLabel());
	}
	
	auto k = pVertex->GetOutEdges().begin();
	while (k != pVertex->GetOutEdges().end())
	{
		auto l = k;
		++k;
		RemoveEdge(_name, (*l)->GetReceiver()->GetName(), (*l)->GetLabel());
	}

	vertexList.remove(pVertex);

	delete pVertex;
}

void FiniteAuto::AddEdge(const string& _sender, const string& _receiver, const string& _label)
{
	Vertex* senderVertex = *find_if(vertexList.cbegin(), vertexList.cend(), SearchVertexByName(_sender));
	Vertex* receiverVertex = *find_if(vertexList.cbegin(), vertexList.cend(), SearchVertexByName(_receiver));

	Edge* newEdge = new Edge(senderVertex, receiverVertex, _label);

	senderVertex->AddOutEdge(newEdge);
	receiverVertex->AddInEdge(newEdge);
}

void FiniteAuto::RemoveEdge(const string& _sender, const string& _receiver, const string& _label)
{
	Vertex* pSender = *find_if(vertexList.cbegin(), vertexList.cend(), SearchVertexByName(_sender));
	Vertex* pReceiver = *find_if(vertexList.cbegin(), vertexList.cend(), SearchVertexByName(_receiver));

	Edge* pEdge = *find_if(pSender->GetOutEdges().cbegin(), pSender->GetOutEdges().cend(), SearchEdgeBySenderNameAndLabel(pSender->GetName(), _label));

	pSender->RemoveOutEdge(pEdge);
	pReceiver->RemoveInEdge(pEdge);

	delete pEdge;
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
		for (list<Edge*>::const_iterator j = i->GetOutEdges().cbegin(); j != i->GetOutEdges().cend(); j++)
		{
			drawer.AddEdge((*j)->GetSender()->GetName(), (*j)->GetReceiver()->GetName(), (*j)->GetLabel());
		}
	}

	drawer.Plot();
	drawer.SaveDot(dotFile);
	drawer.SaveImage(dotExe, dotFile, pngFile);
}

