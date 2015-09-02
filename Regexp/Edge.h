#pragma once

#include "Common.h"

class Vertex;

class Edge
{
public:

	class Tag
	{
		string Label;
	};

					Edge(Vertex* _sender, Vertex* _receiver, Tag _tag);
					Edge(const Edge& _copy);
					~Edge();
	
	const Vertex*	GetSender() const { return sender; }
	void			SetSender(Vertex* sender);

	const Vertex*	GetReceiver() const { return receiver; }
	void			SetReceiver(Vertex* receiver);

	const Tag&		GetTag() const;
	void			SetTag(const Tag& tag);

private:

	Vertex*			sender;
	Vertex*			receiver;
	Tag				tag;
};
