#ifndef POTION_H
#define POTION_H

#include "Item.h"
#include "Character.h"

class Potion : public Item {
public:
    Potion(const std::string& name, const std::string& description, int strength);
    void use(Character& target) override;
    int getStrength() const;
    void setStrength(int str);

private:
    int strength;
};

#endif 