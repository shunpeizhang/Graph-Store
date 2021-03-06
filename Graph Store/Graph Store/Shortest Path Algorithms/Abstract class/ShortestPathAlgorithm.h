#ifndef __SHORTEST_PATH_ALGORITHM_HEADER_INCLUDED__
#define __SHORTEST_PATH_ALGORITHM_HEADER_INCLUDED__

#include "../../String/String.h"
#include "../../Distance/Distance.h"
#include <forward_list>

class Vertex;
class Graph;

class ShortestPathAlgorithm
{
protected:
	struct DecoratedVertex
	{
		DecoratedVertex(const Vertex& originalVertex) :
			originalVertex(originalVertex),
			parent(nullptr),
			distanceToSource(Distance::getInfinity())
		{
		}

		const Vertex& originalVertex;
		const DecoratedVertex* parent;
		Distance distanceToSource;
	};

public:
	class Path
	{
		friend class ShortestPathAlgorithm;

	public:
		Path(const Path&) = default;
		Path& operator=(const Path&) = default;
		Path(Path&& source);
		Path& operator=(Path&& rhs);
		~Path() = default;

		void print(std::ostream& out) const;

	private:
		static bool existsPathBetween(const DecoratedVertex& source, const DecoratedVertex& target);

	private:
		Path(const DecoratedVertex& source, const DecoratedVertex& target);

		void collectIdentifiersOnThePath(const DecoratedVertex& target);
		void printIdentifiers(std::ostream& out) const;
		void printLength(std::ostream& out) const;
		void swapContentsWith(Path p);

	private:
		std::forward_list<String> identifiers;
		Distance length;
	};

public:
	virtual ~ShortestPathAlgorithm() = default;

	Path findShortestPath(const Graph& graph, const Vertex& source, const Vertex& target);
	const String& getID() const;

protected:
	static void initialiseSource(DecoratedVertex& source);

protected:
	ShortestPathAlgorithm(const String& id);
	ShortestPathAlgorithm(const ShortestPathAlgorithm&) = default;
	ShortestPathAlgorithm& operator=(const ShortestPathAlgorithm&) = default;

	virtual void initialise(const Graph& graph, const Vertex& source, const Vertex& target) = 0;
	virtual void execute(const Graph& graph, const Vertex& source, const Vertex& target) = 0;
	virtual void cleanUp() = 0;
	virtual void addDecoratedVersionOf(const Vertex& vertex) = 0;
	virtual DecoratedVertex& getDecoratedVersionOf(const Vertex& vertex) = 0;
	void decorateVerticesOf(const Graph& graph);

private:
	Path createPathBetween(const Vertex& source, const Vertex& target);
	void setID(const String& id);

private:
	String id;
};

#endif //__SHORTEST_PATH_ALGORITHM_HEADER_INCLUDED__