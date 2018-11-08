#ifndef __UNDIRECTED_GRAPH_HEADER_INCLUDED__
#define __UNDIRECTED_GRAPH_HEADER_INCLUDED__

#include "../Abstract class/Graph.h"

class UndirectedGraph : public Graph
{
public:
	explicit UndirectedGraph(const String& id);

	virtual void addEdge(Vertex& start, Vertex& end, OutgoingEdge::Weight weight) override;
	virtual void removeEdge(Vertex& start, Vertex& end) override;

protected:
	virtual void removeEdgesEndingIn(Vertex& v) override;

private:
	void tryToAddUndirectedEdge(Vertex& start, Vertex& end, OutgoingEdge::Weight weight);
};

#endif //__UNDIRECTED_GRAPH_HEADER_INCLUDED__