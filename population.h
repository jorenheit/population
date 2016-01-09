#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include <cstdlib>
#include <stack>
#include "agent.h"

template <typename Population_t>
class PopulationIterator__;

class Population
{
    template  <typename T> friend class PopulationIterator__;
    using Vector = std::vector<Agent>;

    Vector d_agents;
    std::stack<int> d_deadIndices;
    int d_first;
    int d_last;

public:
    Population(int nStart = 0);

    int size() const;
    void add(Population const &other);
    void add(Agent const &agent);
    void add(Gender g, int age);
    void kill(Agent const &agent);

    PopulationIterator__<Population> find(Agent const &agent);
    PopulationIterator__<Population const> find(Agent const &agent) const;

    PopulationIterator__<Population> begin();
    PopulationIterator__<Population> end();

    PopulationIterator__<Population const> begin() const;
    PopulationIterator__<Population const> end() const;

private:
    Agent &operator[](int idx) { return d_agents[idx]; }
    Agent const &operator[](int idx) const { return d_agents[idx]; }
};

#include "populationiterator.tpp"

#endif //POPULATION_H
