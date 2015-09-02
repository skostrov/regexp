#include "Edge.h"
#include "Vertex.h"


Edge::Edge(Vertex* _sender, Vertex* _receiver, const string& _label) : sender(_sender), receiver(_receiver), label(_label)
{
	sender->AddOutEdge(this);
}

Edge::Edge(const Edge& _copy) : sender(_copy.sender), receiver(_copy.receiver), label(_copy.label)
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

const string& Edge::GetLabel() const
{
	return label;
}

void Edge::SetLabel(const string& _label)
{
	label = _label;
}

