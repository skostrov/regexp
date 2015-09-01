//#include "Common.h"
#include "Dot.h"

class Vertex;
class Edge;


class FiniteAuto
{
public:

	FiniteAuto();
	FiniteAuto(const FiniteAuto& _auto);
	~FiniteAuto();

	void AddVertex(const Vertex& _vertex);

	const list<Vertex>& GetVertexList() const;

	void SetDrawer(const Dot& _drawer);
	const Dot& GetDrawer() const;

	void SaveImage(const string& dotExe, const string& dotFile, const string& pngFile);

private:

	list<Vertex> vertexList;
	//Dot drawer;
};

