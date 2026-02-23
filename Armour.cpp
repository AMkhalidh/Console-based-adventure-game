#include "Armour.h"
#include <iostream>

Armour::Armour(const std::string& name, const std::string& description, int protection)
    : Item(name, description, ItemType::ARMOUR), protection(protection) {}

void Armour::use(Character& target) {
    std::cout << target.getName() << " equips " << name << " providing " << protection << " protection!\n";
    target.setArmour(target.getArmour() + protection);
}

int Armour::getProtection() const {
    return protection;
}

void Armour::setProtection(int prot) {
    protection = prot;
} 