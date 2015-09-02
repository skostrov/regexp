#include "Edge.h"
#include "Vertex.h"


Edge::Edge(Vertex* _sender, Vertex* _receiver, const string& _tag) : sender(_sender), receiver(_receiver), tag(_tag)
{
	sender->AddEdge(this);
}

Edge::Edge(const Edge& _copy) : sender(_copy.sender), receiver(_copy.receiver), tag(_copy.tag)
{
}

Edge::~Edge()
{
}

const Vertex* Edge::GetSender() const
{
	return sender;
}

void Edge::SetSender(Vertex* _sender)
{
	sender = _sender;
}

const Vertex* Edge::GetReceiver() const
{
	return receiver;
}

void Edge::SetReceiver(Vertex* _receiver)
{
	receiver = _receiver;
}

const string& Edge::GetTag() const
{
	return tag;
}

void Edge::SetTag(const string& _tag)
{
	tag = _tag;
}

