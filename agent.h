#ifndef AGENT_H
#define AGENT_H
#include <iostream>

enum class Gender
{
    MALE,
    FEMALE
};

inline std::ostream &operator<<(std::ostream &out, Gender g)
{
    return (out << (g == Gender::MALE ? "male" : "female"));
}


class Agent
{
    Gender d_gender;
    int d_age = 0;
    bool d_alive = true;
    int d_idx = -1;
    int d_nChildren = 0;

public:
    Agent(Gender g, int age = 0):
        d_gender(g),
        d_age(age)
    {}

    void getOlder(int amount = 1)
    {
        d_age += amount;
    }

    Gender gender() const 
    { 
        return d_gender; 
    }
    
    void giveBirth() 
    {
        if (d_gender == Gender::MALE)
            throw std::string("Called giveBirth() on a male.");

        ++d_nChildren;
    }
    
    int nChildren() const
    {
        return d_nChildren;
    }

    int age() const
    { 
        return d_age; 
    }

    void kill() 
    { 
        d_alive = false; 
    }
    
    bool alive() const
    {
        return d_alive;
    }
    
    int getIdx() const
    {
        return d_idx;
    }

    void setIdx(int idx)
    {
        d_idx = idx;
    }

    operator bool() const
    { 
        return d_alive; 
    }
};


#endif
