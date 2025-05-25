#include "enemyfactory.hpp"

int getRandomInt(int min, int max) {
    std::random_device rd;                          // Random device seed
    std::mt19937 gen(rd());                         // Mersenne Twister engine
    std::uniform_int_distribution<> distr(min, max); // Uniform distribution
    return distr(gen);
}


vector<Enemy> EnemyFactory::createEnemy(int heroLevel)
{
    vector<string> names = {"Thief", "Smuggler", "Fiend", "Backstaber", "Mutant", "Pirate"};
    vector<string> modifiers = {"Recruit", "Amateur", "Seasoned", "Trained", "Expert", "OG"};

    vector<Enemy> enemies;
    string name, modifier;
    int hp, atkdmg, xp;

    for (int i=0; i <= getRandomInt(2, 5); i++)
    {

        //Name randomizer
        name = names[getRandomInt(0,names.size()-1)];
        if (heroLevel <= 3)
        {
            hp = getRandomInt(4,8);
            atkdmg = getRandomInt(1,3);
            xp = getRandomInt(100,400);
            modifier = modifiers[getRandomInt(0,1)];
        }
        else if(heroLevel > 3 && heroLevel <= 6)
        {
            hp = getRandomInt(10,20);
            atkdmg = getRandomInt(4,8);
            xp = getRandomInt(500,1000);
            modifier = modifiers[getRandomInt(2,3)];
        }
        else
        {
            hp = getRandomInt(40,100);
            atkdmg = getRandomInt(10,15);
            xp = getRandomInt(1000,3000);
            modifier = modifiers[getRandomInt(4,5)];
        }

        name = name + " " + modifier;
        enemies.push_back(Enemy(name, hp, atkdmg, xp, true));
    }
    return enemies;
}

