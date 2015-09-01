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
		case Status::Normal:
			return "";
		}
	}
}

FiniteAuto::FiniteAuto()
{
}

FiniteAuto::FiniteAuto(const FiniteAuto& _auto) : vertexList(_auto.vertexList)
{
}

FiniteAuto::~FiniteAuto()
{
}

void FiniteAuto::AddVertex(const Vertex& _vertex)
{
	if (find(vertexList.cbegin(), vertexList.cend(), _vertex) == vertexList.cend())
	{
		vertexList.push_back(_vertex);
	}
}

const list<Vertex>& FiniteAuto::GetVertexList() const
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
		drawer.AddVertex(i.GetName(), "", GetColor(i));
		for (list<Edge*>::const_iterator j = i.GetEdges().cbegin(); j != i.GetEdges().cend(); j++)
		{
			drawer.AddEdge((*j)->GetSender()->GetName(), (*j)->GetReceiver()->GetName(), (*j)->GetTag());
		}
	}

	drawer.Plot();
	drawer.SaveDot(dotFile);
	drawer.SaveImage(dotExe, dotFile, pngFile);
}

