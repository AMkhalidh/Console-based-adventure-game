#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Location.h"
#include <vector>
#include <memory>
#include "Item.h"
#include "Weapon.h"
#include <string>

class Player : public Character {
public:
    Player(const std::string& name, const std::string& description, int hitpoints, int skillRating);
    
    
    void setScore(int s);
    int getScore() const;
    void setLocation(Location* loc);
    Location* getLocation() const;
    void collectItems(Location* loc);
    bool moveTo(const std::string& direction);
    std::string drinkPotion();
    static int rollDice();
    std::string combat(Location* loc);

    void addItem(std::unique_ptr<Item> item);         
    void useItem(size_t index);                       
    void move(const std::string& direction);          
    void addScore(int points);                        


private:
    int score;
    std::vector<std::unique_ptr<Item>> inventory;
    std::unique_ptr<Weapon> equippedWeapon;

};

#endif 