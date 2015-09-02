#pragma once

#include "Common.h"
#include "Dot.h"

class Vertex;
class Edge;


class FiniteAuto
{
public:

	FiniteAuto();
	FiniteAuto(const FiniteAuto& _auto);
	~FiniteAuto();

	Vertex* GetStart() const;

	void AddVertex(Vertex& _vertex);
	void AddEdge();

	const list<Vertex>& GetVertexList() const;

	void SetDrawer(const Dot& _drawer);
	const Dot& GetDrawer() const;

	void SaveImage(const string& dotExe, const string& dotFile, const string& pngFile);

private:

	Vertex* start;
	list<Vertex> vertexList;
	Dot drawer;
};

