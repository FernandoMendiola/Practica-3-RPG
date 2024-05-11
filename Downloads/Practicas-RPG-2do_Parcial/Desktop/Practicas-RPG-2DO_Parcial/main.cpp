#include <iostream>
#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "Combat/Combat.h"
#include "Files/FileHandler.h"

using namespace std;

Player* loadPlayerInfo() {
    try {
        char buffer[Player::BUFFER_SIZE];
        FileHandler fileHandler;
        fileHandler.readFromFile("PlayerInfo.data", buffer, Player::BUFFER_SIZE);
        return Player::unserialize(buffer);
    } catch(const std::exception& e) {
        cerr << "Error al cargar la información del jugador desde el archivo: " << e.what() << endl;
        cerr << "Creando un nuevo jugador con valores predeterminados." << endl;
        return new Player("DefaultPlayer", 35, 10, 8, 3, 1, 0, 100, 35, 8);
    }
}

int main() {
    Player *player = loadPlayerInfo();
    Enemy *enemy = new Enemy("Bast", 5, 15, 2, 5, 10, 200, 0);
    Enemy *enemy2 = new Enemy("Demon", 5, 15, 2, 5, 10,200,0);

    std::vector<Character*> participants;
    participants.push_back(player);
    participants.push_back(enemy);
    participants.push_back(enemy2);

    Combat *combat = new Combat(participants);
    combat->doCombat();

    delete player;
    delete enemy;
    delete enemy2;
    delete combat;

    return 0;
}