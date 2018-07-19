#ifndef __GRAPH_BASE_HEADER_INCLUDED__
#define __GRAPH_BASE_HEADER_INCLUDED__

#include "DynamicArray.h"
#include "Hash.h"
#include "HashFunctionStringSpecialization.h"
#include "IdentifierAccessor.h"
#include "Graph.h"

class GraphBase : public Graph
{
	typedef Hash<Vertex, String, IdentifierAccessor> Hash;
	typedef DynamicArray<Vertex*> Array;
	typedef DynamicArrayIterator<Vertex*> VertexConcreteIterator;
	typedef LinkedListIterator<Edge> EdgeConcreteIterator;

public:
	GraphBase(const GraphBase&) = delete;
	GraphBase& operator=(const GraphBase&) = delete;
	virtual ~GraphBase();

	virtual void addVertex(const char* identifier) override;
	virtual void removeVertex(Vertex& vertexToRemove) override;

	virtual Vertex& getVertexWithIdentifier(const char* identifier) override;
	virtual VertexAbstractIterator getIteratorOfVertices() override;
	virtual EdgeAbstractIterator getIteratorOfEdgesStartingFrom(Vertex& vertex) override;
	virtual unsigned getVerticesCount() const override;

protected:
	GraphBase(String identifier);

	bool hasVertexWithIdentifier(const char* identifier);
	Vertex* searchForVertexWithIdentifier(const char* identifier);
	std::unique_ptr<Vertex> createVertex(const char* identifier) const;
	void addVertexToCollection(std::unique_ptr<Vertex> vertex);
	virtual void removeEdgesEndingIn(Vertex& vertex);
	virtual void removeEdgesStartingFrom(Vertex& vertex);
	void removeVertexFromCollection(const Vertex& vertexToRemove);
	void destroyVertex(Vertex* vertex) const;
	bool hasEdgeFromTo(Vertex& startVertex, const Vertex& endVertex);
	void addEdgeFromToWithWeight(Vertex& startVertex, Vertex& endVertex, unsigned weight);
	void removeEdgeFromTo(Vertex& startVertex, const Vertex& endVertex);
	bool isOwnerOf(const Vertex& vertex) const;

private:
	EdgeConcreteIterator searchForEdgeFromTo(Vertex& startVertex, const Vertex& endVertex);
	EdgeConcreteIterator getConcreteIteratorOfEdgesStartingFrom(Vertex& vertex);
	LinkedList<Edge>& getEdgesStartingFrom(Vertex& vertex);
	VertexConcreteIterator getConcreteIteratorOfVertices();
	void destroyAllVertices();

private:
	static const size_t INITIAL_COLLECTION_SIZE = 16;

private:
	Array vertices;
	Hash vertexSearchSet;
};

#endif //__GRAPH_BASE_HEADER_INCLUDED__