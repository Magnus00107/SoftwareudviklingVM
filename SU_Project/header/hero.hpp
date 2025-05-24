#pragma once
#include <string>
using namespace std;

class Hero {
    public:

    //Service functions
    Hero(const string& name);

    void attack(class Enemy& enemy);

    void takeDamage(int dmg);

    void changeXP(int xp);

    void levelUp();

    void saveCharacter() const; 
        //const bruges når vi ikke vil ændre objeket's tilstand

    static Hero loadFromFile(const string name);
        //Bruges til at kalde funktionen uden først at have et objekt af typen Hero.

    void deleteCharacter() const;

    void printStats() const;

    //Getter function
    bool isAlive() const;

    string getName() const;

    int getLevel();

    int getXp();

    int getHp();

    int getAtkDmg();

    //Setter functions:
    void setLevel(int newLevel);

    void setXp(int newXp);

    void setHp(int newHp);

    void setAtkDmg(int newAtkDmg);
    
    private:
        bool alive;
        string name;
        int xp;
        int level;
        int hp;
        int atkdmg;
};