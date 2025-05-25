#include "cavefactory.hpp"
#include "enemyfactory.hpp"

Cavefactory::Cave Cavefactory::createCave(const Hero& hero, string name)
{
    Cave cave;
    vector<string> names = {"Pirate Holdout", "Smugglers Den", "Fiends Den"};

    int caveLevel = hero.getLevel();
    int goldReward;

    cave.name = name;
    
    cave.enemies = EnemyFactory::createEnemy(hero.getLevel());
    for (const Enemy& e : cave.enemies)
    {
        goldReward += (e.getXp())*1.5;
    }

    cave.goldReward = goldReward;

    return cave;
}