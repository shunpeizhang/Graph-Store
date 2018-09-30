#ifndef __DIJKSTRA_ALGORITHM_HEADER_INCLUDED__
#define __DIJKSTRA_ALGORITHM_HEADER_INCLUDED__

#include "../Abstract class/ShortestPathAlgorithm.h"
#include "../../Priority Queue/PriorityQueue.h"
#include <unordered_map>

class DijkstraAlgorithm : public ShortestPathAlgorithm
{
	struct DijkstraVertex : public DecoratedVertex
	{
		DijkstraVertex(const Vertex& originalVertex) :
			DecoratedVertex(originalVertex)
		{
		}

		PriorityQueueHandle handle;
	};

	class KeyAccessor
	{
	public:
		const Distance& getKeyOf(const DijkstraVertex& v) const
		{
			return v.distanceToSource;
		}

		void setKeyOfWith(DijkstraVertex& v, const Distance& d) const
		{
			v.distanceToSource = d;
		}
	};

	class HandleUpdator
	{
	public:
		void operator()(DijkstraVertex& v, const PriorityQueueHandle& h) const
		{
			v.handle = h;
		}
	};

	typedef PriorityQueue<DijkstraVertex*, Less, Distance, KeyAccessor, HandleUpdator> PriorityQueue;
	typedef std::unordered_map<String, DijkstraVertex, HashFunction<String>> Hash;

	class HashIterator
	{
	public:
		HashIterator(const Hash::iterator& iterator) :
			iterator(iterator)
		{
		}

		HashIterator& operator++()
		{
			++iterator;

			return *this;
		}

		DijkstraVertex* operator*() const
		{
			return &(iterator->second);
		}

	private:
		Hash::iterator iterator;
	};

public:
	explicit DijkstraAlgorithm(const String& id);
	DijkstraAlgorithm(const DijkstraAlgorithm&) = delete;
	DijkstraAlgorithm& operator=(const DijkstraAlgorithm&) = delete;

	virtual Path findShortestPath(const Graph& graph,
								  const Vertex& source,
								  const Vertex& target) override;
private:
	virtual void addDecoratedVersionOf(const Vertex& vertex) override;
	virtual DijkstraVertex& getDecoratedVersionOf(const Vertex& vertex) override;
	void initialiseAlgorithm(const Graph& graph, const Vertex& source);
	void gatherDecoratedVerticesWithUndeterminedEstimate();
	void relaxEdgesLeaving(const DijkstraVertex& vertex, const Graph& graph);
	void relaxEdge(const DijkstraVertex& start, DijkstraVertex& end, unsigned weight);
	void cleanUpAlgorithmState();

private:
	PriorityQueue undeterminedEstimateVertices;
	Hash decoratedVertices;
};

#endif //__DIJKSTRA_ALGORITHM_HEADER_INCLUDED__