#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <vector>
#include <memory>
#include <map>
#include "Item.h"
#include "Monster.h"

class Location {
public:
    Location(const std::string& name = "", const std::string& description = "");
    
    
    void setName(const std::string& newName);
    std::string getName() const;
    void setDescription(const std::string& newDesc);
    std::string getDescription() const;
    void addExit(const std::string& direction, Location* loc);
    std::string showExits() const;
    void addMonster(Monster* monster);
    void delMonster(Monster* monster);
    void addItem(std::unique_ptr<Item> item);
    std::vector<std::unique_ptr<Item>> removeAllItems();
    std::string listItems() const;
    
    
    void getExits(std::map<std::string, Location*>& outExits) const;

    
    std::vector<std::unique_ptr<Monster>>& getMonsters() { return monsters; }

private:
    std::string name;
    std::string description;
    std::vector<std::unique_ptr<Item>> items;
    std::vector<std::unique_ptr<Monster>> monsters;
    std::map<std::string, Location*> exits;
};

#endif 