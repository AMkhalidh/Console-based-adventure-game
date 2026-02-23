#include "Boss.h"
#include <iostream>

Boss::Boss(const std::string& name, const std::string& description, int skill, int hitpoints, int power, int armour, const std::string& swansong)
    : Monster(name, description, skill, hitpoints, power, armour, swansong) {
    specialAttackPower = power * 2;
}

void Boss::specialAttack(Character& target) {
    std::cout << name << " performs a special attack on " << target.getName() 
              << " for " << specialAttackPower << " damage!\n";
    target.takeHit(specialAttackPower);
}

void Boss::makeSound() const {
    std::cout << name << " roars with earth-shaking force!\n";
}

std::unique_ptr<Item> Boss::dropEldritchRing() {
    return std::move(eldritchRing);
} 