#include "GameManager.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand((unsigned int)time(0));

    GameManager game;
    char choice;

    do {
        game.run();
        cout << "\nPlay again? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            game.reset();
        }
    } while (choice == 'y' || choice == 'Y');

    cout << "Thanks for playing!\n";
    return 0;
}
