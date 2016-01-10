#include <iostream>
#include <cmath>
#include "population.h"
#include "timer.h"
#include "policies.h"

template <typename ChildPolicy, typename KillPolicy>
void nextYear(Population &pop)
{
    Population nextGen;

    for (auto &agent: pop)
    {
        if (ChildPolicy::hasChild(agent))
        {
            agent.giveBirth();
            nextGen.add(std::rand() % 2 ? Gender::MALE : Gender::FEMALE);
        }

        if (KillPolicy::isKilled(agent))
            pop.kill(agent);

        agent.getOlder();
    }

    pop.add(nextGen);
}

template <typename ...>
struct Error;

void fun1(ConstPopulationIterator const &c)
{}

void fun2(ConstPopulationIterator &c)
{}

void run(int nStart, int nYears)
{
    Population pop(nStart);

    Timer timer;
    for (int i = 0; i != nYears; ++i)
    {
        int oldSize = pop.size();

        timer.reset();
        nextYear<BasicChildPolicy, BasicKillPolicy>(pop);

        std::cout << i << '\t' <<  oldSize << '\t' << timer.elapsed().count() << '\n';
    }
}
