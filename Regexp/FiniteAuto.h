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
	void AddEdge(const string& _sender, const string& _receiver, const string& label);

	const list<Vertex*>& GetVertexList() const;

	void SetDrawer(const Dot& _drawer);
	const Dot& GetDrawer() const;

	void SaveImage(const string& dotExe, const string& dotFile, const string& pngFile);

private:

	Vertex* start;
	list<Vertex*> vertexList;
	Dot drawer;

	FiniteAuto(const FiniteAuto& _auto);
	void operator =(const FiniteAuto& _auto);
};

