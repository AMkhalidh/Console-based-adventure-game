#include <iostream>
#include "Monster.h"

Monster::Monster(const std::string& name,
                 const std::string& description,
                 int hitpoints,
                 int skill,
                 int power,
                 int bounty,
                 const std::string& swansong)
    : Character(name, description, hitpoints, skill),
      power(power), bounty(bounty), swansong(swansong) {}

int Monster::getPower() const {
    return power;
}

int Monster::getBounty() const {
    return bounty;
}

std::string Monster::getSwansong() const {
    return swansong;
}

void Monster::setBounty(int b) {
    bounty = b;
}

void Monster::makeSound() const {
    std::cout << name << " growls menacingly!\n";
}

Monster::~Monster() = default;
