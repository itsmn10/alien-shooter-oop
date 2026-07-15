#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

// Owns and coordinates the whole game: the board, all entities,
// spawning, collision detection, scoring, levels and game-over/restart.
class GameManager {
private:
    static const int WIDTH = 30;
    static const int HEIGHT = 20;

    Player player;
    std::vector<Enemy*> enemies;
    std::vector<Bullet*> bullets;

    int level;
    int enemiesDestroyed;
    int enemiesPerLevel;
    int spawnCounter;
    int spawnInterval;
    bool gameOver;

    void handleInput();
    void spawnEnemyIfNeeded();
    void updateEntities();
    void checkCollisions();
    void checkLevelProgress();
    void draw();
    void cleanupDead();

public:
    GameManager();
    ~GameManager();

    void run();     // main game loop
    void reset();   // restart state for a new game
};

#endif
