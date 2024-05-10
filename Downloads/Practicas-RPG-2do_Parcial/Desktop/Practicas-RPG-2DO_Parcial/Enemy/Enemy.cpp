//
// Created by Victor Navarro on 15/02/24.
//

#include "Enemy.h"
#include "../Utils.h"
#include <iostream>


using namespace std;
using namespace combat_utils;

Enemy::Enemy(const char *_name, int _health, int _attack, int _defense, int _speed, int _level, int _experience, int _ident)
        : Character(_name, _health, _attack, _defense, _speed, _level, _experience, false) {
    experience = _experience;
    ident = _ident;
    level = 0;
}

void Enemy::doAttack(Character *target) {
    target->takeDamage(getRolledAttack(attack));
}

void Enemy::takeDamage(int damage) {
    int trueDamage = damage - defense;
    health-= trueDamage;

    cout << name << " took " << trueDamage << " damage!" << endl;
    if(health <= 0) {
        cout << name << " has been defeated!" << endl;
    }
}
int Enemy::Levelup() {
        health += 5;
        attack += 5;
        defense += 5;
        speed += 0;
        level++;
        cout << name << " mejoró sus estadísticas ("<< level << ")" <<", ¡CUIDADO!!" << endl;
    }

void Enemy::GainExperience(Player& player){
    if (player.getLevel() > 0) {
        Levelup();
    }
}

int Enemy::getExperience() {
    return experience;
}
int Enemy::getId() {
    return ident;

}

Character* Enemy::selectTarget(vector<Player*> possibleTargets) {
    //target with less health
    int lessHealth = 9999999;
    Character* target = nullptr;
    for(auto character : possibleTargets) {
        if(character->getHealth() < lessHealth) {
            lessHealth = character->getHealth();
            target = character;
        }
    }
    return target;
}

Action Enemy::takeAction(vector<Player*> partyMembers) {
    int chance = 1+rand()%(101-1);
    Action currentAction;


    desDefense();


    if(getHealth() < getMaxhealth() * .55 && chance <= 70){
        currentAction.action = [this]() {
            defend();
        };
        currentAction.speed = 999999;

    } else {
        Character* target = selectTarget(partyMembers);
        currentAction.target = target;
        currentAction.action = [this, target](){
            doAttack(target);
        };
        currentAction.speed = getSpeed();

    }
    return currentAction;
}

