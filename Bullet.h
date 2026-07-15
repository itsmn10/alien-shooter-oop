#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"

// A bullet fired by the player. Moves straight upward each tick.
class Bullet : public Entity {
public:
    Bullet(int startX, int startY) : Entity(startX, startY, '|') {}

    void update() override {
        y--; // move upward
        if (y < 0) {
            kill(); // left the top of the screen
        }
    }
};

#endif
