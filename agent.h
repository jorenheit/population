#ifndef AGENT_H
#define AGENT_H

#include <iostream>
#include "coordinate.h"

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
    static size_t s_agentCounter;

    Gender d_gender;
    Coordinate d_coord;
    int d_age;
    size_t d_id;

    bool d_alive = true;
    int d_nChildren = 0;

public:
    Agent(Gender g = Gender::MALE, Coordinate const &c = Coordinate(), int age = 0);

    void getOlder(int amount = 1);
    void giveBirth(); 
    void kill(); 
    void setCoordinate(Coordinate const &c);

    Gender gender() const;
    int nChildren() const;
    int age() const;
    bool alive() const;
    size_t id() const;
    Coordinate const &coordinate() const;
    operator bool() const;
    bool operator==(Agent const &other) const;
    bool operator!=(Agent const &other) const;
};

double distance(Agent const &a1, Agent const &a2);

#endif
