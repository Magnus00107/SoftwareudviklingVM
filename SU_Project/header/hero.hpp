#include <string>
using namespace std;

class Hero {
    public:

    //Service functions
    Hero(const string& name);

    void attack(class Enemy& enemy);

    void takeDamage(int dmg);

    void changeXP(int xp);

    void levelUp();

    //Getter function
    bool isAlive() const;

    string getName() const;

    int getLevel();

    int getXp();

    int getHp();

    int getAtkDmg();
    
    private:
        bool alive;
        string name;
        int xp;
        int level;
        int hp;
        int atkdmg;
};