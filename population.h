#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include <cstdlib>
#include <stack>
#include "agent.h"

class Population;

template <typename Population_t>
class PopulationIterator__;

using PopulationIterator = PopulationIterator__<Population>;
using ConstPopulationIterator = PopulationIterator__<Population const>;

class Population
{
    template  <typename T> friend class PopulationIterator__;

    std::vector<Agent> d_agents;
    std::stack<int> d_deadIndices;
    int d_first;
    int d_last;

public:
    explicit Population(int nStart = 0);
    template <typename AgentIter> Population(AgentIter it, AgentIter end);

    template <typename AgentIter> void add(AgentIter it, AgentIter end);
    void add(Agent const &agent);
    void kill(Agent &agent);
    int size() const;

    PopulationIterator begin();
    PopulationIterator end();
    PopulationIterator find(Agent const &agent);

    ConstPopulationIterator begin() const;
    ConstPopulationIterator end() const;
    ConstPopulationIterator find(Agent const &agent) const;

private:
    Agent &operator[](int idx) { return d_agents[idx]; }
    Agent const &operator[](int idx) const { return d_agents[idx]; }
    int getIdx(Agent const &agent) const;
};

// Helper function to generate an initial population
Population initialPopulation(int nStart);


template <typename AgentIter>
Population::Population(AgentIter it, AgentIter end)
{
    int idx = 0;
    while (it != end)
        d_agents.emplace_back(*it++);

    d_deadIndices.push(-1);
}


template <typename AgentIter>
void Population::add(AgentIter it, AgentIter end)
{
    while (it != end)
        add(*it++);
}


#include "populationiterator.tpp"

#endif //POPULATION_H
