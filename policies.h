#ifndef POLICIES_H
#define POLICIES_H

#include "agent.h"

struct BasicChildPolicy
{
    static bool hasChild(Agent const &a);
};

struct BasicKillPolicy
{
    static bool isKilled(Agent const &a);
};

#endif
