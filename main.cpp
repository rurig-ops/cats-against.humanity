#include <iostream>
#include "clase.h"
#include <limits>
using namespace std;

int main() {
    Cat cat1("Magu", 50, 80, 30, 80);
    Cat cat2("Dracat Mihaita", 80, 20, 60, 50);
    Cat cat3("Lucius", 30, 90, 20, 90);
    Cat cat4("Sebi");

    // Constructor copiere și operator=
    //Cat copyCat = cat1;
   // Cat assignedCat("Temp");
    //assignedCat = cat2;

    CatOverlord overlord;
    overlord.addCat(cat1);
    overlord.addCat(cat2);
    overlord.addCat(cat3);
    overlord.addCat(cat4);
   // overlord.addCat(copyCat);
   // overlord.addCat(assignedCat);

    Humanity humans;

    bool gameEnd = false;
    while (!gameEnd) {
        cout << "\n stats \n";
        overlord.printStatus();
        overlord.sortCatsByEvilness();
        overlord.printCats();
        cout << humans << endl;

        cout << "\nChoose action:\n"<< "1. Feed a cat\n"<< "2. Encourage a cat\n"<< "3. Train cat Evilness\n"<< "4. Send cat on mission\n"
             << "5. Next day\n"<< "6. Take cat to yoga\n"<< "7. Quit\n> ";
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                overlord.feedCatInteractive();
                break;
            case 2:
                overlord.encourageCatInteractive();
                break;
            case 3:
                overlord.trainCatEvilInteractive();
                if (overlord.checkEvilnessGameOver()) gameEnd = true;
                break;
            case 4:
                overlord.sendOnMissionInteractive(humans);
                break;
            case 5:
                overlord.nextDay();
                cout << "Day advanced.\n";
                break;
            case 6:
                overlord.calmCatInteractive();
                break;
            case 7:
                gameEnd = true;
                break;
            default:
                cout << "Invalid choice!\n";
                break;
        }

        if (humans.isGameOver()) {
            cout << "Game Over! Humans discovered the cat conspiracy!\n";
            break;
        }
    }

    cout << "Thanks for playing! :3\n";
    return 0;
}