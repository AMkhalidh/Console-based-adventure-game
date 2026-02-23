#include "Potion.h"
#include "Character.h"
#include <iostream>

Potion::Potion(const std::string& name, const std::string& description, int strength)
    : Item(name, description, ItemType::POTION), strength(strength) {}

void Potion::use(Character& target) {
    std::cout << target.getName() << " drinks " << name << " and heals for " << strength << " health!\n";
    target.setHitpoints(target.getHitpoints() + strength);
}

int Potion::getStrength() const {
    return strength;
}

void Potion::setStrength(int str) {
    strength = str;
} 