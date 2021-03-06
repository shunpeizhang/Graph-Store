#ifndef __GRAPH_BUILDER_HEADER_INCLUDED__
#define __GRAPH_BUILDER_HEADER_INCLUDED__

#include "../File Parser/FileParser.h"
#include "../String/String.h"
#include "../Dynamic Array/DynamicArray.h"
#include "../Graph/Abstract class/Graph.h"

class GraphBuilder
{
	struct RawEdge
	{
		size_t startIDIndex;
		size_t endIDIndex;
		unsigned weight;
	};

public:
	GraphBuilder() = default;
	GraphBuilder(const GraphBuilder&) = delete;
	GraphBuilder& operator=(const GraphBuilder&) = delete;
	GraphBuilder(GraphBuilder&&) = delete;
	GraphBuilder& operator=(GraphBuilder&&) = delete;
	~GraphBuilder() = default;

	std::unique_ptr<Graph> buildFromFile(const String& fileName);

private:
	void openFile(const String& name);
	void buildAGraph();
	void createEmptyGraph();
	void addVerticesToTheCreatedGraph();
	void addEdgesHavingAddedVertices();
	RawEdge parseEdge();
	void addEdge(const RawEdge& edge);
	unsigned parseUnsignedAndSkipUntil(char symbol);
	void handleExceptionDuringBuilding(const String& fileName, const std::exception& e);
	void clean();

private:
	static const char EDGE_START = '(';
	static const char EDGE_END = ')';
	static const char EDGE_ATTRIBUTE_SEPARATOR = ',';
	static const char NEW_LINE = '\n';

private:
	std::unique_ptr<Graph> graph;
	DynamicArray<String> identifiers;
	FileParser fileParser;
};

#endif //__GRAPH_BUILDER_HEADER_INCLUDED__