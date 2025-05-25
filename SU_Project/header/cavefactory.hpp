#pragma once
#include "enemyfactory.hpp"
#include "hero.hpp"
#include "enemy.hpp"
#include <vector>
#include <random>
#include <iostream>
#include <string>

class Cavefactory {
    public: 
        struct Cave {
            string name;
            int goldReward;
            vector<Enemy> enemies;
        };

        static Cave createCave(const Hero& hero, string name);

};