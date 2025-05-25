#pragma once
#include <string>
using namespace std;

class Weapon {
    public:

        Weapon(std::string name, int baseDamage, int strengthModifier, int durability);

        string getName() const;

        int getDmg() const;

        int getStrMod() const;

        int getDur() const;

        bool isBroke() const;
    
        void weaponUse();

    private:
        std::string name;
        int baseDamage;
        int strengthModifier;
        int durability;
};
