#include "weapon.hpp"

Weapon::Weapon(std::string name, int baseDamage, int strengthModifier, int durability)
    : name(name), baseDamage(baseDamage), strengthModifier(strengthModifier), durability(durability) {}


string Weapon::getName() const
{
    return name;
}

int Weapon::getDmg() const
{
    return baseDamage;
}

int Weapon::getStrMod() const
{
    return strengthModifier;
}

int Weapon::getDur() const
{
    return durability;
}

void Weapon::weaponUse() {
    if (durability > 0) {
        durability--;
    }
}

bool Weapon::isBroke() const {
    return durability <= 0;
}
