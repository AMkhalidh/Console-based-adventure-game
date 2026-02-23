#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "Player.h"
#include "Monster.h"
#include "Boss.h"
#include "Location.h"
#include <vector>
#include <memory>
#include <string>

class Gameworld {
public:
    Gameworld();
    ~Gameworld() = default;
    
    
    bool isGameOver() const;
    void setGameOver(bool gameOver);
    void loadWorld();
    void run();

private:
    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<Monster>> monsters;
    std::unique_ptr<Boss> boss;
    std::vector<Location> locations;
    bool gameOver;
};

#endif 