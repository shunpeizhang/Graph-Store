#ifndef __CONCRETE_GRAPH_CREATOR_HEADER_INCLUDED__
#define __CONCRETE_GRAPH_CREATOR_HEADER_INCLUDED__

#include "GraphCreator.h"

template <class ConcreteGraph>
class ConcreteGraphCreator : public GraphCreator
{
public:
	explicit ConcreteGraphCreator(const char* criterion);
	ConcreteGraphCreator(const ConcreteGraphCreator<ConcreteGraph>&) = delete;
	ConcreteGraphCreator<ConcreteGraph>& operator=(const ConcreteGraphCreator<ConcreteGraph>&) = delete;
	ConcreteGraphCreator(ConcreteGraphCreator<ConcreteGraph>&&) = delete;
	ConcreteGraphCreator<ConcreteGraph>& operator=(ConcreteGraphCreator<ConcreteGraph>&&) = delete;
	virtual ~ConcreteGraphCreator() = default;

	virtual std::unique_ptr<Graph> createGraph(const String& id) const override;
};

#include "ConcreteGraphCreator.hpp"

#endif //__CONCRETE_GRAPH_CREATOR_HEADER_INCLUDED__