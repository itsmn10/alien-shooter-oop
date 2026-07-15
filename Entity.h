#ifndef ENTITY_H
#define ENTITY_H

// Abstract base class for every object that lives on the game board.
// Demonstrates: abstraction, encapsulation, pure virtual functions.
class Entity {
protected:
    int x, y;       // position on the console grid
    char symbol;    // character used to draw this entity
    bool alive;     // whether the entity is still active

public:
    Entity(int startX, int startY, char sym)
        : x(startX), y(startY), symbol(sym), alive(true) {}

    virtual ~Entity() {}

    // Pure virtual: every derived class must define its own movement/behavior.
    virtual void update() = 0;

    int getX() const { return x; }
    int getY() const { return y; }
    char getSymbol() const { return symbol; }
    bool isAlive() const { return alive; }
    void kill() { alive = false; }

    void setPosition(int newX, int newY) { x = newX; y = newY; }
};

#endif
