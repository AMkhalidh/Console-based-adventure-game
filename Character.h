#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include <memory>
#include <map>
#include "Item.h"


class Location;

class Character {
public:
    Character(const std::string& name, const std::string& description, int hitpoints, int skillRating);
    virtual ~Character() = default;

    
    int getArmourProtection() const;
    void addItem(std::unique_ptr<Item> item);
    void removeItem(const std::string& itemName);
    void dropItem(const std::string& itemName);
    Location* getLocation() const;
    bool moveTo(Location* newLocation);
    void setSkill(int sk);
    int getSkill() const;
    void setHitpoints(int hp);
    int getHitpoints() const;
    void setName(const std::string& newName);
    std::string getName() const;
    void setArmour(int ar);
    int getArmour() const;
    void takeHit(int hit);
    std::string getInventory() const;
    
    
    std::vector<std::string> getPotions() const;
    std::vector<std::string> getTreasures() const;
    std::vector<std::string> getWeapons() const;
    std::vector<std::string> getArmourNames() const;
    void drinkPotion();
    void collectItems(const Location& loc);

    void attack(Character& target);
    void takeDamage(int damage);
    bool isAlive() const;


protected:
    std::string name;
    std::string description;
    int hitpoints;
    int skillRating;
    int armour;
    Location* currentLocation;
    std::vector<std::unique_ptr<Item>> inventory;
};

#endif 