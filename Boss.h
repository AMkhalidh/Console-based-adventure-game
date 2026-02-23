#ifndef BOSS_H
#define BOSS_H

#include "Monster.h"
#include "Item.h"
#include <memory>

class Boss : public Monster {
public:
    Boss(const std::string& name, const std::string& description, int skill, int hitpoints, int power, int armour, const std::string& swansong);
    virtual ~Boss() = default;
    
    
    virtual void specialAttack(Character& target);
    void makeSound() const override;

    
    bool hasEldritchRing() const { return eldritchRing != nullptr; }
    void setEldritchRing(std::unique_ptr<Item> ring) { eldritchRing = std::move(ring); }
    std::unique_ptr<Item> dropEldritchRing();

private:
    int specialAttackPower;
    std::unique_ptr<Item> eldritchRing;
};

#endif 