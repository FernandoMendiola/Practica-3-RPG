#include "Combat.h"
#include <string>
#include <iostream>
#include <utility>

bool compareSpeed(Character *a, Character *b) {
    return a->getSpeed() > b->getSpeed();
}

Combat::Combat(std::vector<Character *> _participants) {
    participants = std::move(_participants);
    for(auto participant : participants) {
        if (participant->getIsPlayer()) {
            partyMembers.push_back((Player *) participant);
        } else {
            enemies.push_back((Enemy *) participant);
        }
    }
}

Combat::Combat(std::vector<Player*> _partyMembers, std::vector<Enemy*> _enemies) {
    partyMembers = std::move(_partyMembers);
    enemies = std::move(_enemies);
    participants = std::vector<Character*>();
    participants.insert(participants.end(), partyMembers.begin(), partyMembers.end());
    participants.insert(participants.end(), enemies.begin(), enemies.end());
}

Combat::Combat() {
    participants = std::vector<Character*>();
}

void Combat::addParticipant(Character *participant) {
    participants.push_back(participant);
    if(participant->getIsPlayer()){
        partyMembers.push_back((Player*) participant);
    } else {
        enemies.push_back((Enemy*) participant);
    }
}

void Combat::combatPrep() {
    // Sort participants by speed
    std::sort(participants.begin(), participants.end(), compareSpeed);
}

std::string Combat::toString() {
    std::string result = "";
    for (auto it = participants.begin(); it != participants.end(); it++){
        result += std::string((*it)->toString()) + "\n";
    }
    std::cout << "====================" << std::endl;
    return result;
}

Character* Combat::getTarget(Character* attacker) {
    std::vector<Character*>::iterator it;
    for(it = participants.begin(); it != participants.end(); it++){
        if((*it)->getIsPlayer() != attacker->getIsPlayer()){
            return *it;
        }
    }
    //TODO: Handle this exception
    return nullptr;
}

void Combat::doCombat() {
    std::cout << "Inicio del combate" << std::endl;
    combatPrep();
    int round = 1;
    //Este while representa las rondas del combate
    while (enemies.size() > 0 && partyMembers.size() > 0) {
        std::cout << "Round " << round << std::endl;
        std::vector<Character*>::iterator it = participants.begin();
        registerActions(it);
        executeActions(it);

        round++;
    }

    if (enemies.empty()) {
        std::cout << "You win!" << std::endl;

    } else {
        std::cout << "You lose!" << std::endl;
    }

}

void Combat::executeActions(std::vector<Character*>::iterator participant) {
    while (!actionQueue.empty()) {
        Action currentAction = actionQueue.top();
        currentAction.action();
        actionQueue.pop();

        //Check if there are any dead characters
        if (currentAction.target != nullptr) {
            checkParticipantStatus(*participant);
            checkParticipantStatus(currentAction.target);
        }
    }
}

void Combat::checkParticipantStatus(Character *participant) {
    if(participant->getHealth() <= 0) {
        if(participant->getIsPlayer()) {
            partyMembers.erase(std::remove(partyMembers.begin(), partyMembers.end(), participant), partyMembers.end());
        } else {
            enemies.erase(std::remove(enemies.begin(), enemies.end(), participant), enemies.end());
        }
        participants.erase(std::remove(participants.begin(), participants.end(), participant), participants.end());
    }
}

void Combat::registerActions(std::vector<Character*>::iterator participantIterator) {
    //Este while representa el turno de cada participante
    //La eleccion que cada personaje elije en su turno
    while(participantIterator != participants.end()) {
        if((*participantIterator)->getIsPlayer()) {
            Action playerAction = ((Player*) *participantIterator)->takeAction(enemies);
            actionQueue.push(playerAction);
        } else {
            Action enemyAction = ((Enemy*) *participantIterator)->takeAction(partyMembers);
            actionQueue.push(enemyAction);
        }

        participantIterator++;
    }
}