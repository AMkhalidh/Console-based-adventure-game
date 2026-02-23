#include "Player.h"
#include <iostream>
#include <sstream>
#include <map>
#include <random>
#include <algorithm>
#include "Weapon.h"
#include "Armour.h"

Player::Player(const std::string& name, const std::string& description, int hitpoints, int skillRating)
    : Character(name, description, hitpoints, skillRating), score(0) {}

void Player::setScore(int s) {
    score = s;
}

int Player::getScore() const {
    return score;
}

void Player::setLocation(Location* loc) {
    currentLocation = loc;
}

Location* Player::getLocation() const {
    return currentLocation;
}

void Player::collectItems(Location* loc) {
    
    std::cout << name << " attempts to collect items at " << loc->getName() << "\n";
}

bool Player::moveTo(const std::string& direction) {
    if (!currentLocation) return false;
    
    
    std::map<std::string, Location*> exits;
    currentLocation->getExits(exits);
    
    
    auto it = exits.find(direction);
    if (it != exits.end()) {
        currentLocation = it->second;
        return true;
    }
    
    return false;
}

std::string Player::drinkPotion() {
    
    return "No potions to drink!";
}

int Player::rollDice() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(1, 6);
    return dis(gen);
}

std::string Player::combat(Location* loc) {
    auto& monsters = loc->getMonsters();
    if (monsters.empty()) {
        return "No monsters to fight!";
    }
    
    auto it = std::max_element(monsters.begin(), monsters.end(),
        [](const std::unique_ptr<Monster>& a, const std::unique_ptr<Monster>& b) {
            return a->getHitpoints() < b->getHitpoints();
        });
    Monster* monster = it->get();
    std::cout << "\nCombat begins with " << monster->getName() << "!\n";
    while (this->isAlive() && monster->isAlive()) {
        
        int playerSkill = this->getSkill();
        int weaponPower = 0;
        Weapon* equippedWeapon = nullptr;
        for (const auto& item : this->inventory) {
            if (item->getType() == ItemType::WEAPON) {
                equippedWeapon = dynamic_cast<Weapon*>(item.get());
                break; 
            }
        }
        if (equippedWeapon) {
            weaponPower = equippedWeapon->getPower();
        }
        int playerRoll = rollDice() + rollDice();
        int playerTotal = playerSkill + weaponPower + playerRoll;

        
        int monsterSkill = monster->getSkill();
        int monsterPower = monster->getPower();
        int monsterRoll = rollDice() + rollDice();
        int monsterTotal = monsterSkill + monsterPower + monsterRoll;

        std::cout << "\nPlayer rolls: Skill(" << playerSkill << ") + Weapon(" << weaponPower << ") + Roll(" << playerRoll << ") = " << playerTotal << "\n";
        std::cout << monster->getName() << " rolls: Skill(" << monsterSkill << ") + Power(" << monsterPower << ") + Roll(" << monsterRoll << ") = " << monsterTotal << "\n";

        if (playerTotal > monsterTotal) {
            
            int damage = weaponPower > 0 ? weaponPower : 1;
            int reduced = std::max(1, damage - monster->getArmourProtection());
            std::cout << "You hit the " << monster->getName() << " for " << reduced << " damage!\n";
            monster->takeHit(reduced);
        } else if (monsterTotal > playerTotal) {
            
            int damage = monsterPower;
            int reduced = std::max(1, damage - this->getArmourProtection());
            std::cout << monster->getName() << " hits you for " << reduced << " damage!\n";
            this->takeHit(reduced);
        } else {
            std::cout << "Both attacks are equal! The round is a draw.\n";
            continue;
        }
        std::cout << "Player HP: " << this->getHitpoints() << " | " << monster->getName() << " HP: " << monster->getHitpoints() << "\n";
    }
    
    if (!monster->isAlive()) {
        std::cout << monster->getSwansong() << std::endl;
        
        
        int bounty = monster->getBounty();
        this->addScore(bounty);
        std::cout << "You defeated the " << monster->getName() << " and earned " << bounty << " points!\n";
        monsters.erase(it);
        return "Victory!";
    } else if (!this->isAlive()) {
        std::cout << "You have been defeated by the " << monster->getName() << "...\n";
        return "Defeat!";
    }
    return "Combat ended.";
}

void Player::addItem(std::unique_ptr<Item> item) {
    std::cout << name << " picked up " << item->getName() << "\n";
    inventory.push_back(std::move(item));
}

void Player::useItem(size_t index) {
    if (index < inventory.size()) {
        inventory[index]->use(*this);
        inventory.erase(inventory.begin() + index);
    }
}

void Player::move(const std::string& direction) {
    std::cout << name << " moves " << direction << "\n";
}

void Player::addScore(int points) {
    score += points;
    std::cout << name << " gained " << points << " points! Total score: " << score << "\n";
} 