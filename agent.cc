#include "agent.h"

int Agent::s_agentCounter = 0;

Agent::Agent(Gender g, Coordinate const &c, int age):
    d_gender(g),
    d_coord(c),
    d_age(age),
    d_id(s_agentCounter++)
{}

void Agent::getOlder(int amount)
{
    d_age += amount;
}

Gender Agent::gender() const 
{ 
    return d_gender; 
}
    
void Agent::giveBirth() 
{
    if (d_gender == Gender::MALE)
        throw std::string("Called giveBirth() on a male.");

    ++d_nChildren;
}
    
int Agent::nChildren() const
{
    return d_nChildren;
}

int Agent::age() const
{ 
    return d_age; 
}

void Agent::kill() 
{ 
    d_alive = false; 
}
    
bool Agent::alive() const
{
    return d_alive;
}
    
Agent::operator bool() const
{ 
    return d_alive; 
}

bool Agent::operator==(Agent const &other) const
{
    return d_id == other.d_id;
}

bool Agent::operator!=(Agent const &other) const
{
    return !operator==(other);
}

Coordinate const &Agent::coordinate() const
{
    return d_coord;
}

void Agent::setCoordinate(Coordinate const &c)
{
    d_coord = c;
}

double distance(Agent const &a1, Agent const &a2)
{
    return distance(a1.coordinate(), a2.coordinate());
}
