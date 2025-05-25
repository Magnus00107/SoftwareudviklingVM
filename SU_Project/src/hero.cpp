#include "hero.hpp"
#include "enemy.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

Hero::Hero(const string& name)
    //Initialiserings listen bruges til at initialisere klassens
    //datafelter før konstruktørens krop kører
    : name(name), xp(0), level(1), hp(10), atkdmg(2) , gold(0), alive(true),
    weapon("Fists", 0, 1, 9999){}    

    void Hero::attack(Enemy &enemy)
    {
        int totalDmg = getAtkDmg();
        cout << name << " attacks " << enemy.getName() << " with " << weapon.getName()
             << " and deals " << totalDmg << " damage!" << endl;
    
        enemy.takeDamage(totalDmg);
        weapon.weaponUse();
    
        if (weapon.isBroke()) {
            cout << "Your " << weapon.getName() << " broke!" << endl;
            weapon = Weapon("Fists", 0, 1, 9999); // fallback
        }
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
    setHp(10+(level-1)*2);
    setAtkDmg(getAtkDmg()+ 1);
    cout << name << "has leveled up to " << level << endl;
}

void Hero::saveCharacter() const
{
    ifstream infile("saves/saves.txt");
    vector<std::string> lines;
    string line;
    bool found = false;

    // Læs eksisterende linjer ind
    while (getline(infile, line)) {
        istringstream iss(line);
        string currentName;
        iss >> currentName;

        if (currentName == name) {
            // Erstat den eksisterende linje med opdateret version
            std::ostringstream newLine;
            newLine << name << " " << xp << " " << level << " " << hp << " " << atkdmg << " " << gold;
            lines.push_back(newLine.str());
            found = true;
        } else {
            lines.push_back(line); // behold uændrede linjer
        }
    }
    infile.close();

    if (!found) {
        // Tilføj ny hero til sidst
        std::ostringstream newLine;
        newLine << name << " " << xp << " " << level << " " << hp << " " << atkdmg << " " << gold;
        lines.push_back(newLine.str());
    }

    // Skriv alle linjer tilbage til filen
    std::ofstream outfile("saves/saves.txt");
    for (const std::string& l : lines) {
        outfile << l << "\n";
    }
    outfile.close();
}


Hero Hero::loadFromFile(const string name) //fordi den returnere typen Hero og Hero nr 2 er fordi funktionen tilhører klassen Hero
{
    string line;
    ifstream savefile("saves/saves.txt");
    while (getline(savefile, line))
    {
        if(line.find(name) !=string::npos)
            //npos er et specielt konstant tal i c++ som signalere "ikke fundet" i forbindelse med søgning i tekststrenge.
        {
            istringstream iss(line); //input string stream
            int xp, level, hp, atkdmg, gold;
            string newName;
            iss >>newName >> xp >> level >> hp >> atkdmg >> gold; //fungerer som cin, sætter variablerne til dem fra linjen

            Hero hero(newName);
            hero.setXp(xp);
            hero.setLevel(level);
            hero.setHp(hp);
            hero.setAtkDmg(atkdmg);
            hero.setGold(gold);
            return hero;
        }
    }
    throw runtime_error("Hero with name " + name + "not found.");
}

void Hero::deleteCharacter() const
{
    string line;
    vector<string> lines;
    ifstream infile("saves/saves.txt");

    while (getline(infile, line))
    {
        istringstream iss(line);
        string currentName;
        iss >> currentName;
        
        if (currentName != name)
        {
            lines.push_back(line);
        }
    }
    infile.close();
    //Reopen the file to write back the lines we kept
    ofstream outfile("saves/saves.txt");
    for (const string &l : lines)
    {
        outfile << l << endl;
    }
    outfile.close();
}

void Hero::printStats() const {
    cout << "\n=== Hero Stats ===\n";
    cout << "Name:    " << name << endl;
    cout << "Level:   " << level << endl;
    cout << "XP:      " << xp << endl;
    cout << "HP:      " << hp << endl;
    cout << "Gold:    " << gold << endl;
    cout << "Weapon:  " << weapon.getName() << endl;
    cout << "Total Atk: " << getAtkDmg() << endl;
    cout << "===================\n\n";
}



bool Hero::isAlive() const
{
    return alive;
}

string Hero::getName() const
{
    return name;
}

int Hero::getLevel() const
{
    return level;
}

int Hero::getXp() const
{
    return xp;
}

int Hero::getHp() const
{
    return hp;
}

int Hero::getAtkDmg() const
{
    return (weapon.getStrMod()*atkdmg) + weapon.getDmg();
    
}

int Hero::getGold() const
{
    return gold;
}

void Hero::setLevel(int newLevel)
{
    level = newLevel;
}

void Hero::setXp(int newXp)
{
    xp = newXp;
}

void Hero::setHp(int newHp)
{
    hp = newHp;
}

void Hero::setAtkDmg(int newAtkDmg)
{
    atkdmg = newAtkDmg;
}

void Hero::setGold(int newGold)
{
    gold = newGold;
}

void Hero::setWeapon(const Weapon& w)
{
    weapon = w;
}

Weapon Hero::getweapon() const
{
    return weapon;
}
