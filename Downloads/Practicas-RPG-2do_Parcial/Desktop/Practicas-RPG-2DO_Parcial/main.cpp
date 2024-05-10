#include <iostream>
#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "Combat/Combat.h"


int main() {
    Player *player = new Player("Ryu", 35, 10, 8, 3, 1, 0, 100, 35, 8);
    Enemy *enemy = new Enemy("Bast", 5, 15, 2, 5, 10, 200, 0);
    Enemy *enemy2 = new Enemy("Demon", 5, 15, 2, 5, 10,200,0);

    vector<Character*> participants;

    participants.push_back(player);
    participants.push_back(enemy);
    participants.push_back(enemy2);

    Combat *combat = new Combat(participants);
    combat->doCombat();

    delete player;
    delete enemy;
    delete combat;
    return 0;
}
