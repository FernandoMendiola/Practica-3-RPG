#include "Player.h"
#include <iostream>
#include "../Files/FileHandler.h"
#include <cstring>
using namespace std;

void Player::saveProgress() {
    const char* buffer = this->serialize();

    // Copiar la cadena constante a un búfer mutable
    char mutableBuffer[Player::BUFFER_SIZE];
    strncpy(mutableBuffer, buffer, Player::BUFFER_SIZE);

    FileHandler fileHandler;
    fileHandler.writeToFile("PlayerInfo.data", const_cast<char*>(mutableBuffer), Player::BUFFER_SIZE);

    cout << "\n\tProgreso guardado !" << endl
         << "Stats:" << endl
         << this->toString() << endl;
}
Player::Player(const char* _name, int _health, int originalhealth, int _attack, int _defense, int _originaldefense, int _speed, int _level, int _experience): Character(_name, _health, _attack, _defense, _speed, _level, _experience, true) {

    level = 1;
    experience = 0;
}

Player::Player(const char* _name, int _health, int _attack, int _defense, int _speed,int _level, int _experience, int _expnecesaria, int _originalhealth, int _originaldefense)
        : Character(_name, _health, _attack, _defense, _speed, _level, _experience, true) {
    level = _level;
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
         << "2. Defend" << endl
         << "3. Save Progress" << endl; // Nueva opción para guardar progreso

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
                if(target->getHealth() <= 0) {
                    Enemy* enemigo = dynamic_cast<Enemy*>(target);
                    if(enemigo && (enemigo->getExperience() + experience >= 100)) {
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
        case 3:
            saveProgress();
            return takeAction(enemies);
        default:
            cout << "Invalid action" << endl;
            return takeAction(enemies);
    }

    return currentAction;
}

char* Player::serialize() {
    char* iterator = buffer;

    memcpy(iterator, &name, sizeof(name));
    iterator += sizeof(name);

    memcpy(iterator, &health, sizeof(health));
    iterator += sizeof(health);

    memcpy(iterator, &attack, sizeof(attack));
    iterator += sizeof(attack);

    memcpy(iterator, &originalhealth, sizeof(originalhealth));
    iterator += sizeof(originalhealth);

    memcpy(iterator, &defense, sizeof(defense));
    iterator += sizeof(defense);

    memcpy(iterator, &originaldefense, sizeof(originaldefense));
    iterator += sizeof(originaldefense);

    memcpy(iterator,&speed , sizeof(speed));
    iterator += sizeof(speed);

    memcpy(iterator, &isPlayer, sizeof(isPlayer));
    iterator += sizeof(isPlayer);

    memcpy(iterator, &level, sizeof(level));
    iterator += sizeof(level);

    memcpy(iterator, &experience, sizeof(experience));

    return buffer;
}

Player* Player::unserialize(char* buffer) {
    char* iterator = buffer;
    char name[30];
    int health, attack, originalhealth, defense, originaldefense, speed, level, experience;
    bool isPlayer;

    memcpy(&name, iterator, sizeof(name));
    iterator+=sizeof(name);

    memcpy(&health, iterator, sizeof(health));
    iterator+=sizeof(health);

    memcpy(&attack, iterator, sizeof(attack));
    iterator+=sizeof(attack);

    memcpy(&originalhealth, iterator, sizeof(originalhealth));
    iterator+=sizeof(originalhealth);

    memcpy(&defense, iterator, sizeof(defense));
    iterator+=sizeof(defense);

    memcpy(&originaldefense, iterator, sizeof(originaldefense));
    iterator+=sizeof(originaldefense);

    memcpy(&speed, iterator, sizeof(speed));
    iterator+=sizeof(speed);

    memcpy(&isPlayer, iterator, sizeof(isPlayer));
    iterator+=sizeof(isPlayer);

    memcpy(&level, iterator, sizeof(level));
    iterator += sizeof(level);

    memcpy(&experience, iterator, sizeof(experience));
    iterator += sizeof(experience);

    return new Player(name, health, originalhealth, attack, defense, originaldefense, speed, level, experience);
}