#ifndef __COMMAND_HEADER_INCLUDED__
#define __COMMAND_HEADER_INCLUDED__

#include "../../../../../args-master/args-master/args.hxx"
#include "../../Graph Collection/GraphCollection.h"

class Command
{
public:
	virtual ~Command() = default;
	virtual void execute(args::Subparser& parser) = 0;

protected:
	Command() = default;
	Command(const Command&) = default;
	Command& operator=(const Command&) = default;
	Command(Command&&) = default;
	Command& operator=(Command&&) = default;

protected:
	static GraphCollection& getGraphs();
	static bool isUsedGraph(const Graph& graph);
	static Graph& getUsedGraph();
	static void useNoGraph();
	static void setUsedGraph(Graph& graph);
	
private:
	static Graph* usedGraph;
	static GraphCollection graphs;
};

#endif //__COMMAND_HEADER_INCLUDED__