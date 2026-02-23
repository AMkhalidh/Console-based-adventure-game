#include "Treasure.h"
#include "Player.h"
#include <iostream>

Treasure::Treasure(const std::string& name, const std::string& description, int value)
    : Item(name, description, ItemType::TREASURE), value(value) {}

void Treasure::use(Character& target) {
    if (auto* player = dynamic_cast<Player*>(&target)) {
        std::cout << player->getName() << " collects " << name << " worth " << value << " points!\n";
        player->addScore(value);
    } else {
        std::cout << "Only players can collect treasure!\n";
    }
}

int Treasure::getValue() const {
    return value;
}

void Treasure::setValue(int val) {
    value = val;
} 