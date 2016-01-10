#include "policies.h"

bool BasicChildPolicy::hasChild(Agent const &a)
{
    if (a.gender() ==  Gender::MALE || a.nChildren() > 4)
        return false;
        
    static int const ages[][9] = {
        {0, 11}, {12, 15}, {16, 19},
        {20, 24}, {25, 29}, {30, 34},
        {35, 39}, {40, 44}, {45, 1000},
    };

    static constexpr int N_AGE_CATEGORIES = std::extent<decltype(ages), 1>::value;

    static double const fraction[N_AGE_CATEGORIES] = {
        0, 0.00092895, 0.077258, 
        0.23194, 0.28433, 0.25638, 
        0.11949, 0.027722, 0.0019624
    };

    int age = a.age();
    for (int i = 0; i != N_AGE_CATEGORIES; ++i)
        if (age >= ages[i][0] && age <= ages[i][1])
            return static_cast<double>(std::rand()) / RAND_MAX < fraction[i];

    throw std::string("Reached the end of ChildPolicy::hasChild");
}

bool BasicKillPolicy::isKilled(Agent const &a)
{
    static int const ages[][11] = {
        {0,   0}, {1,   4}, {5,  14}, 
        {15, 24}, {25, 34}, {35, 44}, 
        {45, 54}, {55, 64}, {65, 74}, 
        {75, 84}, {85, 1000}
    };

    static constexpr int N_AGE_CATEGORIES = std::extent<decltype(ages), 1>::value;

    static double const fraction[][11] = {
        {1.0 /  177,  1.0 /   225},
        {1.0 / 4386,  1.0 /  5376},
        {1.0 / 8333,  1.0 / 10417},
        {1.0 / 1908,  1.0 /  4132},
        {1.0 / 1215,  1.0 /  2488},
        {1.0 /  663,  1.0 /  1104},
        {1.0 /  279,  1.0 /   421},
        {1.0 /  112,  1.0 /   178},
        {1.0 /   42,  1.0 /    65},
        {1.0 /   15,  1.0 /    21},
        {1.0 /    6,  1.0 /     7}
    };

    int age = a.age();
    for (int i = 0; i != N_AGE_CATEGORIES; ++i)
        if (age >= ages[i][0] && age <= ages[i][1])
            return (static_cast<double>(std::rand()) / RAND_MAX < 
                    fraction[i][static_cast<int>(a.gender())]);
        
    throw std::string("Reached the end of KillPolicy::isKilled");
}
