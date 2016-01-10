#include <iostream>
#include <cmath>
#include "population.h"
#include "timer.h"
#include "policies.h"

template <typename ChildPolicy, typename KillPolicy>
void nextYear(Population &pop)
{
    std::vector<Agent> nextGen;

    for (auto &agent: pop)
    {
        if (ChildPolicy::hasChild(agent))
        {
            agent.giveBirth();
            nextGen.push_back(std::rand() % 2 ? Gender::MALE : Gender::FEMALE);
        }

        if (KillPolicy::isKilled(agent))
            pop.kill(agent);

        agent.getOlder();
    }

    pop.add(nextGen.begin(), nextGen.end());
}

void run(int nStart, int nYears)
{
    Population pop = initialPopulation(nStart);

    Timer timer;
    for (int i = 0; i != nYears; ++i)
    {
        int oldSize = pop.size();

        timer.reset();
        nextYear<BasicChildPolicy, BasicKillPolicy>(pop);

        std::cout << i << '\t' <<  oldSize << '\t' << timer.elapsed().count() << '\n';
    }
}
