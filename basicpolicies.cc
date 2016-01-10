#include "policies.h"

bool BasicChildPolicy::hasChild(Agent const &a)
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
            return static_cast<double>(std::rand()) / RAND_MAX < maternity[i][2];

    throw std::string("Reached the end of ChildPolicy::hasChild");
}

bool BasicKillPolicy::isKilled(Agent const &a)
{
    static double const mortality[][11] = {
        {0,       0,    1.0 /  177,  1.0 /   225},
        {1,       4,    1.0 / 4386,  1.0 /  5376},
        {5,      14,    1.0 / 8333,  1.0 / 10417},
        {15,     24,    1.0 / 1908,  1.0 /  4132},
        {25,     34,    1.0 / 1215,  1.0 /  2488},
        {35,     44,    1.0 /  663,  1.0 /  1104},
        {45,     54,    1.0 /  279,  1.0 /   421},
        {55,     64,    1.0 /  112,  1.0 /   178},
        {65,     74,    1.0 /   42,  1.0 /    65},
        {75,     84,    1.0 /   15,  1.0 /    21},
        {85,     1e6,   1.0 /   6,   1.0 /     7}
    };

    int age = a.age();
    int col = a.gender() == Gender::MALE ? 2 : 3;

    for (int i = 0; i != 11; ++i)
        if (age >= mortality[i][0] && age <= mortality[i][1])
            return static_cast<double>(std::rand()) / RAND_MAX < mortality[i][col];
        
    throw std::string("Reached the end of KillPolicy::isKilled");
}


