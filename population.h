#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include <cstdlib>
#include <stack>
#include "agent.h"

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

private:
    Agent &operator[](int idx) { return d_agents[idx]; }
    Agent const &operator[](int idx) const { return d_agents[idx]; }
};

template <typename Population_t>
class PopulationIterator__;

template <typename Population_t>
PopulationIterator__<Population_t> begin(Population_t &);

template <typename Population_t>
PopulationIterator__<Population_t> end(Population_t &);

template <typename Population_t>
class PopulationIterator__
{
    friend PopulationIterator__ begin<Population_t>(Population_t &);
    friend PopulationIterator__ end<Population_t>(Population_t &);

    enum class IteratorValue { 
        BEGIN = -1,
        END = -2 
    };

    Population_t &d_population;
    int d_idx;

    PopulationIterator__(Population_t &pop, IteratorValue val): 
        d_population(pop)
    {
        switch (val)
        {
        case IteratorValue::BEGIN:
            d_idx = d_population.d_first;
            break;
        case IteratorValue::END:
            d_idx = static_cast<int>(IteratorValue::END);
            break;
        default:
            throw std::string("Default reached in constructor of PopulationIterator");
        }
    }

public:
    PopulationIterator__ &operator++()
    {
        if (d_population.size() == 0 || d_idx >= d_population.d_last)
        {
            d_idx = static_cast<int>(IteratorValue::END);
            return *this;
        }

        // Look for next alive agent
        while (!d_population[++d_idx]) 
        {}

        return *this;
    }

    PopulationIterator__ &operator--()
    {
        if (d_population.size() == 0)
        {
            d_idx = static_cast<int>(IteratorValue::END);
            return *this;
        }
            
        if (d_idx == d_population.d_first)
            return *this;

        // Look for previous alive agent
        while (!d_population[--d_idx]) 
        {}
        
        return *this;
    }

    bool operator==(PopulationIterator__ const &other)
    {
        return d_idx == other.d_idx;
    }

    bool operator!=(PopulationIterator__ const &other)
    {
        return d_idx != other.d_idx;
    }

    typename std::conditional<std::is_const<Population_t>::value, Agent const&, Agent&>::type
    operator*() 
    { 
        if (d_idx == static_cast<int>(IteratorValue::END))
            throw std::string("Trying to dereference end-iterator");

        return d_population[d_idx]; 
    }
};


template <typename Population_t>
inline PopulationIterator__<Population_t> begin(Population_t &pop) 
{ 
    using Iter_t = PopulationIterator__<Population_t>;
    return Iter_t(pop, pop.size() ? Iter_t::IteratorValue::BEGIN : Iter_t::IteratorValue::END); 
}

template <typename Population_t>
inline PopulationIterator__<Population_t> end(Population_t &pop) 
{ 
    using Iter_t = PopulationIterator__<Population_t>;
    return Iter_t(pop, Iter_t::IteratorValue::END); 
}

#endif //POPULATION_H
