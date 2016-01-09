#include "agent.h"

Agent::Agent(Gender g, int age):
    d_gender(g),
    d_age(age)
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
    
int Agent::getIdx() const
{
    return d_idx;
}

void Agent::setIdx(int idx)
{
    d_idx = idx;
}

Agent::operator bool() const
{ 
    return d_alive; 
}

bool Agent::operator==(Agent const &other) const
{
    return d_idx != -1 && d_idx == other.d_idx;
}

bool Agent::operator!=(Agent const &other) const
{
    return d_idx != -1 && d_idx != other.d_idx;
}
