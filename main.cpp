#include "clase.h"
#include <iostream>
using namespace std;

int main(){
    cout<<"Welcome to Cat Overlord Game! :3"<<endl;
    CatOverlord overlord(100,0,6);
    Humanity humans(0,100);

    // adaugam cativa motani initiali
    overlord.addCat(Cat("Sebi"));
    overlord.addCat(Cat("Dracat"));
    overlord.addCat(Cat("Lucius"));

    // sortam pisicile dupa maleficitate
    overlord.sortCatsByEvilness();

    bool quit=false;
    while(!quit && !humans.isGameOver()){
        cout<<"\n===== Status ====="<<endl;
        overlord.printStatus();
        overlord.printCats();
        cout<<humans<<endl;
        cout<<"=================="<<endl;

        cout<<"\nChoose an action:"<<endl;
        cout<<"1. Feed a cat"<<endl;
        cout<<"2. Encourage loyalty"<<endl;
        cout<<"3. Train evilness"<<endl;
        cout<<"4. Send cat on mission"<<endl;
        cout<<"5. Perform special action"<<endl;
        cout<<"6. End day"<<endl;
        cout<<"7. Quit"<<endl;
        cout<<"8. Send cat to Spa"<<endl;
        int choice; cin>>choice;

        try{
            switch(choice){
                case 1: overlord.feedCatInteractive(); break;
                case 2: overlord.encourageCatInteractive(); break;
                case 3: overlord.trainCatEvilInteractive(); break;
                case 4: overlord.sendOnMissionInteractive(humans); break;
                case 5:{
                    overlord.printCats();
                    cout<<"Select cat index: "; int ci; cin>>ci;
                    cout<<"Select action:\n";
                    for(size_t i=0;i<overlord.getNumActions();i++) cout<<i<<". "<<overlord.getActions()[i]->name()<<"\n";
                    int ai; cin>>ai;
                    overlord.performAction(ci,ai,humans);
                    break;
                }
                case 6: overlord.nextDay(); break;
                case 7: quit=true; break;
                default: cout<<"Invalid option!"<<endl;
                case 8:
                    overlord.sendCatToSpaInteractive();
                    break;
            }
        } catch(const GameException& e){
            cout<<"Error: "<<e.what()<<endl;
        }
    }

    if(humans.isGameOver()) cout<<"Game over! Humans discovered the cat overlord plans!"<<endl;
    else cout<<"Thanks for playing! :3"<<endl;

    return 0;
}
