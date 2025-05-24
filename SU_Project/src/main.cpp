#include <iostream>
#include <vector>
#include "hero.hpp"
#include "enemy.hpp"
#include "enemyfactory.hpp"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

bool isFighting;
void game(Hero &hero);
void fight(Hero &hero, Enemy &enemy);
void mainMenu();

vector<Enemy> enemies =
{
    Enemy ("Thief", 4, 1, 100, true),
    Enemy ("Chief Thieft ", 6, 2, 1000, true),
    Enemy ("Smuggler", 8, 3, 400, true),
    Enemy ("Sneaky Smuggler", 6, 2, 200, true),
    Enemy ("Fiend", 15, 5, 800, true),
    Enemy ("Pirate Captain", 5, 8, 1500, true)
};

#include <limits> // required for std::numeric_limits

void fight(Hero &hero, Enemy &enemy)
{
    isFighting = true;
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
        mainMenu();
    }
    else
    {
        std::cout << enemy.getName() << " has been defeated!!" << std::endl;
        hero.changeXP(enemy.getXp());
        game(hero);
    }
}


void game(Hero &hero)
{
    hero.printStats();
    cout << " Choose an enemy to fight" << endl;
    for (size_t i = 0; i < enemies.size(); i++)
    {
        if (enemies[i].isAlive() == true)
        {
            cout << i+1 << ". " << enemies[i].getName() << endl;
        }
    }
    std::cout << "Enter your choice or -1 save to save and exit game";
    int choice;
    std::cin >> choice;
    if (choice == -1)
    {
        hero.saveCharacter();
        exit(0);
    }
    fight(hero, enemies[choice-1]);
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

void mainMenu()
{
    int input;
    cout << "Shatter Field" << endl;
    cout << "Enter 1 for a list of saved games or enter 2 to start a new game" << endl;
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
        
        default:
            cout << "Wrong input" << endl;
            break;
    }
}



int main()
{
    EnemyFactory ef1; // Adjusted to match the default constructor
    
    for (size_t i = 0; i < ef1.createEnemy(3,3).size(); i++)
    {
        if (ef1.createEnemy(3,3)[i].isAlive() == true)
        {
            cout << i+1 << ". " << ef1.createEnemy(3,3)[i].getName() << endl;
        }
    }
    
    mainMenu();
}