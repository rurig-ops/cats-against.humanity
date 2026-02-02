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
    // 1. Initializari Template (GenericTracker)
    GenericTracker<int> moneyLog;
    moneyLog.log(100);

    GenericTracker<std::string> eventLog;
    eventLog.log("Game Session Started");

    // 2. Singleton & Dificultate
    cout << "Alege dificultatea jocului (1-3): ";
    int diff = 1;
    if (!(cin >> diff)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    GameSettings::getInstance().setDifficulty(diff);

    // 3. Functie sablon
    logGameEvent("Difficulty Level Set To", GameSettings::getInstance().getDifficulty());

    cout << "\nWelcome to Cat Overlord Game! :3" << endl;

    CatOverlord overlord(100, 0, 6);
    Humanity humans(0, 100);

    // Citire pisici din fisier
    ifstream fin("cats.txt");
    if (!fin) {
        cerr << "Warning: Can't open cats.txt! Starting with an empty roster.\n";
    } else {
        string name;
        int ev, c, h, l;
        while (fin >> name >> ev >> c >> h >> l) {
            overlord.addCat(Cat(name, ev, c, h, l));
        }
        fin.close();
    }

    overlord.sortCatsByEvilness();

    bool quit = false;
    // Loop-ul principal cu protectie pentru End-Of-File (EOF)
    while (!quit && !humans.isGameOver()) {
        if (cin.eof()) break; // Previne Stack Overflow pe GitHub Actions

        cout << "\n===== Status =====" << endl;
        overlord.printStatus();
        overlord.printCats();
        cout << humans << endl;

        cout << "\nChoose an action:" << endl;
        cout << "1. Feed a cat\n2. Encourage loyalty\n3. Train evilness\n4. Send cat on mission\n"
             << "5. Perform special action\n6. Send cat to spa\n7. End day\n8. Quit\n"
             << "Your choice: ";

        int choice;
        if (!(cin >> choice)) {
            if (cin.eof()) break;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        try {
            switch(choice) {
                case 1:
                    overlord.feedCatInteractive();
                    break;
                case 2:
                    overlord.encourageCatInteractive();
                    break;
                case 3:
                    overlord.trainCatEvilInteractive();
                    overlord.sortCatsByEvilness();
                    break;
                case 4:
                    overlord.sendOnMissionInteractive(humans);
                    overlord.sortCatsByEvilness();
                    break;
                case 5: {
                    overlord.printCats();
                    int ci, ai;
                    cout << "Select cat index: ";
                    if (!(cin >> ci)) break;

                    cout << "Select action index:\n";
                    for (size_t i = 0; i < overlord.getNumActions(); i++) {
                        cout << i << ". " << overlord.getActions()[i]->name() << "\n";
                    }
                    if (!(cin >> ai)) break;

                    overlord.performAction(ci, ai, humans);
                    break;
                }
                case 6:
                    overlord.calmCatInteractive();
                    break;
                case 7:
                    overlord.nextDay();
                    eventLog.log("Day ended");
                    break;
                case 8:
                    quit = true;
                    break;
                default:
                    cout << "Invalid option!" << endl;
                    break;
            }
        } catch (const GameException& e) {
            cout << "Game Error: " << e.what() << endl;
        }
    }

    cout << "\n--- Final Statistics ---" << endl;
    logGameEvent("Total Events Logged", eventLog.getTotalEntries());

    return 0;
}