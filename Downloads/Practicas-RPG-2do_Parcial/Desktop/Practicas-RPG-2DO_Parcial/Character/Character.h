#ifndef RPG_CHARACTER_H
#define RPG_CHARACTER_H

class Character {
protected:
    char name[30]{}; // Cambiado a char array para almacenar nombres de hasta 29 caracteres más el carácter nulo terminador
    int health;
    int attack;
    int defense;
    int speed;
    bool isPlayer;
    int maxdefense;
    int maxhealth;

public:
    Character(const char *_name, int _health, int _attack, int _defense, int _speed, int _level, int _experience, bool _isPlayer);
    virtual void doAttack(Character *target) = 0;
    virtual void takeDamage(int damage) = 0;

    //TODO: Implementar metodo de defensa
    //Incrementar la defensa un 20% solo por el turno actual

    bool flee(Character* target);
    char* getName();
    int getHealth();
    int getAttack();
    int getDefense();
    bool getIsPlayer();
    int getSpeed();

    void UpAttack(int newstat);

    void defend();
    int getMaxhealth();
    int getMaxdefense();
    void desDefense();
    char* toString();
};

#endif // RPG_CHARACTER_H