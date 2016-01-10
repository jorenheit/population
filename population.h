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
    explicit Population(std::vector<int> const &ages);
    explicit Population(std::vector<Coordinate> const &coords);
    Population(std::vector<int> const &ages, 
               std::vector<Coordinate> const &coords);

    int size() const;
    void add(Population const &other);
    void add(Agent const &agent);
    void add(Gender g, int age);
    void kill(Agent const &agent);

    PopulationIterator find(Agent const &agent);
    ConstPopulationIterator find(Agent const &agent) const;

    PopulationIterator begin();
    PopulationIterator end();

    ConstPopulationIterator begin() const;
    ConstPopulationIterator end() const;

private:
    Agent &operator[](int idx) { return d_agents[idx]; }
    Agent const &operator[](int idx) const { return d_agents[idx]; }
};

#include "populationiterator.tpp"

#endif //POPULATION_H
