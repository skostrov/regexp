#include "GraphicFiniteAuto.h"
#include "Vertex.h"
#include "Edge.h"

namespace
{
	string GetVertexColor(const Vertex* _vertex)
	{
		switch (_vertex->GetStatus())
		{

		case VertexStatus::Start:
			return "gray67";
			break;

		case VertexStatus::Final:
			return "gray86";
			break;

		default:
			return "";
			break;
		}
	}

	string GetVertexName(const Vertex* _vertex)
	{
		return "V" + to_string((int)_vertex);
	}
}

GraphicFiniteAuto::GraphicFiniteAuto()
{
	drawer = Dot();
}


GraphicFiniteAuto::~GraphicFiniteAuto()
{
}

void GraphicFiniteAuto::SaveImage(const string& _dotExe, const string& _dotFile, const string& _pngFile)
{
	for (const auto& i : vertexList)
	{
		drawer.AddVertex(GetVertexName(i), "", GetVertexColor(i));

		for (const auto& j : i->GetOutEdges())
		{
			drawer.AddEdge(GetVertexName(j->GetSender()), GetVertexName(j->GetReceiver()), j->GetLabel());
		}
	}

	drawer.Plot();
	drawer.SaveDot(_dotFile);
	drawer.SaveImage(_dotExe, _dotFile, _pngFile);
}

