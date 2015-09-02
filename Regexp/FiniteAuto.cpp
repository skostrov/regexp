#include "FiniteAuto.h"

#include "Vertex.h"
#include "Edge.h"

//namespace
//{
//	string GetColor(const Vertex& _vertex)
//	{
//		switch (_vertex.GetStatus())
//		{
//		case Status::Final:
//			return "gray67";
//		case Status::Start:
//			return "gray93";
//		}
//
//		return "";
//	}
//}

FiniteAuto::FiniteAuto():
	startVertex( nullptr ),
	finalVertex( nullptr )
{
}

FiniteAuto::FiniteAuto(const FiniteAuto& _auto):
	vertexList(_auto.vertexList),
	startVertex( nullptr ),
	finalVertex( nullptr )
{
	if ( _auto.GetStartVertex() )
	{
		startVertex = new Vertex( _auto.GetStartVertex()->GetStatus() );
	}

	if ( _auto.GetFinalVertex() )
	{
		finalVertex = new Vertex( _auto.GetFinalVertex()->GetStatus() );
	}
}

FiniteAuto::~FiniteAuto()
{
	for ( auto& it : vertexList )
	{
		for ( auto& jt : it->GetEdges() )
		{
			delete jt;
		}

		delete it;
	}
}

Edge* FiniteAuto::AddEdge( Vertex* sender, Vertex* receiver, const Edge::Tag& tag )
{
	auto result = new Edge( sender, receiver, tag );
	return result;
}

Vertex* FiniteAuto::AddVertex( const Vertex::EStatus& vertexStatus )
{
	for ( auto& it : vertexList )
	{
		if ( it->GetStatus() == vertexStatus )
		{
			it->SetStatus( Vertex::EStatus::Normal );
		}
	}

	auto result = new Vertex( vertexStatus );
	vertexList.push_back( result );

	if ( vertexStatus == Vertex::EStatus::Start )
	{
		startVertex = result;
	}
	else if ( vertexStatus == Vertex::EStatus::Final )
	{
		finalVertex = result;
	}

	return result;
}

//void FiniteAuto::SaveImage(const string& dotExe, const string& dotFile, const string& pngFile)
//{
//	for (auto i : vertexList)
//	{
//		drawer.AddVertex(i.GetName(), "", GetColor(i));
//		for (list<Edge*>::const_iterator j = i.GetEdges().cbegin(); j != i.GetEdges().cend(); j++)
//		{
//			drawer.AddEdge((*j)->GetSender()->GetName(), (*j)->GetReceiver()->GetName(), (*j)->GetTag());
//		}
//	}
//
//	drawer.Plot();
//	drawer.SaveDot(dotFile);
//	drawer.SaveImage(dotExe, dotFile, pngFile);
//}
