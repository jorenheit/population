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
    int d_age;

    bool d_alive = true;
    int d_idx = -1;
    int d_nChildren = 0;

public:

    Agent(Gender g, int age = 0);

    void setIdx(int idx);
    void getOlder(int amount = 1);
    void giveBirth(); 
    void kill(); 

    Gender gender() const;
    int nChildren() const;
    int age() const;
    bool alive() const;
    int getIdx() const;
    operator bool() const;
    bool operator==(Agent const &other) const;
    bool operator!=(Agent const &other) const;
};

#endif
