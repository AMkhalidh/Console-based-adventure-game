#include "Weapon.h"
#include "Character.h"
#include <iostream>

Weapon::Weapon(const std::string& name, const std::string& description, int power)
    : Item(name, description, ItemType::WEAPON), power(power) {}

void Weapon::use(Character& target) {
    std::cout << "Using " << name << " on " << target.getName() << " for " << power << " damage!\n";
    target.takeHit(power);
}

void Weapon::setPower(int pw) {
    power = pw;
} 