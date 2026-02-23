#include "Item.h"

Item::Item(const std::string& name, const std::string& description, ItemType type)
    : name(name), description(description), type(type) {}

void Item::setName(const std::string& newName) {
    name = newName;
}

std::string Item::getName() const {
    return name;
}

std::string Item::getDescription() const {
    return description;
}

ItemType Item::getType() const {
    return type;
} 