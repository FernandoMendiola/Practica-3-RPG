#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(const char* _name, int _health, int _attack, int _defense, int _speed,int _level, int _experience, int _expnecesaria, int _originalhealth, int _originaldefense)
        : Character(_name, _health, _attack, _defense, _speed, _level, _experience, true) {
    level = 1;
    experience = 0;
    expnecesaria = 100;
    originalhealth = _originalhealth;
    originaldefense = _originaldefense;
}

void Player::doAttack(Character *target) {
    target->takeDamage(attack);
}

void Player::takeDamage(int damage) {
    int trueDamage = damage - defense;

    health -= trueDamage;

    if(trueDamage > 0){
        cout << name << " took " << trueDamage << " damage!" << endl;
        cout << "La salud de "<< name << " ahora es de "<< health << endl;
        if(health <= 0) {
            cout << name << " has been defeated!" << endl;
        }
    } else {
        cout << getName() << " ha defendido por completo el ataque." << endl;
    }

}
//TODO: Agrgar que el usuario tambien pueda seleccionar entre subir salud y defensa
void Player::levelUp() {
    char decision;
    if (level > 0) {
        cout << name << " ha subido a nivel " << (level + 1) << " ¿Quieres mejorar tu personaje? (y/n)" << endl;
        cin >> decision;

        if (decision == 'y' || decision == 'Y') {
            cout << "Tu salud de " << originalhealth << " ha mejorado a " << (originalhealth + 10) << endl;
            cout << "Tu defensa de " << originaldefense << " ha mejorado a " << (originaldefense + 10) << endl;

            health = originalhealth += 10;
            defense = originaldefense += 10;

            cout << "Selecciona qué estadística quieres mejorar (1,2):\n"
                 << "1. Velocidad: " << speed << "\n"
                 << "2. Ataque: " << attack << endl;

            int mejora;
            cin >> mejora;

            switch (mejora) {
                case 1:
                    speed += 10;
                    cout << "Tu velocidad ha mejorado a " << speed << " puntos" << endl;
                    break;
                case 2:
                    attack += 10;
                    cout << "Tu ataque ha mejorado a " << attack << " puntos" << endl;
                    break;
                default:
                    cout << "Opción inválida" << endl;
                    break;
            }
            level++;
        }
    }
}

void Player::gainExperience(int exp) {
    experience += exp;
    while(experience >= expnecesaria) {
        levelUp();
        expnecesaria += 50;
        if((experience = experience - expnecesaria) < 0 ){
            experience = 0;
        }
        else(
                experience = experience - experience
                );
        cout << "Experiencia necesaria para el siguiente nivel: " << expnecesaria << endl;
    }
    cout << "Experiencia restante: " << experience << endl;
}
int Player::getLevel() const {
    return level;
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
            currentAction.action = [this, target, enemies](){ // Captura la variable 'enemies' aquí
                doAttack(target);
                if(target->getHealth()<=0){
                    Enemy* enemigo = ((Enemy*)target);
                    if(enemigo->getExperience() + experience >= 100){
                        for (int i = 0; i < enemies.size(); i++) {
                            if(enemies[i]->getId() != enemigo->getId() && enemies.size() > 1) {
                                enemies[i]->UpAttack(1);
                            }
                        }
                    }
                    gainExperience(enemigo->getExperience());
                }
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