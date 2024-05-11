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
    int originalhealth;
    int originaldefense;
    int expnecesaria;
    void levelUp();
    void saveProgress();

public:
    Player(const char* _name, int _health, int originalhealth, int _attack, int _defense, int _originaldefense, int _speed, int _level, int _experience);
    Player(const char* _name, int _health, int _attack, int _defense, int _speed,
           int _level, int _experience, int _expnecesaria, int originalhealth, int originaldefense);
    void doAttack(Character *target) override;
    void takeDamage(int damage) override;
    Character* selectTarget(vector<Enemy*> possibleTargets);
    Action takeAction(vector<Enemy*> enemies);

    void gainExperience(int exp);
    int getLevel() const;    //TODO: Implement use object

    char* serialize();
    static Player* unserialize(char* buffer);

    static const unsigned int BUFFER_SIZE = sizeof(name) + sizeof (health) + sizeof(originalhealth) + sizeof(attack) + sizeof(defense) + sizeof(originaldefense) + sizeof(speed) + sizeof(isPlayer) + sizeof(level) + sizeof(experience);

private:
char buffer[Player::BUFFER_SIZE];
};

#endif //RPG_PLAYER_H
