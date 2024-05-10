//
// Created by Victor Navarro on 15/02/24.
//
#pragma once
#ifndef RPG_PLAYER_H
#define RPG_PLAYER_H
#include "../Character/Character.h"
#include "../Enemy/Enemy.h"
#include "../Combat/Action.h"
#include <vector>

class Enemy;

class Player: public Character {
    //TODO: Implement Classes (Mage, Warrior, Rogue, etc..)
    //TODO: Implement Inventory
private:
    int level;
    int experience;
    int expnecesaria;
    int originalhealth;
    int originaldefense;
public:

    Player(const char* _name, int _health, int _attack, int _defense, int _speed,
           int _level, int _experience, int _expnecesaria, int originalhealth, int originaldefense);
    void doAttack(Character *target) override;
    void takeDamage(int damage) override;
    Character* selectTarget(vector<Enemy*> possibleTargets);
    Action takeAction(vector<Enemy*> enemies);

    void gainExperience(int exp);
    void levelUp();
    int getLevel() const;};    //TODO: Implement use object

#endif //RPG_PLAYER_H
