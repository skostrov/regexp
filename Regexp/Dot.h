#pragma once

#include "Common.h"

class Dot
{
public:

	struct Vertex
	{
		string Name;
		string Label;
		string Color;
	};

	struct Edge
	{
		string V1Name;
		string V2Name;
		string Label;
	};

					Dot();
					~Dot();

	void			AddVertex( const string& name, const string& label, const string& color = "" );
	void			AddEdge( const string& firstVertexName, const string& secondVertexName, const string& label = "" );
	void			Clear();

	void			Plot();
	void			SaveDot( const string& dotFile );
	void			SaveImage( const string& dotExe, const string& dotFile, const string& pngFile );

private:

	list<Vertex>	vertexes;
	list<Edge>		edges;

	string			dot;
};

