#include "CatOverlord.h"
#include "Cat.h"
#include "Humanity.h"
#include "Exceptions.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    cout << "Welcome to Cat Overlord Game! :3" << endl;

    // Inițializare joc
    CatOverlord overlord(100, 0, 6);
    Humanity humans(0, 100);

    // Citire pisici din fișier
    ifstream fin("cats.txt");
    if (!fin) {
        cerr << "Warning: Can't open cats.txt! Starting with an empty roster.\n";
    } else {
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
        fin.close();
    }

    overlord.sortCatsByEvilness();

    bool quit = false;
    while (!quit && !humans.isGameOver()) {
        cout << "\n===== Status =====" << endl;
        overlord.printStatus();
        overlord.printCats();
        cout << humans << endl;
        cout << "Total cats in hierarchy: " << Cat::getTotalCats() << endl;

        cout << "\nChoose an action:" << endl;
        cout << "1. Feed a cat" << endl;
        cout << "2. Encourage loyalty" << endl;
        cout << "3. Train evilness" << endl;
        cout << "4. Send cat on mission" << endl;
        cout << "5. Perform special action (Polymorphism)" << endl;
        cout << "6. Send cat to spa" << endl;
        cout << "7. End day" << endl;
        cout << "8. Quit" << endl;
        cout << "Your choice: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        try {
            switch(choice) {
                case 1: overlord.feedCatInteractive(); break;
                case 2: overlord.encourageCatInteractive(); break;
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
        }
        // Tratarea excepțiilor separat, conform feedback-ului
        catch (const NotEnoughMoneyException& e) {
            cout << "\033[1;31mFinancial Error: " << e.what() << "\033[0m" << endl;
        }
        catch (const NotEnoughAPException& e) {
            cout << "\033[1;33mAction Point Error: " << e.what() << "\033[0m" << endl;
        }
        catch (const InvalidCatIndexException& e) {
            cout << "\033[1;31mSelection Error: " << e.what() << "\033[0m" << endl;
        }
        catch (const GameException& e) {
            cout << "Game Error: " << e.what() << endl;
        }
        catch (const exception& e) {
            cout << "Unexpected System Error: " << e.what() << endl;
        }
    }

    if (humans.isGameOver())
        cout << "\n!!! GAME OVER !!!\nHumans discovered the cat overlord plans!" << endl;
    else
        cout << "\nThanks for playing, Overlord! :3" << endl;

    return 0;
}