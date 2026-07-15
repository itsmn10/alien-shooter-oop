#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

// An alien enemy. Moves downward; speed increases with difficulty level.
class Enemy : public Entity {
private:
    int speed;      // how many ticks between each downward move
    int tickCount;  // internal counter to control speed
    bool reachedBottom;

public:
    Enemy(int startX, int startY, int enemySpeed)
        : Entity(startX, startY, 'W'), speed(enemySpeed), tickCount(0), reachedBottom(false) {}

    void update() override {
        tickCount++;
        if (tickCount >= speed) {
            y++;
            tickCount = 0;
        }
    }

    bool hasReachedBottom() const { return reachedBottom; }
    void markReachedBottom() { reachedBottom = true; kill(); }
};

#endif
