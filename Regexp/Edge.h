#pragma once

#include "Common.h"

class Vertex;

class Edge
{
public:
	Edge(Vertex* _sender, Vertex* _receiver, string _tag);
	Edge(const Edge& _copy);
	~Edge();
	
	const Vertex* GetSender() const;
	void SetSender(Vertex* _sender);

	const Vertex* GetReceiver() const;
	void SetReceiver(Vertex* _receiver);

	const string& GetTag() const;
	void SetTag(const string& _tag);

private:
	Vertex* sender;
	Vertex* receiver;
	string tag;
};

