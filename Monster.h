#ifndef MONSTER_H
#define MONSTER_H

#include "Character.h"
#include <string>

class Monster : public Character {
public:
    Monster(const std::string& name,
            const std::string& description,
            int hitpoints,
            int skill,
            int power,
            int bounty,
            const std::string& swansong);

    int getPower() const;
    int getBounty() const;
    std::string getSwansong() const;
    void setBounty(int b);

    virtual ~Monster();

    virtual void makeSound() const;

private:
    int power;
    int bounty;
    std::string swansong;
};

#endif 
