#include "population.h"

Population::Population(int nStart):
    d_first(0),
    d_last(nStart - 1)
{
    d_agents.reserve(nStart);
    for (int i = 0; i != nStart; ++i)
        d_agents.emplace_back(std::rand() % 2 ? Gender::MALE : Gender::FEMALE);

    d_deadIndices.push(-1);
}

int Population::size() const 
{ 
    return d_agents.size() - d_deadIndices.size() + 1; 
}

void Population::add(Agent const &agent)
{
    int idx = d_deadIndices.top();
    if (idx == -1)
    {
        d_agents.emplace_back(agent);
        d_last = d_agents.size() - 1;
    }
    else
    {
        d_agents[idx] = agent;
        d_deadIndices.pop();
            
        if (idx < d_first)
            d_first = idx;
        else if (idx > d_last)
            d_last = idx;
    }
}

void Population::kill(Agent &agent)
{
    if (!agent)
        return; //already dead

    kill(getIdx(agent));
}

void Population::kill(PopulationIterator const &it)
{
    if (!it->alive())
        return; // already dead

    kill(it.d_idx);
}

void Population::kill(int idx)
{
    // Assumed that checks on idx are already performed

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



int Population::getIdx(Agent const &agent) const
{
    int idx = &agent - &d_agents[0];
    if (idx < 0 || idx >= static_cast<int>(d_agents.size()))
        throw std::string("Attempted to get the index of an agent that is not part of the population.");

    return idx;
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

Population initialPopulation(int nStart)
{
    static int const ages[][19] = {
        {0, 4}, {5, 9}, {10, 14}, {15, 19},
        {20, 24}, {25, 29}, {30, 34}, {35, 39},
        {40, 44}, {45, 49}, {50, 54}, {55, 59},
        {60, 64}, {65, 69}, {70, 74}, {75, 79},
        {80, 84}, {85, 89}, {90, 100}
    };

    static constexpr int N_AGE_CATEGORIES = std::extent<decltype(ages), 1>::value;
    
    static double const fractions[N_AGE_CATEGORIES] = {
        0.062, 0.056, 0.058, 0.063,
        0.068, 0.068, 0.065, 0.066,
        0.073, 0.073, 0.065, 0.057,
        0.060, 0.048, 0.039, 0.032,
        0.024, 0.015, 0.008
    };

    Population result;
    int nTotal = 0;
    for (int i = 0; i != N_AGE_CATEGORIES; ++i)
    {
        int minAge = ages[i][0];
        int maxAge = ages[i][1];
        int ageDiff = maxAge - minAge;
        int n = fractions[i] * nStart;
        for (int j = 0; j != n; ++j)
        {
            int age = minAge + ageDiff * (static_cast<double>(std::rand()) / RAND_MAX);
            Gender g = std::rand() % 2 ? Gender::MALE : Gender::FEMALE;
            result.add(Agent(g, Coordinate(), age));
        }

        nTotal += n;
    }
    
    for (int i = 0; i != nStart - nTotal; ++i)
    {
        int age = ages[0][0] + (ages[N_AGE_CATEGORIES - 1][1] - ages[0][0]) * 
            (static_cast<double>(std::rand()) / RAND_MAX);
        Gender g = std::rand() % 2 ? Gender::MALE : Gender::FEMALE;
        result.add(Agent(g, Coordinate(), age));
    }

    return result;
}
