#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

// The player-controlled spaceship.
class Player : public Entity {
private:
    int health;
    int score;
    int minX, maxX; // horizontal movement bounds

public:
    Player(int startX, int startY, int boundMinX, int boundMaxX)
        : Entity(startX, startY, 'A'), health(3), score(0),
          minX(boundMinX), maxX(boundMaxX) {}

    // Player has no automatic movement; update() is a no-op each tick,
    // movement happens in moveLeft/moveRight in response to input.
    void update() override {}

    void moveLeft() {
        if (x > minX) x--;
    }

    void moveRight() {
        if (x < maxX) x++;
    }

    void loseLife() { health--; }
    bool isDead() const { return health <= 0; }
    int getHealth() const { return health; }

    void addScore(int points) { score += points; }
    int getScore() const { return score; }
};

#endif
