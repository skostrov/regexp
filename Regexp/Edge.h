#pragma once

#include "Common.h"

class Vertex;

class Edge
{
public:
	Edge(Vertex* _sender, Vertex* _receiver, const string& label);
	Edge(const Edge& _copy);
	~Edge();
	
	const Vertex* GetSender() const;
	void SetSender(Vertex* _sender);

	const Vertex* GetReceiver() const;
	void SetReceiver(Vertex* _receiver);

	const string& GetLabel() const;
	void SetLabel(const string& _label);

private:
	Vertex* sender;
	Vertex* receiver;
	string label;
};

