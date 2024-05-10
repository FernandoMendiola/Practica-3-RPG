//
// Created by Victor Navarro on 15/02/24.
//

#include "Character.h"
#include <iostream>
#include <cstring> // Para strcpy
#include <cstdio> // Para sprintf

using namespace std;

Character::Character(const char *_name, int _health, int _attack, int _defense, int _speed, int _level, int _experience, bool _isPlayer) {
    strcpy(name, _name);
    health = _health;
    attack = _attack;
    defense = _defense;
    speed = _speed;
    isPlayer = _isPlayer;
    maxdefense = _defense;
    maxhealth = _health;
}

char* Character::getName() {
    return name;
}

int Character::getHealth() {
    return health;
}

int Character::getAttack() {
    return attack;
}

int Character::getDefense() {
    return defense;
}

int Character::getSpeed() {
    return speed;
}

char* Character::toString() {
    char* buffer = new char[256];
    sprintf(buffer, "Name: %s\nHealth: %d\nAttack: %d\nDefense: %d\nSpeed: %d", name, health, attack, defense, speed);
    return buffer;
}

bool Character::getIsPlayer() {
    return isPlayer;
}

//Comienza la implementacion del metodo defensa


void Character::defend(){
    cout<<getName()<< " incremento su defensa" << endl;
        defense += (maxdefense*0.2);
        cout<< "Defensa: "<< defense << endl;
}
int Character::getMaxhealth() {
    return maxhealth;
}
int Character::getMaxdefense() {
    return maxdefense;
}

void Character::UpAttack(int newStat) {
        attack = newStat + attack;

        cout<<name<<" su ataque ha aumentado en: "<<newStat<<endl;
    }

void Character::desDefense() {
    defense = maxdefense;
}
bool Character::flee(Character*target) {
    if (this->speed > target->speed)
        return true;

    int chance = rand() % 100;
    return chance > 30;
}
