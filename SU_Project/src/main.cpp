#include <iostream>
#include <vector>
#include "hero.hpp"
#include "enemy.hpp"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void game(Hero &hero)
{
    cout << "The game has started" << endl;
    hero.saveCharacter();
    //Create function to exit and save
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

    mainMenu();

}