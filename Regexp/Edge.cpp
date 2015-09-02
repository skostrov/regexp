#include "Edge.h"

#include "Vertex.h"

Edge::Edge(Vertex* _sender, Vertex* _receiver, Tag _tag) : sender(_sender), receiver(_receiver), tag(_tag)
{
	sender->AddEdge(this);
}

Edge::Edge(const Edge& _copy) : sender(_copy.sender), receiver(_copy.receiver), tag(_copy.tag)
{
}

Edge::~Edge()
{
}

void Edge::SetSender(Vertex* _sender)
{
	sender = _sender;
}

void Edge::SetReceiver(Vertex* _receiver)
{
	receiver = _receiver;
}

void Edge::SetTag(const Tag& _tag)
{
	tag = _tag;
}
