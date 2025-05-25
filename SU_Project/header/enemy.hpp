#pragma once
#include <string>
using namespace std;

class Enemy {
    public:
        //Service functions
        Enemy(const string& name, int hp, int atkdmg, int xp, bool alive);

        void attack(class Hero& hero);

        void takeDamage(int dmg);

        bool isAlive() const;

        //Getter functions:
        string getName() const;

        int getXp() const;

        int getHp() const;

        int getAtkDmg() const;

    private:
        string name;
        int xp;
        int hp;
        int atkdmg;
        bool alive;
};