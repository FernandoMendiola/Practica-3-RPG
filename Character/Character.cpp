//
// Created by Victor Navarro on 15/02/24.
//

#include "Character.h"
#include <iostream>

using namespace std;

Character::Character(string _name, int _health, int _attack, int _defense, int _speed, bool _isPlayer) {
    name = _name;
    health = _health;
    attack = _attack;
    defense = _defense;
    speed = _speed;
    isPlayer = _isPlayer;
    maxdefense = _defense;
    maxhealth = _health;

}

string Character::getName() {
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

string Character::toString() {
    return "Name: " + name + "\nHealth: " + to_string(health) + "\nAttack: " + to_string(attack) + "\nDefense: " + to_string(defense) + "\nSpeed: " + to_string(speed);
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
void Character::desDefense() {
    defense = maxdefense;
}
bool Character::flee(Character*target) {
    if (this->speed > target->speed)
        return true;

    int chance = rand() % 100;
    return chance > 30;
}
