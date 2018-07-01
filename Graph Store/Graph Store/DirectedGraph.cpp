#include "stdafx.h"
#include "DirectedGraph.h"

GraphRegistrator<DirectedGraph> DirectedGraph::registrator("directed");

DirectedGraph::DirectedGraph(const char* identifier) :
	GraphBase(identifier)
{
}

void DirectedGraph::addEdgeBetweenWithWeight(Vertex& startVertex, Vertex& endVertex, unsigned weight)
{
	assert(isOwnerOf(startVertex));
	assert(isOwnerOf(endVertex));

	if (!hasEdgeFromTo(startVertex, endVertex))
	{
		addEdgeFromToWithWeight(startVertex, endVertex, weight);
	}
	else
	{
		throw std::logic_error("There already is such an edge in the graph!");
	}
}

void DirectedGraph::removeEdgeBetween(Vertex& startVertex, Vertex& endVertex)
{
	assert(isOwnerOf(startVertex));
	assert(isOwnerOf(endVertex));

	removeEdgeFromTo(startVertex, endVertex);
}
