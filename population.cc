#include "population.h"

Population::Population(int nStart):
    d_first(0),
    d_last(nStart - 1)
{
    d_agents.reserve(5 * nStart);
    for (int i = 0; i != nStart; ++i)
    {
        d_agents.emplace_back(std::rand() % 2 ? Gender::MALE : Gender::FEMALE);
        d_agents.back().setIdx(i);
    }

    d_deadIndices.push(-1);
}

Population::Population(std::vector<int> const &ages):
    d_first(0),
    d_last(ages.size() - 1)
{
    int nStart = ages.size();
    d_agents.reserve(5 * nStart);
    for (int i = 0; i != nStart; ++i)
    {
        d_agents.emplace_back(std::rand() % 2 ? Gender::MALE : Gender::FEMALE,
                              Coordinate(),
                              ages[i]);
        d_agents.back().setIdx(i);
    }
    d_deadIndices.push(-1);
}

Population::Population(std::vector<Coordinate> const &coords):
    d_first(0),
    d_last(coords.size() - 1)
{
    int nStart = coords.size();
    d_agents.reserve(5 * nStart);
    for (int i = 0; i != nStart; ++i)
    {
        d_agents.emplace_back(std::rand() % 2 ? Gender::MALE : Gender::FEMALE,
                              coords[i]);
        d_agents.back().setIdx(i);
    }
    d_deadIndices.push(-1);
}

Population::Population(std::vector<int> const &ages, std::vector<Coordinate> const &coords)
{
    if (ages.size() != coords.size())
        throw std::string("Called Population constructor with vectors of unequal length.");

    int nStart = coords.size();
    d_agents.reserve(5 * nStart);
    for (int i = 0; i != nStart; ++i)
    {
        d_agents.emplace_back(std::rand() % 2 ? Gender::MALE : Gender::FEMALE,
                              coords[i],
                              ages[i]);
        d_agents.back().setIdx(i);
    }
    d_deadIndices.push(-1);

    d_first = 0;
    d_last = nStart - 1;
}

int Population::size() const 
{ 
    return d_agents.size() - d_deadIndices.size() + 1; 
}

void Population::add(Gender g, int age)
{
    add(Agent(g, age));
}

void Population::add(Agent const &agent)
{
    int idx = d_deadIndices.top();
    if (idx == -1)
    {
        d_agents.emplace_back(agent);
        d_last = d_agents.size() - 1;
        d_agents.back().setIdx(d_last);
    }
    else
    {
        d_agents[idx] = agent;
        d_agents[idx].setIdx(idx);
        d_deadIndices.pop();
            
        if (idx < d_first)
            d_first = idx;
        else if (idx > d_last)
            d_last = idx;
    }
}

void Population::add(Population const &other)
{
    for (auto const &agent: other)
    {
        add(agent);
    }
}

void Population::kill(Agent const &agent)
{
    int idx = agent.getIdx(); 
    if (idx == -1)
        return;

    if (!d_agents[idx])
        return; //already dead

    d_agents[idx].kill();
    d_deadIndices.push(idx);

    if (size() == 0)
    {
        d_first = d_last = 0;
        return;
    }

    if (idx == d_first)
    { // update d_first
        while (!d_agents[++d_first]) {}
    }
    else if (idx == d_last)
    { // update d_last
        while (!d_agents[--d_last]) {}
    }
}

PopulationIterator__<Population> Population::find(Agent const &agent)
{
    return PopulationIterator__<Population>(*this, agent);
}


PopulationIterator__<Population const> Population::find(Agent const &agent) const
{
    return PopulationIterator__<Population const>(*this, agent);
}

PopulationIterator__<Population> Population::begin() 
{ 
    return ::begin(*this);
}

PopulationIterator__<Population> Population::end() 
{ 
    return ::end(*this);
}

PopulationIterator__<Population const> Population::begin() const
{ 
    return ::begin(*this);
}

PopulationIterator__<Population const> Population::end() const
{ 
    return ::end(*this);
}


