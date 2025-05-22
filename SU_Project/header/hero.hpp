#include <string>
using namespace std;

class Hero {
    public:

    Hero(const string& name);

    void attack(class Enemy& enemy);

    

    
    private:
    string name;
    int xp;
    int level;
    int hp;
    int atkdmg
}