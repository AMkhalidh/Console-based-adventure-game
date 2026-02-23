#ifndef TREASURE_H
#define TREASURE_H

#include "Item.h"
#include "Character.h"

class Treasure : public Item {
public:
    Treasure(const std::string& name, const std::string& description, int value);
    void use(Character& target) override;
    int getValue() const;
    void setValue(int val);

private:
    int value;
};

#endif // 