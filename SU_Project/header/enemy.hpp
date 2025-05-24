#include <string>
using namespace std;

class Enemy {
    public:
        //Service functions
        Enemy(const string& name, int hp, int atkdmg, int xp, bool alive);

        void attack(class Hero& hero);

        void takeDamage(int dmg);

        bool isAlive() const;

        //Getter functions:
        string getName() const;

        int getXp();

        int getHp();

        int getAtkDmg();

    private:
        string name;
        int xp;
        int hp;
        int atkdmg;
        bool alive;
};