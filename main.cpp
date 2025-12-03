#include <iostream>
#include "clase.h"
#include <limits>
using namespace std;

int main() {
    Cat cat1("Magu", 50, 80, 30, 80);
    Cat cat2("Dracat Mihaita", 80, 20, 60, 50);
    Cat cat3("Lucius", 30, 90, 20, 90);
    Cat cat4("Sebi");

    CatOverlord overlord;
    overlord.addCat(cat1);
    overlord.addCat(cat2);
    overlord.addCat(cat3);
    overlord.addCat(cat4);

    Humanity humans;

    bool gameEnd = false;
    while (!gameEnd) {
        cout << "\n=== Current Stats ===\n";
        overlord.printStatus();
        overlord.sortCatsByEvilness();
        overlord.printCats();
        cout << humans << endl;

        cout << "\nChoose action:\n"
             << "1. Feed a cat\n"
             << "2. Encourage a cat\n"
             << "3. Train cat Evilness\n"
             << "4. Send cat on mission\n"
             << "5. Next day\n"
             << "6. Take cat to yoga\n"
             << "7. Cat special action\n"
             << "8. Quit\n> ";

        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        try {
            switch (choice) {
                case 1: overlord.feedCatInteractive(); break;
                case 2: overlord.encourageCatInteractive(); break;
                case 3:
                    overlord.trainCatEvilInteractive();
                    if (overlord.checkEvilnessGameOver()) gameEnd = true;
                    break;
                case 4: overlord.sendOnMissionInteractive(humans); break;
                case 5: overlord.nextDay(); cout << "Day advanced.\n"; break;
                case 6: overlord.calmCatInteractive(); break;
                case 7: {
                    int index;
                    cout << "Select cat index to perform action: ";
                    cin >> index;
                    if (index < 0 || index >= (int)overlord.getCats().size()) {
                        cout << "Invalid index!\n";
                        break;
                    }

                    vector<unique_ptr<CatAction>> actions;
                    actions.push_back(make_unique<StealFoodAction>());
                    actions.push_back(make_unique<SpreadChaosAction>());
                    actions.push_back(make_unique<RecruitCatsAction>(&overlord));

                    cout << "Select action:\n";
                    for (size_t i = 0; i < actions.size(); i++)
                        cout << i + 1 << ". " << actions[i]->name() << "\n";

                    int actChoice;
                    cin >> actChoice;
                    if (actChoice < 1 || actChoice > (int)actions.size()) {
                        cout << "Invalid action choice!\n";
                        break;
                    }

                    actions[actChoice - 1]->execute(overlord.getCats()[index], humans);
                    break;
                }
                case 8: gameEnd = true; break;
                default: cout << "Invalid choice!\n"; break;
            }
        } catch(const GameException& e) {
            cout << "Caught exception: " << e.what() << endl;
        }

        if (humans.isGameOver()) {
            cout << "Game Over! Humans discovered the cat conspiracy!\n";
            break;
        }
    }

    cout << "Thanks for playing! :3\n";
    return 0;
}
