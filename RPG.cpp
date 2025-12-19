#include <iostream>

#include <fstream>

#include <iomanip>

using namespace std;

//Game
//Inputs will be numbers
enum State {
    MAIN,
    INTRO,
    DEAD,
    EXIT,
    QUIT
};
struct Character {
    string name;
    int damage;
    int health;
};
State intro(Character & player);

enum Skill {
    PA,
    ASS,
    IR
};

int main() {
    State currentState = MAIN;
    while (currentState != QUIT) {

        Character player;
        currentState = INTRO;
        switch (currentState) {
        case INTRO:
            currentState = intro(player);
            break;

        }
    } 
}

State intro(Character& player) {
    cout << "You have selected to play the RPG.\n";
    cout << "Please select your character's name.\n";
    cin >> player.name;
    cout << "Your eyes open as you take in your surroundings. The walls around you are bright white. Human bodies lay on the ground in front of you, dead or unconscious, you can't tell. You are in a line, second from the front.";
    return QUIT;
}

void fight() {

}