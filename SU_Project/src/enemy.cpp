#include "hero.hpp"
#include "enemy.hpp"
#include <iostream>
using namespace std;

Enemy::Enemy(const string& name, int hp, int atkdmg, int xp, bool alive)
: name(name), hp(hp), atkdmg(atkdmg), xp(xp), alive(true) {}

void Enemy::attack(Hero &hero)
{
    cout << name << " attacks " << hero.getName() << " and damages" 
    << getAtkDmg() << "damage!" << endl;
    hero.takeDamage(getAtkDmg()); 
}

void Enemy::takeDamage(int dmg)
{
    hp -= dmg;

    if (hp <= 0)
    {
        alive = false;
        hp = 0;
    }
}

bool Enemy::isAlive() const
{
    return alive;
}

string Enemy::getName() const
{
    return name;
}

int Enemy::getXp()
{
    return xp;
}

int Enemy::getHp()
{
    return hp;
}

int Enemy::getAtkDmg()
{
    return atkdmg;
}



