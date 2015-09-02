#pragma once

#include "Common.h"
#include "Dot.h"
#include "Vertex.h"

class Edge;


class FiniteAuto
{
public:

	FiniteAuto();
	~FiniteAuto();

	Vertex* GetStart() const;

	void AddVertex(const string& _name, const Status& _status = Status::Normal);
	void RemoveVertex(const string& _name);

	void AddEdge(const string& _sender, const string& _receiver, const string& _label);
	void RemoveEdge(const string& _sender, const string& _receiver, const string& _label);

	const list<Vertex*>& GetVertexList() const;

	const list<Vertex*>& GetFinalList() const;

	void SetDrawer(const Dot& _drawer);
	const Dot& GetDrawer() const;

	void SaveImage(const string& dotExe, const string& dotFile, const string& pngFile);

private:

	list<Vertex*> vertexList;
	Vertex* start;
	list<Vertex*> finalList;
	Dot drawer;

	FiniteAuto(const FiniteAuto& _auto);
	void operator =(const FiniteAuto& _auto);
};

