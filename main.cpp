#include "clase.h"
#include <iostream>
#include<fstream>
using namespace std;

int main() {
    cout << "Welcome to Cat Overlord Game! :3" << endl;
    CatOverlord overlord(100, 0, 6);
    Humanity humans(0, 100);

    ifstream fin("cats.txt");
    if (!fin) {
        cerr << "Can't open cats.txt!\n";
        return 1;
    }

    string name;
    int ev, c, h, l;

    while (fin >> name) {
        if (fin >> ev >> c >> h >> l) {
            overlord.addCat(Cat(name, ev, c, h, l));
        } else {
            fin.clear();
            overlord.addCat(Cat(name));
        }
    }

    overlord.sortCatsByEvilness();

    bool quit = false;
    while (!quit && !humans.isGameOver()) {
        cout << "\n===== Status =====" << endl;
        overlord.printStatus();
        overlord.printCats();
        cout << humans << endl;
        cout << "Total cats: " << Cat::getTotalCats() << endl;

        cout << "\nChoose an action:" << endl;
        cout << "1. Feed a cat" << endl;
        cout << "2. Encourage loyalty" << endl;
        cout << "3. Train evilness" << endl;
        cout << "4. Send cat on mission" << endl;
        cout << "5. Perform special action" << endl;
        cout << "6. Send cat to spa" << endl;
        cout << "7. End day" << endl;
        cout << "8. Quit" << endl;

        int choice; cin >> choice;
        try {
            switch(choice) {
                case 1: overlord.feedCatInteractive(); break;
                case 2: overlord.encourageCatInteractive(); break;
                case 3: overlord.trainCatEvilInteractive();
                        overlord.sortCatsByEvilness();
                        break;
                case 4: overlord.sendOnMissionInteractive(humans);
                        overlord.sortCatsByEvilness();
                        break;
                case 5: {
                    overlord.printCats();
                    cout << "Select cat index: "; int ci; cin >> ci;
                    cout << "Select action:\n";
                    for (size_t i = 0; i < overlord.getNumActions(); i++)
                        cout << i << ". " << overlord.getActions()[i]->name() << "\n";
                    int ai; cin >> ai;
                    overlord.performAction(ci, ai, humans);
                    break;
                }
                case 6: overlord.calmCatInteractive(); break;
                case 7: overlord.nextDay(); break;
                case 8: quit = true; break;
                default: cout << "Invalid option!" << endl;
            }
        } catch (const GameException& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    if (humans.isGameOver())
        cout << "Game over! Humans discovered the cat overlord plans!" << endl;
    else
        cout << "Thanks for playing! :3" << endl;

    return 0;
}
