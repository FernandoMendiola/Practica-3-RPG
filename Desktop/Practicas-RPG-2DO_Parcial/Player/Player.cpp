#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(const char* _name, int _health, int _attack, int _defense, int _speed,int _level, int _experience)
        : Character(_name, _health, _attack, _defense, _speed, _level, _experience, true) {
    level = 1;
    experience = 0;
}

void Player::doAttack(Character *target) {
    target->takeDamage(attack);
}

void Player::takeDamage(int damage) {
    int trueDamage = damage - defense;

    health-= trueDamage;

    if(trueDamage > 0){
        cout << name << " took " << trueDamage << " damage!" << endl;

        if(health <= 0) {
            cout << name << " has been defeated!" << endl;
        }
    } else {
        cout << getName() << " ha defendido por completo el ataque." << endl;
    }
}

void Player::levelUp() {
    char decision;
    if (level > 0) {
        cout << name << " ha subido a nivel " << (level + 1) << " Quieres mejorar tu personaje(y/n)?" << endl;
        cin >> decision;

        switch (decision) {
            case 'Y':
            case 'y':
                cout << "Selecciona que stadistica quieres mejorar (1,2,3,4):\n" <<"Salud: " <<health << "\nAtaque: " << attack << "\nDefensa: " << defense
                     << "\nVelocidad: " << speed << endl;
                int mejora;
                cin >> mejora;
                switch (mejora) {
                    case 1 :
                        health += 10;
                        cout << "tu salud a mejorado ha " << health << " puntos" << endl;
                        break;
                    case 2 :
                        attack += 10;
                        cout << "tu ataque a mejorado ha " << attack << " puntos" << endl;
                        break;
                    case 3 :
                        defense += 10;
                        cout << "tu defensa a mejorado ha " << defense << " puntos" << endl;
                        break;
                    case 4 :
                        speed += 10;
                        cout << "tu velocidad a mejorado ha" << speed << " puntos" <<endl;
                        break;
                }
                level++;
                break;
            case 'N':
            case 'n' :
                break;
            default:
                cout << "Seleccion no valida" << endl;
        }
        cout << "Experiencia restante: " << experience << endl;
    }
}

void Player::gainExperience(int exp) {
    experience += exp;
    if (experience >= 100) {
        levelUp();
    }
}

Character* Player::selectTarget(vector<Enemy*> possibleTargets) {
    int selectedTarget = 0;
    cout << "Select a target: " << endl;
    for (int i = 0; i < possibleTargets.size(); i++) {
        cout << i << ". " << possibleTargets[i]->getName() << endl;
    }

    //TODO: Add input validation
    cin >> selectedTarget;
    return possibleTargets[selectedTarget];
}

Action Player::takeAction(vector<Enemy*> enemies) {
    int action = 0;
    cout << "Select an action: " << endl
         << "1. Attack" << endl
         << "2. Defend" << endl;

    //TODO: Validate input
    cin >> action;
    Action currentAction;
    Character* target = nullptr;

    desDefense();
    switch(action) {
        case 1:
            target = selectTarget(enemies);
            currentAction.target = target;
            currentAction.action = [this, target](){
                doAttack(target);
            };
            currentAction.speed = getSpeed();
            break;
        case 2:
            currentAction.action = [this](){
                defend();
            };
            currentAction.speed = 9999999;
            break;
        default:
            cout << "Invalid action" << endl;
            break;
    }

    return currentAction;
}