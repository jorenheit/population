#include <iostream>
#include <cmath>
#include "population.h"
#include "timer.h"

struct ChildPolicy
{
    static bool hasChild(Agent const &a)
    {
        if (a.gender() ==  Gender::MALE || a.nChildren() > 4)
            return false;
        
        static double const maternity[][9] = {
            {0, 11, 0},
            {12, 15, 0.00092895},   
            {16, 19, 0.077258},   
            {20, 24, 0.23194},   
            {25, 29, 0.28433},   
            {30, 34, 0.25638},   
            {35, 39, 0.11949},   
            {40, 44, 0.027722},   
            {45, 1e6, 0.0019624}
        };

        int age = a.age();
        for (int i = 0; i != 9; ++i)
            if (age >= maternity[i][0] && age <= maternity[i][1])
            {
                double p = maternity[i][2];
                return static_cast<double>(std::rand()) / RAND_MAX < p;
            }

        throw std::string("Reached the end of ChildPolicy::hasChild");
    }
};

struct KillPolicy
{
    static bool isKilled(Agent const &a)
    {
        static int const mortality[][11] = {
            {0,       0,     177,     225},
            {1,       4,    4386,    5376},
            {5,      14,    8333,   10417},
            {15,     24,    1908,    4132},
            {25,     34,    1215,    2488},
            {35,     44,     663,    1104},
            {45,     54,     279,     421},
            {55,     64,     112,     178},
            {65,     74,      42,      65},
            {75,     84,      15,      21},
            {85,     1000,     6,       7}
        };

        int age = a.age();
        int gen = a.gender() == Gender::MALE ? 2 : 3;

        for (int i = 0; i != 11; ++i)
        {
            if (age >= mortality[i][0] && age <= mortality[i][1])
            {
                double p = 1.0 / mortality[i][gen];
                return static_cast<double>(std::rand()) / RAND_MAX < p;
            }
        }
        
        throw std::string("Reached the end of KillPolicy::isKilled");
    }
};

template <typename ChildPolicy_, typename KillPolicy_>
void nextYear(Population &pop)
{
    Population nextGen;

    for (auto &agent: pop)
    {
        if (ChildPolicy_::hasChild(agent))
        {
            agent.giveBirth();
            nextGen.add(std::rand() % 2 ? Gender::MALE : Gender::FEMALE);
        }

        if (KillPolicy_::isKilled(agent))
            pop.kill(agent);

        agent.getOlder();
    }

    pop.add(nextGen);
}

void run(int nStart, int nYears)
{
    Population pop(nStart);

    Timer timer;
    for (int i = 0; i != nYears; ++i)
    {
        int oldSize = pop.size();

        timer.reset();
        nextYear<ChildPolicy, KillPolicy>(pop);

        std::cout << i << '\t' <<  oldSize << '\t' << timer.elapsed().count() << '\n';
    }
}
