#include "Gameworld.h"
#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include "Armour.h"
#include "Potion.h"
#include "Treasure.h"
#include "Weapon.h"

Gameworld::Gameworld() : gameOver(false) {}



void Gameworld::run() {
    loadWorld();  
    
    
    while (!isGameOver()) {
        
        Location* loc = player->getLocation();
        std::cout << "\nYou are at " << loc->getName() << "\n";
        std::cout << loc->getDescription() << "\n";
        std::cout << loc->showExits() << "\n";
        std::cout << loc->listItems() << "\n";

        std::cout << "Commands:\n";
        std::cout << "Exits: e/w/s/n\n";
        std::cout << "Inventory: inv/inventory\n";
        std::cout << "Collect: collect/c\n";
        std::cout << "Drink Potion: drink/d\n";
        std::cout << "Fight Monster: fight/f\n";
        std::cout << "Quit game: quit/q\n";
    
        std::cout << "\nEnter command: ";
        std::string command;
        std::getline(std::cin, command);
        
        
        std::transform(command.begin(), command.end(), command.begin(), ::tolower);

        
        if (command == "quit" || command == "q") {
            setGameOver(true);
            continue;
        }

        
        if (command == "inv" || command == "inventory") {
            std::cout << player->getInventory();
            continue;
        }

        
        if (command == "collect" || command == "c") {
            auto items = loc->removeAllItems();
            for (auto& item : items) {
                player->addItem(std::move(item));
            }
            continue;
        }

        
        if (command == "drink" || command == "d") {
            std::string result = player->drinkPotion();
            std::cout << result << std::endl;
            continue;
        }

        
        if (command == "fight" || command == "f") {
            std::string result = player.get()->combat(loc);
            std::cout << result << std::endl;
            if (result == "Defeat!") {
                setGameOver(true);
            }
            continue;
        }

        
        std::string direction;
        if (command == "n" || command == "north") direction = "NORTH";
        else if (command == "s" || command == "south") direction = "SOUTH";
        else if (command == "e" || command == "east") direction = "EAST";
        else if (command == "w" || command == "west") direction = "WEST";

        if (!direction.empty()) {
            if (player->moveTo(direction)) {
                
            } else {
                std::cout << "You cannot go that way.\n";
            }
            continue;
        }

        
        std::cout << "Invalid command.\n";

        
        auto inv = player->getInventory();
        if (inv.find("Eldritch Ring") != std::string::npos) {
            std::cout << "\nYou have obtained the Eldritch Ring! You have won the game!\n";
            setGameOver(true);
        }
    }
}

bool Gameworld::isGameOver() const {
    return gameOver;
}

void Gameworld::setGameOver(bool newGameOver) {
    gameOver = newGameOver;
}

void Gameworld::loadWorld() {
    
    locations.clear();  
    
    
    locations.resize(33);  
    
    locations[19] = Location("The Central Nexus", "An ancient crossroads where time and space intertwine.");
    locations[1] = Location("The Great Abercromby Gates", "Massive stone gates carved with arcane runes.");
    locations[2] = Location("The Guildhall of Scholars", "A grand hall where traders, scribes, and mysterious figures gather.");
    locations[5] = Location("The Thompson Observatory", "A domed tower where the stars reveal glimpses of fate.");
    locations[30] = Location("The Scholar's Ascent", "A winding staircase that tests the mind as much as the body.");
    locations[29] = Location("The Fenwick Rift", "A tear in reality...");
    locations[32] = Location("The Final Gateway", "A portal leading to the realm beyond.");
    locations[31] = Location("The Octagon Spire", "A mystical tower containing knowledge beyond mortal comprehension.");
    locations[20] = Location("The Victoria Spire", "A towering spire with a celestial beacon at its peak.");
    locations[13] = Location("The Chatham Archives", "Endless rows of scrolls, each documenting powerful relics lost to time.");
    locations[15] = Location("The Sidney Vault", "A labyrinth of books and stone where scholars vanished centuries ago.");
    locations[3] = Location("The Forbidden Harold Temple", "Ancient tomes whisper secrets from their dusty shelves.");
    locations[6] = Location("The Holt Enclave", "A ruined amphitheater where echoes of past lectures still resonate.");
    locations[14] = Location("The Mountford Keep", "A towering fortress where ancient warriors once trained.");
    locations[9] = Location("The Rendall Arena", "The echoes of battle cries ring through the ruined walls.");
    locations[7] = Location("The Reilly Battlegrounds", "A coliseum of stone and steel, where warriors train and champions rise.");
    locations[26] = Location("The Guilded Forge", "A legendary forge where artifacts of immense power were once crafted.");

    
    
    
    
    locations[19].addExit("WEST", &locations[1]);
    locations[19].addExit("NORTH", &locations[2]);
    locations[19].addExit("EAST", &locations[3]);

    
    locations[1].addExit("EAST", &locations[19]);

    
    locations[2].addExit("SOUTH", &locations[19]);
    locations[2].addExit("NORTH", &locations[5]);
    locations[2].addExit("EAST", &locations[13]);
    locations[2].addExit("WEST", &locations[15]);

    
    locations[5].addExit("SOUTH", &locations[2]);
    locations[5].addExit("NORTH", &locations[30]);
    locations[5].addExit("EAST", &locations[31]);

    
    locations[30].addExit("SOUTH", &locations[5]);
    locations[30].addExit("WEST", &locations[29]);

    
    locations[29].addExit("EAST", &locations[30]);
    locations[29].addExit("SOUTH", &locations[32]);

    
    locations[32].addExit("NORTH", &locations[29]);

    
    locations[31].addExit("NORTH", &locations[20]);
    locations[31].addExit("WEST", &locations[5]);

    
    locations[20].addExit("SOUTH", &locations[31]);

    
    locations[13].addExit("WEST", &locations[2]);

    
    locations[15].addExit("EAST", &locations[2]);

    
    locations[3].addExit("WEST", &locations[19]);
    locations[3].addExit("NORTH", &locations[6]);
    locations[3].addExit("EAST", &locations[14]);
    locations[3].addExit("SOUTH", &locations[9]);

    
    locations[6].addExit("SOUTH", &locations[3]);
    locations[6].addExit("EAST", &locations[26]);

    
    locations[14].addExit("SOUTH", &locations[7]);
    locations[14].addExit("NORTH", &locations[26]);
    locations[14].addExit("WEST", &locations[3]);

    
    locations[9].addExit("NORTH", &locations[3]);
    locations[9].addExit("WEST", &locations[7]);

    
    locations[7].addExit("NORTH", &locations[14]);
    locations[7].addExit("EAST", &locations[9]);

    
    locations[26].addExit("SOUTH", &locations[14]);
    locations[26].addExit("WEST", &locations[6]);

    
    
    
    locations[29].addItem(std::make_unique<Armour>("Leather Armour", "Basic protective gear", 5));
    locations[31].addItem(std::make_unique<Armour>("Plate Armour", "Heavy protective armour", 20));
    locations[14].addItem(std::make_unique<Armour>("Steel Shield", "A sturdy shield", 10));

    
    locations[6].addItem(std::make_unique<Potion>("Red Healing Potion", "A healing draught", 40));
    locations[9].addItem(std::make_unique<Potion>("Blue Healing Potion", "A powerful healing potion", 50));
    locations[19].addItem(std::make_unique<Potion>("Green Healing Potion", "A moderate healing potion", 30));
    locations[32].addItem(std::make_unique<Potion>("Ultimate Healing", "The strongest healing potion", 200));

    
    locations[6].addItem(std::make_unique<Treasure>("Diamond", "A brilliant gem", 100));
    locations[5].addItem(std::make_unique<Treasure>("Gold Crown", "A royal artifact", 150));
    locations[9].addItem(std::make_unique<Treasure>("Gold Coin", "A valuable coin", 50));
    locations[9].addItem(std::make_unique<Treasure>("Gemstone", "A precious stone", 75));
    locations[1].addItem(std::make_unique<Treasure>("Silver Coin", "A valuable coin", 25));
    locations[2].addItem(std::make_unique<Treasure>("Scholar's Medallion", "A symbol of wisdom", 50));
    locations[15].addItem(std::make_unique<Treasure>("Ruby Gemstone", "A blood-red gem", 70));
    locations[31].addItem(std::make_unique<Treasure>("Celestial Orb", "A mysterious sphere", 150));
    locations[2].addItem(std::make_unique<Treasure>("Silver Key", "An ornate key", 20));

    
    locations[29].addItem(std::make_unique<Weapon>("Great Axe", "A mighty weapon", 15));
    locations[2].addItem(std::make_unique<Weapon>("Iron Sword", "A reliable blade", 12));
    locations[31].addItem(std::make_unique<Weapon>("Great Axe", "A powerful axe", 15));
    locations[19].addItem(std::make_unique<Weapon>("Rusty Sword", "An old but serviceable weapon", 5));
    locations[3].addItem(std::make_unique<Weapon>("Ceremonial Dagger", "An ornate blade", 8));
    locations[14].addItem(std::make_unique<Weapon>("Knight's Sword", "A well-crafted sword", 12));
    locations[9].addItem(std::make_unique<Weapon>("Gladiator's Spear", "A balanced polearm", 10));
    locations[7].addItem(std::make_unique<Weapon>("Battle Axe", "A heavy war axe", 14));
    locations[26].addItem(std::make_unique<Weapon>("Master's Hammer", "A mighty war hammer", 18));
    locations[31].addItem(std::make_unique<Weapon>("Enchanted Staff", "A magical weapon", 15));

    
    auto raider = std::make_unique<Monster>("Raider", "A swift and ruthless attacker.", 30, 3, 10, 5, "The final blow before falling.");
    locations[6].addMonster(raider.get());
    monsters.push_back(std::move(raider));

    auto warrior = std::make_unique<Monster>("Warrior", "A stalwart defender of ancient traditions.", 40, 4, 12, 8, "Dies honourably in battle.");
    locations[5].addMonster(warrior.get());
    monsters.push_back(std::move(warrior));

    auto brute = std::make_unique<Monster>("Brute", "A formidable opponent with crushing strength.", 50, 2, 15, 10, "Falls with a deafening roar.");
    locations[29].addMonster(brute.get());
    monsters.push_back(std::move(brute));

    auto troll = std::make_unique<Monster>("Troll", "An ancient creature lurking beneath the shadows.", 60, 2, 18, 12, "Its final roar shakes the earth.");
    locations[29].addMonster(troll.get());
    monsters.push_back(std::move(troll));

    auto bandit = std::make_unique<Monster>("Bandit", "A cunning thief with a taste for blood.", 45, 4, 20, 7, "Slumps quietly after a fatal misstep.");
    locations[2].addMonster(bandit.get());
    monsters.push_back(std::move(bandit));

    auto wraith = std::make_unique<Monster>("Wraith", "An ethereal entity from beyond the grave.", 35, 2, 8, 4, "Fades into the mist with a haunting whisper.");
    locations[30].addMonster(wraith.get());
    monsters.push_back(std::move(wraith));

    auto knight = std::make_unique<Monster>("Knight", "A noble warrior sworn to protect his honour.", 50, 5, 18, 12, "Falls with dignity in his final charge.");
    locations[31].addMonster(knight.get());
    monsters.push_back(std::move(knight));

    auto sprite = std::make_unique<Monster>("Sprite", "A mischievous and elusive fae creature.", 25, 1, 10, 3, "Disappears with a final burst of light.");
    locations[9].addMonster(sprite.get());
    monsters.push_back(std::move(sprite));

    
    auto boss = std::make_unique<Boss>(
        "Archon of the Spire",
        "A towering figure wreathed in cosmic energy, guardian of the Eldritch Ring.",
        8,   // Skill
        80,  // Hitpoints
        20,  // Power
        10,  // Armour
        "With a final roar, the Archon collapses, the Eldritch Ring tumbling from its grasp."
    );
    boss->setBounty(500);
    boss->setEldritchRing(std::make_unique<Treasure>("Eldritch Ring", "A ring pulsing with otherworldly power", 1000));
    locations[20].addMonster(boss.get());
    this->boss = std::move(boss);

    
    player = std::make_unique<Player>("Hero", "A brave adventurer", 50, 6);
    player->setArmour(0);
    player->setLocation(&locations[19]); 

    std::cout << "Lockin. You are at " << player->getLocation()->getName() << ".\n";
}  