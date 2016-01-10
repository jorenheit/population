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
    using Vector = std::vector<Agent>;

    Vector d_agents;
    std::stack<int> d_deadIndices;
    int d_first;
    int d_last;

public:
    explicit Population(int nStart = 0);

    void add(Population const &other);
    void add(Agent const &agent);
    void kill(Agent const &agent);

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
};

#include "populationiterator.tpp"

#endif //POPULATION_H
