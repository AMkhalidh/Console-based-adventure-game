#include "Location.h"
#include <iostream>
#include <sstream>
#include <algorithm>

Location::Location(const std::string& name, const std::string& description)
    : name(name), description(description) {}

void Location::setName(const std::string& newName) {
    name = newName;
}

std::string Location::getName() const {
    return name;
}

void Location::setDescription(const std::string& newDesc) {
    description = newDesc;
}

std::string Location::getDescription() const {
    return description;
}

void Location::addExit(const std::string& direction, Location* loc) {
    if (loc) {
        exits[direction] = loc;
    }
}

std::string Location::showExits() const {
    std::stringstream ss;
    ss << "Exits: ";
    for (const auto& exit : exits) {
        ss << exit.first << " ";
    }
    return ss.str();
}

void Location::addMonster(Monster* monster) {
    if (monster) {
        monsters.push_back(std::unique_ptr<Monster>(monster));
    }
}

void Location::delMonster(Monster* monster) {
    auto it = std::find_if(monsters.begin(), monsters.end(),
        [monster](const std::unique_ptr<Monster>& m) { return m.get() == monster; });
    if (it != monsters.end()) {
        monsters.erase(it);
    }
}

void Location::addItem(std::unique_ptr<Item> item) {
    if (item) {
        items.push_back(std::move(item));
    }
}

std::vector<std::unique_ptr<Item>> Location::removeAllItems() {
    std::vector<std::unique_ptr<Item>> collectedItems;
    collectedItems = std::move(items);
    items.clear();
    return collectedItems;
}

std::string Location::listItems() const {
    if (items.empty()) {
        return "No items here.";
    }
    
    std::stringstream ss;
    ss << "Items here:\n";
    for (const auto& item : items) {
        ss << "  " << item->getName() << "\n";
    }
    return ss.str();
}

void Location::getExits(std::map<std::string, Location*>& outExits) const {
    outExits = exits;
} 
 