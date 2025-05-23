#include <iostream>
#include <vector>
#include "hero.hpp"
#include "enemy.hpp"

using namespace std;

void saves()
{

}

void game(Hero &hero)
{

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

    Hero hero1(name);
    game(hero1);
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