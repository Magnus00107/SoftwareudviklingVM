#include "hero.hpp"
#include "enemy.hpp"
#include <iostream>
using namespace std;

Hero::Hero(const string& name)
    //Initialiserings listen bruges til at initialisere klassens
    //datafelter før konstruktørens krop kører
    : name(name), xp(0), level(1), hp(10), atkdmg(2) ,alive(true){}    

void Hero::attack(Enemy &enemy)
{
    cout << name << " attacks " << enemy.getName() << " and damages" 
    << getAtkDmg() << "damage!" << endl;
    enemy.takeDamage(getAtkDmg()); 
}

void Hero::takeDamage(int dmg)
{
    hp -= dmg;

    if (hp <= 0)
    {
        alive = false;
        hp = 0;
    }
}

void Hero::changeXP(int amount)
{
    //Hero kan ikke stige i mere end 1 level ad gangen?
    xp += amount;
    cout << name << "has recieved " << amount << "xp and has now a total of "
    << xp << "xp!!" << endl;
    if (xp >= level*1000)
    {
        levelUp();
    }
}

void Hero::levelUp()
{
    level += 1;
    int minusxp = -(level-1) * 1000;
    changeXP(minusxp);
    cout << name << "has leveled up to " << level << endl;
}

bool Hero::isAlive() const
{
    return alive;
}

string Hero::getName() const
{
    return name;
}

int Hero::getLevel()
{
    return level;
}

int Hero::getXp()
{
    return xp;
}

int Hero::getHp()
{
    return hp;
}

int Hero::getAtkDmg()
{
    return atkdmg;
}
