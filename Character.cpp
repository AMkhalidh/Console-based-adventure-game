#include "Character.h"
#include "Location.h"
#include "Potion.h"
#include <iostream>
#include <sstream>
#include <algorithm>

Character::Character(const std::string& name, const std::string& description, int hitpoints, int skillRating)
    : name(name), description(description), hitpoints(hitpoints), skillRating(skillRating), 
      armour(0), currentLocation(nullptr) {}

int Character::getArmourProtection() const {
    return armour;
}

void Character::addItem(std::unique_ptr<Item> item) {
    if (item) {
        std::cout << name << " picks up " << item->getName() << "\n";
        inventory.push_back(std::move(item));
    }
}

void Character::removeItem(const std::string& itemName) {
    auto it = std::find_if(inventory.begin(), inventory.end(),
        [&itemName](const std::unique_ptr<Item>& item) { return item->getName() == itemName; });
    if (it != inventory.end()) {
        inventory.erase(it);
    }
}

void Character::dropItem(const std::string& itemName) {
    auto it = std::find_if(inventory.begin(), inventory.end(),
        [&itemName](const std::unique_ptr<Item>& item) { return item->getName() == itemName; });
    if (it != inventory.end() && currentLocation) {
        
        inventory.erase(it);
    }
}

Location* Character::getLocation() const {
    return currentLocation;
}

bool Character::moveTo(Location* newLocation) {
    if (newLocation) {
        currentLocation = newLocation;
        return true;
    }
    return false;
}

void Character::setSkill(int sk) {
    skillRating = sk;
}

int Character::getSkill() const {
    return skillRating;
}

void Character::setHitpoints(int hp) {
    hitpoints = hp;
}

int Character::getHitpoints() const {
    return hitpoints;
}

void Character::setName(const std::string& newName) {
    name = newName;
}

std::string Character::getName() const {
    return name;
}

void Character::setArmour(int ar) {
    armour = ar;
}

int Character::getArmour() const {
    return armour;
}

std::vector<std::string> Character::getArmourNames() const {
    std::vector<std::string> armours;
    for (const auto& item : inventory) {
        if (item->getType() == ItemType::ARMOUR) {
            armours.push_back(item->getName());
        }
    }
    std::sort(armours.begin(), armours.end());
    return armours;
}

void Character::takeHit(int hit) {
    int damage = std::max(0, hit - getArmourProtection());
    hitpoints -= damage;
    if (hitpoints < 0) hitpoints = 0;
    std::cout << name << " takes " << damage << " damage (reduced by " << getArmourProtection() << " armour)\n";
}

std::vector<std::string> Character::getPotions() const {
    std::vector<std::string> potions;
    for (const auto& item : inventory) {
        if (item->getType() == ItemType::POTION) {
            potions.push_back(item->getName());
        }
    }
    std::sort(potions.begin(), potions.end());
    return potions;
}

std::vector<std::string> Character::getTreasures() const {
    std::vector<std::string> treasures;
    for (const auto& item : inventory) {
        if (item->getType() == ItemType::TREASURE) {
            treasures.push_back(item->getName());
        }
    }
    std::sort(treasures.begin(), treasures.end());
    return treasures;
}

std::vector<std::string> Character::getWeapons() const {
    std::vector<std::string> weapons;
    for (const auto& item : inventory) {
        if (item->getType() == ItemType::WEAPON) {
            weapons.push_back(item->getName());
        }
    }
    std::sort(weapons.begin(), weapons.end());
    return weapons;
}

void Character::drinkPotion() {
    
    auto it = std::find_if(inventory.begin(), inventory.end(),
        [](const std::unique_ptr<Item>& item) {
            return item->getType() == ItemType::POTION;
        });
    if (it != inventory.end()) {
        (*it)->use(*this);
        inventory.erase(it);
    } else {
        std::cout << name << " has no potions to drink.\n";
    }
}

std::string Character::getInventory() const {
    std::stringstream ss;
    
    auto potions = getPotions();
    auto treasures = getTreasures();
    auto weapons = getWeapons();
    auto armours = getArmourNames();
    
    ss << "\nInventory for " << name << ":\n";
    
    if (!potions.empty()) {
        ss << "Potions:\n";
        for (const auto& potion : potions) {
            ss << "  " << potion << "\n";
        }
    }
    
    if (!treasures.empty()) {
        ss << "Treasures:\n";
        for (const auto& treasure : treasures) {
            ss << "  " << treasure << "\n";
        }
    }
    
    if (!weapons.empty()) {
        ss << "Weapons:\n";
        for (const auto& weapon : weapons) {
            ss << "  " << weapon << "\n";
        }
    }
    
    if (!armours.empty()) {
        ss << "Armour:\n";
        for (const auto& armour : armours) {
            ss << "  " << armour << "\n";
        }
    }
    
    if (potions.empty() && treasures.empty() && weapons.empty() && armours.empty()) {
        ss << "Empty\n";
    }
    
    return ss.str();
}

void Character::collectItems(const Location& loc) {
    
}

void Character::attack(Character& target) {
    std::cout << name << " attacks " << target.getName() << " for " << skillRating << " damage!\n";
    target.takeHit(skillRating);
}

void Character::takeDamage(int damage) {
    hitpoints -= damage;
    if (hitpoints < 0) hitpoints = 0;
    std::cout << name << " takes " << damage << " damage! Remaining health: " << hitpoints << "\n";
}

bool Character::isAlive() const {
    return hitpoints > 0;
} 