#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"

class Weapon : public Item {
public:
    Weapon(const std::string& name, const std::string& description, int power);

    void use(Character& target) override;
    int getPower() const { return power; }
    void setPower(int pw);

private:
    int power; 
};

#endif 
