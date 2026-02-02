#include "CatOverlord.h"
#include "Cat.h"
#include "Humanity.h"
#include "Exceptions.h"
#include "GameSettings.h"
#include "GenericTracker.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

int main() {
    // trackere loguri
    GenericTracker<int> moneyLog;
    GenericTracker<string> eventLog;
    eventLog.log("game session started");

    // setare dificultate
    cout << "alege dificultatea (1-3): ";
    int diff = 1;
    if (!(cin >> diff)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    GameSettings::getInstance().setDifficulty(diff);

    cout << "\nwelcome to cat overlord game! :3" << endl;

    CatOverlord overlord(100, 0, 6);
    Humanity humans(0, 100);

    // citire date pisici
    ifstream fin("cats.txt");
    if (fin) {
        string name;
        int ev, c, h, l;
        while (fin >> name >> ev >> c >> h >> l) {
            overlord.addCat(Cat(name, ev, c, h, l));
        }
        fin.close();
    } else {
        cout << "eroare: nu am gasit fisierul cats.txt!" << endl;
        overlord.addCat(Cat("operative_zero", 10, 10, 5, 5));
    }

    // sortare initiala
    overlord.sortCatsByEvilness();

    bool quit = false;
    while (!quit && !humans.isGameOver()) {
        if (cin.eof()) break;

        cout << "\n--- status ---" << endl;
        overlord.printStatus();
        overlord.printCats();
        cout << humans << endl;

        cout << "\nactions: 1.feed 2.loyalty 3.train 4.mission 5.special 6.spa 7.next day 8.quit" << endl;
        cout << "your choice: ";

        int choice = 0;
        if (!(cin >> choice)) {
            if (cin.eof()) break;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        try {
            switch(choice) {
                case 1: overlord.feedCatInteractive(); break;
                case 2: overlord.encourageCatInteractive(); break;
                case 3: overlord.trainCatEvilInteractive(); break;
                case 4: overlord.sendOnMissionInteractive(humans); break;
                case 5: {
                    int ci = -1, ai = -1;
                    cout << "cat index: ";
                    if (!(cin >> ci)) { cin.clear(); cin.ignore(1000, '\n'); break; }

                    cout << "action index:" << endl;
                    for (size_t i = 0; i < overlord.getNumActions(); i++)
                        cout << i << ". " << overlord.getActions()[i]->name() << "\n";

                    if (!(cin >> ai)) { cin.clear(); cin.ignore(1000, '\n'); break; }
                    overlord.performAction(ci, ai, humans);
                    break;
                }
                case 6: overlord.calmCatInteractive(); break;
                case 7:
                    overlord.nextDay();
                    eventLog.log("day ended");
                    break;
                case 8: quit = true; break;
                default: cout << "invalid choice!" << endl;
            }
        } catch (const GameException& e) {
            cout << "error: " << e.what() << endl;
        }
    }

    // statistici finale
    cout << "\n--- final statistics ---" << endl;
    overlord.printStatus();
    logGameEvent("total events logged", eventLog.getTotalEntries());
    cout << "game over. humans state: " << (humans.isGameOver() ? "defeated" : "survived") << endl;

    return 0;
}