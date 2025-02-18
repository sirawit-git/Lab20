#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<iomanip>

using namespace std;

class Equipment {
    int hpmax;
    int atk;
    int def;
public:
    Equipment(int hp, int attack, int defense) : hpmax(hp), atk(attack), def(defense) {}
    vector<int> getStat() {
        return {hpmax, atk, def};
    }
};

class Unit {
    string name;
    string type;
    int hp;
    int hpmax;
    int atk;
    int def;
    bool guard_on;
    bool dodge_on;
    Equipment* equipment; 
public:
    Unit(string t, string n);
    void showStatus();
    void newTurn();
    int attack(Unit&);
    int ultimateAttack(Unit&);
    int beAttacked(int);
    int heal();
    void guard();
    void dodge();
    bool isDead();
    void equip(Equipment*);
};

Unit::Unit(string t, string n) {
    type = t;
    name = n;
    if (type == "Hero") {
        hpmax = rand() % 20 + 120;
        atk = rand() % 5 + 14;
        def = rand() % 3 + 9;
    } else if (t == "Monster") {
        hpmax = rand() % 20 + 250;
        atk = rand() % 5 + 25;
        def = rand() % 3 + 5;
    }
    hp = hpmax;
    guard_on = false;
    dodge_on = false;
    equipment = NULL;
}

void Unit::showStatus() {
    if (type == "Hero") {
        cout << "---------------------------------------\n";
        cout << name << "\n";
        cout << "HP: " << hp << "/" << hpmax << "\tATK: " << atk << "\t\tDEF: " << def;
        cout << "\n---------------------------------------\n";
    } else if (type == "Monster") {
        cout << "\t\t\t\t---------------------------------------\n";
        cout << "\t\t\t\t" << name << "\n";
        cout << "\t\t\t\tHP: " << hp << "\t\tATK: " << atk << "\t\tDEF: " << def;
        cout << "\n\t\t\t\t---------------------------------------\n";
    }
}


void Unit::dodge() {
    dodge_on = true;
}

int Unit::beAttacked(int oppatk) {
    int dmg = 0;
    if (dodge_on) {
        int dodgeChance = rand() % 2;
        if (dodgeChance == 1) {
            return 0;
        } else {
            dmg = (oppatk-def)*2;
        }
    }

    else if (oppatk > def) {
        dmg = oppatk - def;
        if (guard_on) dmg = dmg / 3;
    }

    hp -= dmg;
    if (hp <= 0) hp = 0;

    return dmg;
}


void Unit::newTurn() {
    guard_on = false;
    dodge_on = false;
}


int Unit::attack(Unit& opp) {
    return opp.beAttacked(atk);
}

int Unit::ultimateAttack(Unit& opp) {
    return opp.beAttacked(atk * 2);
}

int Unit::heal() {
    int h = rand() % 21 + 10;
    if (hp + h > hpmax) h = hpmax - hp;
    hp += h;
    return h;
}

void Unit::guard() {
    guard_on = true;
}



bool Unit::isDead() {
    return hp <= 0;
}



void drawScene(char p_action, int p, char m_action, int m) {
    cout << "                                                       \n";
    if (p_action == 'A') {
        cout << "                                       " << -p << "\n";
    } else {
        cout << "                                                       \n";
    }
    cout << "                                *               *      \n";
    cout << "                                **  *********  **      \n";
    cout << "                                ****         ****      \n";
    if (m_action == 'A') {
        cout << "                 " << setw(5) << -m << "           *** **   ** ***       Attack!\n";
    } else if (m_action == 'G') {
        cout << "                                 *** **   ** ***       Guard!\n";
    } else if (m_action == 'D') {
        cout << "                                 *** **   ** ***       Dodge!\n";
    } else if (m_action == 'U') {
        cout << "                 " << setw(5) << -m << "           *** **   ** ***       Ultimate Attack!\n";
    } else {
        cout << "                                 *** **   ** ***       \n";
    }
    cout << "                                  ** **   ** **        \n";
    cout << "                   ***             *         *         \n";
    if (p_action == 'A') {
        cout << "        Attack!    ***  *           *********          \n";
    } else if (p_action == 'H') {
        cout << "      Heal! +" << setw(2) << p << "    ***  *           *********          \n";
    } else if (p_action == 'G') {
        cout << "         Guard!    ***  *           *********          \n";
    } else if (p_action == 'D') {
        cout << "         Dodge!    ***  *           *********          \n";
    } else {
        cout << "                   ***  *           *********          \n";
    }
    cout << "                    *  *       ***  *  *  *            \n";
    cout << "                  *****           **   *   *           \n";
    cout << "                    *                  *    ***        \n";
    cout << "                   * *               **        *       \n";
    cout << "                  *   *                                \n";
    cout << "                                                       \n";
}

void playerWin() {
    cout << "*******************************************************\n";
    for (int i = 0; i < 3; i++) cout << "*                                                     *\n";
    cout << "*                   YOU WIN!!!                        *\n";
    for (int i = 0; i < 3; i++) cout << "*                                                     *\n";
    cout << "*******************************************************\n";
}

void playerLose() {
    cout << "*******************************************************\n";
    cout << "*                                                     *\n";
    cout << "*                   YOU LOSE!!!                       *\n";
    cout << "*                                                     *\n";
    cout << "*******************************************************\n";
}