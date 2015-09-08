#pragma once
#include "Common.h"
#include "FiniteAuto.h"
#include "Dot.h"

class Vertex;
class Edge;

class GraphicFiniteAuto : public FiniteAuto
{
public:

	GraphicFiniteAuto();
	~GraphicFiniteAuto();

	void SaveImage(const string& dotExe = "C:/Program Files (x86)/Graphviz/bin/dot.exe",
				   const string& dotFile = "./../tests/test.dot",
				   const string& pngFile = "./../tests/test.png");

private:

	Dot drawer;
};

