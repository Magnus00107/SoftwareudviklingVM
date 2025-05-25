#pragma once
#include "enemy.hpp"
#include <vector>
#include <random>
#include <iostream>

class EnemyFactory {
    public: 
        static vector<Enemy> createEnemy(int heroLevel);

};