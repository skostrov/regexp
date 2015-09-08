#include "Dot.h"

namespace
{
	bool StartProcess(const char* path, char* attributes)
	{
		STARTUPINFOA cif;
		memset(&cif, NULL, sizeof(STARTUPINFOA));
		PROCESS_INFORMATION pi;

		return 0 != CreateProcessA(path, attributes,
			NULL, NULL, FALSE, NULL, NULL, NULL, &cif, &pi) ;
	}
}

Dot::Dot()
{
}

Dot::~Dot()
{
}

void Dot::AddVertex(const string& name, const string& label, const string& color)
{
	vertexes.push_back(Vertex { name, label, color });
}

void Dot::AddEdge(const string& firstVertexName, const string& secondVertexName, const string& label)
{
	edges.push_back(Edge { firstVertexName, secondVertexName, label });
}

void Dot::Clear()
{
	dot.clear();
	vertexes.clear();
	edges.clear();
}

void Dot::Plot()
{
	dot = "digraph\n{\n";

	for (const auto& it : vertexes)
	{
		dot += it.Name + " [ label = \"" + it.Label + "\"" +
			((it.Color.empty()) ? "" : (", style = filled, color = " + it.Color)) +" ]; \n";
	}

	for (const auto& it : edges)
	{
		dot += it.V1Name + " -> " + it.V2Name + " [ label = \"" + it.Label + "\" ]; \n";
	}

	dot += "}";
}

void Dot::SaveDot(const string& dotFile)
{
    ofstream out(dotFile);
    out << dot;
    out.close();
}

void Dot::SaveImage(const string& dotExe, const string& dotFile, const string& pngFile)
{
	string attributes = "\"" + dotExe + "\"" + " " + "\"" + dotFile + "\"" + " -Tpng -o" + "\"" + pngFile + "\"";
	char* atc = new char[attributes.length() + 1];
	strcpy(atc, attributes.c_str());

	bool result = StartProcess(dotExe.c_str(), atc);

	delete atc;
}