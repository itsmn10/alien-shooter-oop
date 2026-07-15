#include "GameManager.h"
#include <iostream>
#include <conio.h>    // _kbhit, _getch  (Windows / Dev-C++ / Turbo C++)
#include <windows.h>  // Sleep, system("cls")
#include <cstdlib>

using namespace std;

GameManager::GameManager()
    : player(WIDTH / 2, HEIGHT - 1, 0, WIDTH - 1),
      level(1), enemiesDestroyed(0), enemiesPerLevel(5),
      spawnCounter(0), spawnInterval(15), gameOver(false) {}

GameManager::~GameManager() {
    for (Enemy* e : enemies) delete e;
    for (Bullet* b : bullets) delete b;
}

void GameManager::reset() {
    for (Enemy* e : enemies) delete e;
    for (Bullet* b : bullets) delete b;
    enemies.clear();
    bullets.clear();

    player = Player(WIDTH / 2, HEIGHT - 1, 0, WIDTH - 1);
    level = 1;
    enemiesDestroyed = 0;
    spawnCounter = 0;
    spawnInterval = 15;
    gameOver = false;
}

void GameManager::handleInput() {
    if (_kbhit()) {
        char key = _getch();
        switch (key) {
            case 'a': case 'A':
                player.moveLeft();
                break;
            case 'd': case 'D':
                player.moveRight();
                break;
            case ' ':
                // Fire a bullet from the player's current position
                bullets.push_back(new Bullet(player.getX(), player.getY() - 1));
                break;
            case 'q': case 'Q':
                gameOver = true;
                break;
        }
    }
}

void GameManager::spawnEnemyIfNeeded() {
    spawnCounter++;
    if (spawnCounter >= spawnInterval) {
        spawnCounter = 0;
        int spawnX = rand() % WIDTH;
        // Higher level -> lower "speed" value -> enemy moves down more often -> harder
        int enemySpeed = max(2, 8 - level);
        enemies.push_back(new Enemy(spawnX, 0, enemySpeed));
    }
}

void GameManager::updateEntities() {
    player.update();
    for (Enemy* e : enemies) e->update();
    for (Bullet* b : bullets) b->update();

    // Enemies that reach the bottom cost the player a life
    for (Enemy* e : enemies) {
        if (e->isAlive() && e->getY() >= HEIGHT - 1) {
            e->markReachedBottom();
            player.loseLife();
        }
    }
}

void GameManager::checkCollisions() {
    for (Bullet* b : bullets) {
        if (!b->isAlive()) continue;
        for (Enemy* e : enemies) {
            if (!e->isAlive()) continue;
            if (b->getX() == e->getX() && b->getY() == e->getY()) {
                b->kill();
                e->kill();
                player.addScore(10);
                enemiesDestroyed++;
            }
        }
    }

    // Enemy collides directly with the player
    for (Enemy* e : enemies) {
        if (e->isAlive() && e->getX() == player.getX() && e->getY() == player.getY()) {
            e->kill();
            player.loseLife();
        }
    }

    if (player.isDead()) {
        gameOver = true;
    }
}

void GameManager::checkLevelProgress() {
    if (enemiesDestroyed >= enemiesPerLevel * level) {
        level++;
        spawnInterval = max(5, spawnInterval - 2); // enemies spawn faster each level
    }
}

void GameManager::cleanupDead() {
    for (size_t i = 0; i < enemies.size(); ) {
        if (!enemies[i]->isAlive()) {
            delete enemies[i];
            enemies.erase(enemies.begin() + i);
        } else {
            i++;
        }
    }
    for (size_t i = 0; i < bullets.size(); ) {
        if (!bullets[i]->isAlive()) {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
        } else {
            i++;
        }
    }
}

void GameManager::draw() {
    system("cls");

    // Build a blank board
    vector<string> board(HEIGHT, string(WIDTH, '.'));

    for (Enemy* e : enemies) {
        if (e->isAlive()) board[e->getY()][e->getX()] = e->getSymbol();
    }
    for (Bullet* b : bullets) {
        if (b->isAlive()) board[b->getY()][b->getX()] = b->getSymbol();
    }
    board[player.getY()][player.getX()] = player.getSymbol();

    cout << "Score: " << player.getScore()
         << "   Health: " << player.getHealth()
         << "   Level: " << level << "\n";
    cout << string(WIDTH, '-') << "\n";
    for (int row = 0; row < HEIGHT; row++) {
        cout << board[row] << "\n";
    }
    cout << string(WIDTH, '-') << "\n";
    cout << "Controls: A = left, D = right, SPACE = fire, Q = quit\n";
}

void GameManager::run() {
    while (!gameOver) {
        handleInput();
        spawnEnemyIfNeeded();
        updateEntities();
        checkCollisions();
        checkLevelProgress();
        cleanupDead();
        draw();
        Sleep(80); // controls overall game speed
    }

    cout << "\n=== GAME OVER ===\n";
    cout << "Final Score: " << player.getScore() << "\n";
    cout << "Level Reached: " << level << "\n";
}
