#ifndef ARMOUR_H
#define ARMOUR_H

#include "Item.h"
#include "Character.h"

class Armour : public Item {
public:
    Armour(const std::string& name, const std::string& description, int protection);
    void use(Character& target) override;
    int getProtection() const;
    void setProtection(int prot);

private:
    int protection;
};

#endif 