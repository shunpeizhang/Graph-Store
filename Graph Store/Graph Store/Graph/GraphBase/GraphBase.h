#ifndef __GRAPH_BASE_HEADER_INCLUDED__
#define __GRAPH_BASE_HEADER_INCLUDED__

#include "../../Dynamic Array/DynamicArray.h"
#include "../../Hash/Hash.h"
#include "../../Hash/Hash Function/HashFunctionStringSpecialization.h"
#include "../../Hash/Identifier Accessor/IdentifierAccessor.h"
#include "../Abstract class/Graph.h"

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

	virtual void addVertex(const String& identifier) override;
	virtual void removeVertex(Vertex& vertexToRemove) override;

	virtual Vertex& getVertexWithIdentifier(const String& identifier) override;
	virtual VertexAbstractIterator getIteratorOfVertices() override;
	virtual EdgeAbstractIterator getIteratorOfEdgesStartingFrom(Vertex& vertex) override;
	virtual unsigned getVerticesCount() const override;

protected:
	GraphBase(String identifier);

	bool hasVertexWithIdentifier(const String& identifier);
	Vertex* searchForVertexWithIdentifier(const String& identifier);
	std::unique_ptr<Vertex> createVertex(const String& identifier) const;
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