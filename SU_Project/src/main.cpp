#include <iostream>
#include <vector>
#include "hero.hpp"
#include "enemy.hpp"
#include "enemyfactory.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <cavefactory.hpp>
#include <weapon.hpp>
#include <sqlite3.h>
using namespace std;

bool inCave = false;
int cavesCompleted = 0;
void game(Hero &hero);
void fight(Hero &hero, Enemy &enemy);
void mainMenu();
void cave(Hero &hero);

vector<Enemy> enemies =
{
    Enemy ("Thief", 4, 1, 100, true),
    Enemy ("Chief Thieft ", 6, 2, 1000, true),
    Enemy ("Smuggler", 8, 3, 400, true),
    Enemy ("Sneaky Smuggler", 6, 2, 200, true),
    Enemy ("Fiend", 15, 5, 800, true),
    Enemy ("Pirate Captain", 5, 8, 1500, true)
};

std::vector<Weapon> weapons = {
    Weapon("Plasma Dagger",      12, 1, 30),
    Weapon("Neon Baton",         6,  2, 25),
    Weapon("Ion Saber",         20, 1, 40),
    Weapon("Graviton Hammer",   15, 3, 35),
    Weapon("Laser Whip",         5, 4, 20),
    Weapon("Photon Blade",      25, 1, 30),
    Weapon("EMP Gauntlet",       0, 5, 15),
    Weapon("Quantum Spear",     18, 2, 28),
    Weapon("Stellar Katana",    30, 2, 50),
    Weapon("Void Rifle",        10, 3, 10)
};

#include <limits> // required for std::numeric_limits

void recordKill(const Hero& hero, const Enemy& enemy) {
    sqlite3* db;
    if (sqlite3_open("game.db", &db) == SQLITE_OK) {
        std::ostringstream sql;
        sql << "INSERT INTO kills (hero_name, weapon_name, enemy_name) VALUES ('"
            << hero.getName() << "', '"
            << hero.getWeapon().getName() << "', '"
            << enemy.getName() << "');";

        sqlite3_exec(db, sql.str().c_str(), nullptr, nullptr, nullptr);
        sqlite3_close(db);
        cout << "Kill logged to DB\n";
    }
}


void fight(Hero &hero, Enemy &enemy)
{
    while (hero.isAlive() && enemy.isAlive())
    {
        //std::cout << hero.getName() << " attacks " << enemy.getName() << std::endl;
        hero.attack(enemy);
        std::cout << hero.getName() << " has " << hero.getHp() << " hp left" << std::endl;
        std::cout << enemy.getName() << " has " << enemy.getHp() << " hp left" << std::endl;

        if (enemy.isAlive()) {
            //std::cout << enemy.getName() << " attacks " << hero.getName() << std::endl;
            enemy.attack(hero);
            std::cout << hero.getName() << " has " << hero.getHp() << " hp left" << std::endl;
            std::cout << enemy.getName() << " has " << enemy.getHp() << " hp left" << std::endl;
        }

        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }

    if (!hero.isAlive())
    {
        std::cout << hero.getName() << " has been defeated!" << std::endl;
        std::cout << "!!GAME OVER!!" << std::endl;
        hero.deleteCharacter();
        inCave = false;
        mainMenu();
    }
    else
    {
        std::cout << enemy.getName() << " has been defeated!!" << std::endl;
        hero.changeXP(enemy.getXp());
        hero.saveCharacter();
        recordKill(hero, enemy);

        if (inCave == true)
        {
            cavesCompleted ++;
            cave(hero);
        }
        else
        {
            game(hero);
        }
    }
}


void game(Hero &hero)
{
    hero.printStats();
    std::cout << "Choose an action:\n";
    std::cout << "1. Fight an enemy\n";
    std::cout << "2. Enter a cave (greater reward)\n";
    std::cout << "3. Save and return to main menu\n";
    std::cout << "Enter number (1-3): ";
    int input;
    cin >> input;

    switch(input){
        case 1:
            for (size_t i = 0; i < enemies.size(); i++)
            {
                if (enemies[i].isAlive() == true)
                {
                    cout << i+1 << ". " << enemies[i].getName() << endl;
                }
            }
            std::cout << "Enter your choice";
            int choice;
            std::cin >> choice;
            fight(hero, enemies[choice-1]);
            break;

        case 2:
            cave(hero);
            break;

        case 3:
            hero.saveCharacter();
            mainMenu();
            break;
    }
}

void cave(Hero &hero)
{
    static Cavefactory::Cave currentCave;
    if (inCave == false)
    {
        std::vector<Cavefactory::Cave> caves;
        caves.push_back(Cavefactory::createCave(hero, "Smugglers Den"));
        caves.push_back(Cavefactory::createCave(hero, "Fiends Den"));
        caves.push_back(Cavefactory::createCave(hero, "Pirates Cove"));
    
        // Show cave names
        std::cout << "Available caves:\n";
        for (size_t i = 0; i < caves.size(); ++i) {
            std::cout << i + 1 << ". " << caves[i].name << " (" << caves[i].enemies.size() << " enemies, "
                    << caves[i].goldReward << " gold reward)\n";
        }
    
        std::cout << "Enter number to explore: ";
        int caveChoice;
        std::cin >> caveChoice;
    
        if (caveChoice < 1 || caveChoice > caves.size())
        {
            cout << "Invalid cave choice" << endl;
            return;
        }

        currentCave = caves[caveChoice - 1];
        cout << "Entering " << currentCave.name << "...\n";
        inCave = true;
        cave(hero);
    }
    else if (inCave == true)
    {
        for (Enemy &e : currentCave.enemies)
        {
            if (e.isAlive() == true)
            {
                fight(hero, e);
            }
        }
        cout << currentCave.name << " has been conquered" << endl;
        cout << hero.getName() << " has been awarded " << currentCave.goldReward << " gold" << endl;
        hero.setGold(hero.getGold()+currentCave.goldReward);

        if (cavesCompleted < weapons.size())
        {
            cout << "Weapon: " << weapons[cavesCompleted].getName() << " has been awarded." << endl;
            hero.setWeapon(weapons[cavesCompleted]);
        }
        else
        {
            cout << "You already have the most OP weapon." << endl;
        }        
        inCave = false;
        game(hero);
    }
}

void saves()
{
    string name;
    string line;
    ifstream savefile("saves/saves.txt");
    while (getline(savefile, line))
    {
        cout << line << endl;
    }
    cout << " " << endl;
    cout << "Enter name of save to play: ";
    cin >> name;
    Hero hero = Hero::loadFromFile(name);
    game(hero);
}

void newGame()
{
    string name;
    int choice;
    cout << "name your hero" << endl;
    cin >> name;
    cout << "Are you sure you wish to name your hero: " << name << " ?" << endl;
    cout << "Press 1 to confirm or press 2 to rename";
    cin >> choice;

    switch (choice)
    {
        case 1:
            break;
        case 2:
            cout << "Rename your hero" << endl;
            cin >> name;
            break;

        default:
            cout << "Invalid choice. Returning to main menu." << endl;
            break;    
    }
    Hero hero(name);
    hero.saveCharacter();
    game(hero);
}

void analyzeMenu() {
    sqlite3* db;

    while (true) {
        db = nullptr;
        if (sqlite3_open("game.db", &db) != SQLITE_OK) {
            std::cerr << "Failed to open DB\n";
            return;
        }

        std::cout << "\n=== Analysis Menu ===\n";
        std::cout << "1. Show all kills\n";
        std::cout << "2. Show kills per hero\n";
        std::cout << "3. Show kills per weapon per hero\n";
        std::cout << "4. Show heroes in alphabetic order\n";
        std::cout << "5. Back to main menu\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        const char* sql = nullptr;
        switch (choice) {
            case 1:
                sql = "SELECT * FROM kills;";
                break;
            case 2:
                sql = "SELECT hero_name, COUNT(*) as kills FROM kills GROUP BY hero_name;";
                break;
            case 3:
                sql = "SELECT hero_name, weapon_name, COUNT(*) as kills FROM kills GROUP BY hero_name, weapon_name;";
                break;
            case 4:
                sql = "SELECT DISTINCT hero_name FROM kills ORDER BY hero_name DESC;";
                break;
            case 5:
                sqlite3_close(db);
                mainMenu();
                break;
            default:
                std::cout << "Invalid choice\n";
                sqlite3_close(db);
                continue;
        }

        sqlite3_exec(db, sql, [](void*, int cols, char** vals, char** colNames) {
            for (int i = 0; i < cols; ++i)
                std::cout << colNames[i] << ": " << (vals[i] ? vals[i] : "NULL") << "  ";
            std::cout << "\n";
            return 0;
        }, nullptr, nullptr);

        sqlite3_close(db);
    }
}

void mainMenu()
{
    int input;
    cout << "Shatter Field" << endl;
    cout << "1. List of saves" << endl;
    cout << "2. Start new game" << endl;
    cout << "3. Analyzer Menu" << endl;
    cout << "4. Exit game" << endl;
    cin >> input;
    switch (input)
    {
        case 1:
            cout << "list of saved games" << endl;
            saves();
            break;

        case 2:
            newGame();
            break;
        
        case 3:
            analyzeMenu();
            break;
        case 4:
            exit(0);
            break;
        default:
            cout << "Wrong input" << endl;
            break;
    }
}

//Implement function to remove caves
//Implement function to count how many enemies each hero has defeated
//Implement function to count how many kills a hero has commited pr weapon
//For each weapon show many enemies each hero has killed.

int main()
{
    mainMenu();
}