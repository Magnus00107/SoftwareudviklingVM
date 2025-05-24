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
    : name(name), xp(0), level(1), hp(10), atkdmg(2) ,alive(true){}    

void Hero::attack(Enemy &enemy)
{
    cout << name << " attacks " << enemy.getName() << " and deals " 
    << getAtkDmg() << " damage!" << endl;
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
            newLine << name << " " << xp << " " << level << " " << hp << " " << atkdmg;
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
        newLine << name << " " << xp << " " << level << " " << hp << " " << atkdmg;
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
            int xp, level, hp, atkdmg;
            string newName;
            iss >>newName >> xp >> level >> hp >> atkdmg; //fungerer som cin, sætter variablerne til dem fra linjen

            Hero hero(newName);
            hero.setXp(xp);
            hero.setLevel(level);
            hero.setHp(hp);
            hero.setAtkDmg(atkdmg);
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
    std::cout << "\n=== Hero Stats ===\n";
    std::cout << "Name:    " << name << std::endl;
    std::cout << "Level:   " << level << std::endl;
    std::cout << "XP:      " << xp << std::endl;
    std::cout << "HP:      " << hp << std::endl;
    std::cout << "Attack:  " << atkdmg << std::endl;
    std::cout << "===================\n\n";
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

