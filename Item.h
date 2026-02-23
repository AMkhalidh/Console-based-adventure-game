#ifndef ITEM_H
#define ITEM_H

#include <string>

class Character;

enum class ItemType {
    POTION,
    TREASURE,
    WEAPON,
    ARMOUR
};

class Item {
public:
    Item(const std::string& name, const std::string& description, ItemType type);
    virtual ~Item() = default;
    
    virtual void use(Character& target) = 0;
    virtual void setName(const std::string& newName);
    virtual std::string getName() const;
    virtual std::string getDescription() const;
    virtual ItemType getType() const;

protected:
    std::string name;
    std::string description;
    ItemType type;
};

#endif 