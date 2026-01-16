#include <iostream>

#include <fstream>

#include <iomanip>

#include <windows.h>

#include <cstdlib>

#include <ctime>

using namespace std;

//Game
//Inputs will be numbers
enum State { //used for switch statement for rpg
    MAIN,
    INTRO,
    TOWN,
    SKILL,
    DEAD,
    QUIT
};

enum Skill { //used for character skills
    PA, //plot armor
    ASS, //assassin
    GS //gathering storm
};

struct Character {
    string name;
    int damage;
    int health;
    int maxHealth;
    Skill skill;
    int gold;
    int priority;
    int dodgeChance;
    int commonPotions;
};
State intro(Character & , int & , ofstream & ); 
State skill(Character & , int & , ofstream & );
State town(Character & , int & , ofstream & );
State dead();

void fight(Character & , Character & );
ofstream outFile("C:\\Users\\99210\\Documents\\GitHub\\Shape-Creator\\Both.txt");
int main() {
    int shapeCount = 0;
    int totalUses = 0;
    srand(static_cast < unsigned > (time(nullptr))); //randomizes seed
    bool mainMenu = true;

    if (outFile.is_open()) { //verifies file is open
        outFile << "Game started." << endl;
    } else {
        cout << "Failed to open file." << endl;
        cout << "Please check the file path and try again." << endl;
        return 1;
    }

    while (mainMenu) { //main menu loop
        cout << "Do you want to play the game or use the shape creator?\n(1) Play the game\n(2) Use the shape creator\n(3) Quit\n";
        int menuChoice;
        cin >> menuChoice;

        if (menuChoice == 1) { //starts rpg
            State currentState = INTRO;
            int playerRep = 50;
            int playerInf = 0; //influences dialogue choices
            currentState = INTRO;
            Character player;
            while (currentState != QUIT) {
                switch (currentState) {
                case INTRO:
                    currentState = intro(player, playerInf, outFile);
                    break;

                case SKILL:
                    currentState = skill(player, playerInf, outFile);
                    break;

                case TOWN:
                    currentState = town(player, playerInf, outFile);
                    break;

                case DEAD:
                    currentState = dead();
                    break;

                default:
                    currentState = QUIT;
                    break;
                }
            }

            cout << "Would you like to return to the main menu?\n(1) Yes\n(2) No\n";
            int menuSel;
            cin >> menuSel;
            if (menuSel == 1) {
                mainMenu = true;
                outFile << "User goes back to the main menu.\n";
            } else {
                outFile << "User exits the game from main menu.\n";
                mainMenu = false;
            }
            totalUses++;
        } else if (menuChoice == 2) {
            outFile << "User enters the shape creator from main menu.\n";
            bool cont = true;
            while (cont == true) {
                char character;
                int size;
                char shape;
                //asks for desired shape
                cout << "Please input the shape you want out of the following: s = square, t = triangle, d = diamond.\n";
                cin >> shape;
                //identifies shape
                if (shape == 's') { //square
                    cout << "You have selected: Square\nPlease input the character used to make up the square and the size.\n";
                    cin >> character;
                    cin >> size;
                    if (size > 0) {
                        for (int j = 1; j <= size; j++) {
                            for (int i = 1; i <= size; i++) {
                                outFile << character << setw(3);
                            }
                            outFile << "\n";
                        }
                        shapeCount++;
                    } else cout << "Invalid input for size.";
                } else if (shape == 't') { //triangle
                    char option;
                    //specifies triangle type
                    cout << "You have selected: Triangle\nPlease input one of the following letters: e = equilateral, r = right\n";
                    cin >> option;
                    //identifies type
                    if (option == 'e') { //equilateral
                        cout << "Please select the character that will make up the shape, and the size of a side, separated by spaces.\n";
                        cin >> character;
                        cin >> size;
                        if (size > 0) {
                            outFile << setw(1 + size * .5) << character << endl;
                            for (int i = 1; i <= (size * .433); i++) { //.433 is the rough estimate of amount of rows based on height and space between rows (.866/2)
                                outFile << setw(1 + size * .5 - i) << character;
                                outFile << setw(2 * i) << character << endl;
                            }
                            for (int i = 1; i <= size; i++) {
                                outFile << character;
                            }
                            outFile << endl;
                            shapeCount++;
                        } else {
                            cout << "Invalid size input.\n";
                        }
                    } else if (option == 'r') {
                        int height;
                        cout << "Please select the character that will make up the shape, and the length of the base, and the height, separated by spaces.\n";
                        cin >> character;
                        cin >> size;
                        cin >> height;
                        if (size > 0 && height > 0) {
                            outFile << character << endl;
                            for (int i = 1; i <= (height / 2.5); i++) { //rough estimate to help with space between rows(not applied in square creator)
                                outFile << character;
                                outFile << setw(i * 1.5) << character << endl;
                            }
                            for (int i = 1; i <= size; i++) {
                                outFile << character;
                            }
                            outFile << endl;
                            shapeCount++;
                        } else {
                            cout << "Invalid input for size.\n";
                        }
                    } else {
                        cout << "Invalid input.";
                    }
                } else if (shape == 'd') {
                    cout << "Please select the character that will make up the shape, and the size of a side, separated by spaces. (Diamond works best with larger numbers)\n";
                    cin >> character;
                    cin >> size;
                    if (size > 0) {
                        outFile << setw(1 + size * .5) << character << endl;
                        for (int i = 1; i <= (size * .433); i++) { //.433 is the rough estimate of amount of rows based on height and space between rows (.866/2)
                            outFile << setw(1 + size * .5 - i) << character;
                            outFile << setw(2 * i) << character << endl;
                        }
                        for (int i = (size * .43); i >= 1; i--) {
                            outFile << setw(1 + size * .5 - i) << character;
                            outFile << setw(2 * i) << character << endl;
                        }
                        outFile << setw(1 + size * .5) << character << endl;
                        outFile << endl;
                        shapeCount++;
                    } else {
                        cout << "Invalid input for size.\n";
                    }
                } else {
                    cout << "Invalid input.\n";
                }
                outFile << endl;
                char another;

                if (shapeCount == 1) {
                    cout << "You have created " << shapeCount << " shape.\n";
                } else {
                    cout << "You have created " << shapeCount << " shapes.\n";
                }
                bool next = false;
                while (next == false) {
                    cout << "Would you like to create another shape? (y = yes, n = no)\n";
                    cin >> another;
                    if (another == 'n') {
                        outFile << "-------------------------\n";
                        next = true;
                        cont = false;
                        string line;
                        ifstream inFile("C:\\Users\\99210\\Documents\\GitHub\\Shape-Creator\\Both.txt");

                        cout << "\nReading from \"C:\\Users\\99210\\Documents\\GitHub\\Shape-Creator\\Both.txt\"" << endl;
                        if (shapeCount == 0) {
                            cout << "You have created 0 shapes\n";
                        } else if (shapeCount == 1) {
                            cout << "You have created the following 1 shape: \n";
                        } else {
                            cout << "You have created the following " << shapeCount << " shapes: " << endl;
                        }
                        if (inFile.is_open()) {
                            while (getline(inFile, line)) { //reads line by line
                                cout << line << endl;
                            }
                            inFile.close();
                        } else {
                            cout << "Unable to open file for reading" << endl;
                        }
                    } else if (another == 'y') {
                        next = true;
                    } else {
                        cout << "Invalid input.\n";
                    }
                    totalUses++;
                }
            }
        } else if (menuChoice == 3) {
            outFile << "Player exits the program from main menu.\n";
            mainMenu = false;
        } else {
            cout << "Invalid input.\n";
        }
    }
    outFile << "Total uses of the program: " << totalUses << endl;
    outFile.close();
    return 0;
}

State intro(Character & player, int & playerInf, ofstream & log) {
    log << "Intro started. ";
    int sel;
    bool cont = false;
    cout << "Please select your character's name.\n";
    cin >> player.name;
    log << "Welcome, " << player.name << "!\n";
    player.gold = 0; //initializes Character player stats
    player.health = 100;
    player.maxHealth = 100;
    player.damage = 8;
    player.commonPotions = 0;
    player.priority = 2;
    cout << "Your eyes open as you take in your surroundings. You appear to be at the bottom of torch-lit ravine. Human bodies lay on the ground in front of you, dead or unconscious, you can't tell. You are in a line of people, second from the front.\n";
    cout << "An older man dressed in a completely white outfit in front of you glances back at you, eyes wide. His face is weathered, a large bruise is clear on his temple. He studies your face for a second before speaking.\n";
    cout << ">\"" << player.name << ", I'll find you, okay? Just please... stay alive. Do you understand?\"\n";
    cout << "Select:\n(1) Nod and say yes.\n(2) Deny knowing him.\n";
    cout << "[WARNING: Choices like this may influence the story.]\n";
    while (!cont) { //choice loop in case of invalid selections
        cin >> sel;
        if (sel == 1) {
            cout << "------------------------\n";
            cout << "You take a moment to gather your bearings, then nod and say yes.\nThe man smiles and appears calmer. He turns around and, after a moment, falls to the ground lifelessly.\n";
            log << player.name << " acknowledged the man, successfully avoiding suspicion from the [UNINTELLIGIBLE].\n";
            cont = true;
        } else if (sel == 2) {
            cout << "------------------------\n";
            cout << "You're overwhelmed by the situation. You make a weird face and shake your head. You tell him you don't know who he is.\nHe opens his mouth to say something, but suddenly falls to the ground lifelessly.\n";
            log << player.name << " denied knowing the man, resulting in being marked as an outsider by the [UNINTELLIGIBLE].\n";
            playerInf += 10;
            cont = true;
        } else {
            cout << "Invalid input.\n";
        }
    }
    cont = false;
    cout << "A man in a suit of dark armor beside you steps forward to push the man's body out of the way, and then steps back.\nA golden, shimmering orb is visible in front of you.\n";
    cout << "Select:\n(1) Touch the orb immediately.\n(2) Hesitate to touch it.\n";
    while (!cont) {
        cin >> sel;
        if (sel == 1) {
            cout << "------------------------\n";
            cout << "You glance at the figure of the dark knight before stepping forward to touch the orb. It slowly floats toward you. You feel a strong sense of repulsion despite its beautiful appearance, but still opt to place your palm on its surface.\n";
            log << player.name << " touched the orb without hesitation, demonstrating bravery.\n";
            cont = true;
        } else if (sel == 2) {
            cout << "------------------------\n";
            cout << "You hesitate to touch it. After a moment, a scream comes from near the back of the line. You glance back and see a jet-black cloud coming over the horizon.\nAn overwhelming sense of fear overcomes you. As you glance back toward the orb, you find it touching your hand.\n";
            log << player.name << " hesitated before touching the orb and sees what the world has come to.\n";
            cont = true;
        } else {
            cout << "Invalid input.\n";
        }
    }
    cont = false;
    cout << "Your vision immediately turns black.\n";
    log << "Intro ended.\n";
    log << "------------------------\n";
    cout << "[End of Part One: Intro]\nSelect:\n(1) Continue\n(2) Quit\n";
    while (!cont) {
        cin >> sel;
        if (sel == 1) {
            return SKILL;
        } else if (sel == 2) {
            return QUIT;
        } else {
            cout << "Invalid input.\n";
        }
    }
    cout << "how'd you get here?\n";
    return QUIT;
}

State skill(Character & player, int & playerInf, ofstream & log) {
    int sel;
    bool cont = false;
    cout << "-------------------------\n";
    cout << "Darkness surrounds you. You feel weightless, as if you're floating in midair.\n";
    cout << "After a moment, you can open your eyes again, but all that surrounds you is an infinite void.\n";

    if (playerInf > 0) { //outsider dialogue based on previous choice with the older man
        cout << "A melodic, seemingly feminine voice rings out in your ear.\n";
        cout << ">\"Another outsider? What a turn of events. Perhaps this is just what we needed, [UNINTELLIGIBLE].\"\n";
        cout << "A more masculine voice responds.\n";
        cout << ">\"I thought the same thing about the last one. [UNINTELLIGIBLE]'s death was truly saddening.\"\n";
        cout << ">\"That whole timeli- Ah, we seem to have limited time here. Let's see what this one picks.\"\n";
        log << player.name << " is identified as an outsider.\n";
    }

    cout << "Three light blue cards with text on them appear before you, beckoning for you to grab one.\n\n";

    cout << "Card 1: Plot Armor\n";
    cout << "You now have a 10% critical strike chance and a 50% chance of surviving a fatal attack at 1 health.\n\n";

    cout << "Card 2: Assassination\n";
    cout << "You always strike first in combat, dealing bonus damage.\n";
    cout << "In certain situations, one-shotting an enemy will prevent reputation loss.\n\n";

    cout << "Card 3: Gathering Storm\n";
    cout << "You now have a chance to dodge attacks.\n";
    cout << "Starting at 10%, this chance slowly increases over time.\n\n";

    cout << "Select a card (1-3):\n";

    while (!cont) { //card selection loop
        cin >> sel;

        if (sel == 1) {
            player.skill = PA;
            cout << "-------------------------\n";
            cout << "You reach for the first card.\n";
            cout << ">\"Interesting choice,\" a voice murmurs warmly.\n";
            log << player.name << " selected the Plot Armor card, granting a 10% critical strike chance and a 50% chance of surviving a fatal attack at 1 health.\n";
            cont = true;
        } else if (sel == 2) {
            player.skill = ASS;
            cout << "-------------------------\n";
            cout << "You snatch the second card without hesitation.\n";
            cout << ">\"Decisive,\" a voice notes quietly.\n";
            player.priority = 0;
            log << player.name << " selected the Assassination card, granting permanent attack priority and bonus damage on first strike in combat.\n";
            cont = true;
        } else if (sel == 3) {
            player.skill = GS;
            cout << "-------------------------\n";
            cout << "You hesitate before grabbing the third card.\n";
            cout << ">\"Fascinating,\" a voice whispers.\n";
            player.dodgeChance = 20;
            log << player.name << " selected the Gathering Storm card, granting a 20% chance to dodge attacks.\n";
            cont = true;
        } else {
            cout << "Invalid input.\n";
        }
    }

    cout << "\nThe cards dissolve into light.\n";
    cout << "Your senses snap back into place.\n";

    return TOWN;
}

State town(Character & player, int & playerInf, ofstream & log) {
    int sel;
    bool cont = false;
    bool explore = false;
    bool inn = false;
    bool shop = false;
    cout << "You find yourself in a small town. The sun is setting, and the air is filled with the scent of wood smoke and fresh bread. It's a nice contrast to the darkness you were just in.\n";
    if (playerInf == 0) {
        cout << "You feel a strange familiarity with this place, but a strong sense of loneliness.\n";
    } else {
        cout << "You're overwhelmed by the new environment.\n";
    }

    while (!cont) {
        if (explore && inn && shop) { //traps user in loop until all 3 options are done
            cont = true;
        } else {
            cout << "Select:\n(1) Explore the town\n(2) Visit the inn\n(3) Go to the market\n";
            cin >> sel;
            if (sel == 1) {
                cout << "-------------------------\n";
                cout << "You wander through the streets, admiring the small shops and friendly faces. The townsfolk seem welcoming, and you feel a sense of peace here.\n";
                explore = true;
            } else if (sel == 2) {
                cout << "-------------------------\n";
                cout << "You enter a cozy inn where you can rest and recover your health.\n";
                player.health = player.maxHealth;
                cout << "You exit the inn feeling refreshed and at full health.\n";
                inn = true;
            } else if (sel == 3) {
                cout << "-------------------------\n";
                cout << "You browse through various stalls selling goods from all over the realm. You find what appears to be a small shop selling magical items.\n";
                cout << "A barker in front of the shop shouts:\n";
                cout << ">\"Step right up! Mana-infused items for sale! Defend against the darkness!\"\n";
                cout << "You feel a strong urge to enter the shop, but realize you don't have enough gold to make any purchases. Perhaps you can come back later.\n";
                shop = true;
            } else {
                cout << "Invalid input.\n";
            }
        }
    }
    log << player.name << " has explored town, rested at the inn, and visited the market.\n";
    cont = false;

    if (playerInf == 10) {
        cout << "Having explored the town, rested at the inn, and visited the market, you feel a little aimless.\n";
        cout << "As you stand in the town square, contemplating your next move, a scream echoes through the air, coming from what you can identify as the town's shrine.\n";
        cout << "Without hesitation, you decide to head to the shrine to investigate the source of the scream.\n";
        log << player.name << " feels aimless due to incorrectly assimillating his body's memories.\n";
    } else {
        cout << "Having explored the town, rested at the inn, and visited the market, you decide to head to the town's shrine to pray.\n";
        cout << "As you approach the shrine, a sudden scream pierces the air, causing you to quicken your pace toward the source of the sound.\n";
        log << player.name << " feels a sense of purpose due to correctly assimillating his body's memories.\n";
    }

    cout << "You arrive at the shrine to find a dark, shadowy figure looming over a fallen priest. The figure turns to face you, its eyes glowing with a purple energy.\n";
    cout << "Without warning, the figure lunges at you, and you find yourself in combat!\n";
    Character goblin; //creates first enemy
    goblin.name = "Shadow Fiend";
    goblin.health = 80;
    goblin.maxHealth = 80;
    goblin.damage = 8;
    goblin.priority = 1; //sets who goes first in the fight unless player has assassination skill
    goblin.gold = 5;
    while (!cont) { //forces user to fight
        cout << "Select:\n(1) Fight\n";
        cin >> sel;
        if (sel == 1) {
            cont = true;
        } else {
            cout << "Invalid input. You must fight the Shadow Fiend!\n";
            log << player.name << " hesitated to fight the Shadow Fiend.\n";
        }
    }
    cont = false;
    fight(player, goblin);
    log << player.name << " has defeated the Shadow Fiend who endangered the priest.\n";
    cout << "-------------------------\n";
    if (player.health <= 0) { //checks if player lost fight
        cout << "-------------------------\n";
        cout << "You have been defeated by the Shadow Fiend. Your journey ends here.\n";
        cout << "[GAME OVER]\n";
        return DEAD;
    }
    cout << "With the Shadow Fiend defeated, the townsfolk emerge from their homes, expressing their gratitude for your bravery.\n";
    if (playerInf == 0) {
        cout << "The townsfolk recognize you as a hero, and your reputation in the town improves.\n";
        log << player.name << " is recognized as a hero by the townsfolk.\n";
    } else {
        cout << "Despite the townsfolk's gratitude, you still feel like an outsider here.\n";
        log << player.name << " feels out of place among the townsfolk despite their gratitude.\n";
    }
    cout << "The priest, though shaken, thanks you profusely for saving his life, and gives you a small reward.\n";
    cout << "You receive 20 gold.\n";
    player.gold += 20;
    cout << "Your current gold: " << player.gold << "\n";
    log << player.name << " received 5 gold from the Fiend and 20 gold from the priest, totaling 25 gold.\n";
    while (!cont) {
        if (player.health < player.maxHealth) {
            cout << "Select (Keep in mind your low health!):\n(1) Visit the inn\n(2) Go to the market\n(3) Find something to do\n";
        } else {
            cout << "Select:\n(1) Visit the inn\n(2) Go to the market\n(3) Move on\n";
        }
        cin >> sel;
        bool dagger = false;
        bool amulet = false;
        if (sel == 1) {
            cout << "-------------------------\n";
            cout << "You enter a cozy inn where you can rest and recover your health.\n";
            player.health = player.maxHealth; //restores health to full
            cout << "You exit the inn feeling refreshed and at full health.\n";
            log << player.name << " rested at the inn and restored health to full.\n";
        } else if (sel == 2) { //shop
            log << player.name << " returned to the magical item shop in the market.\n";
            cout << "-------------------------\n";
            cout << "You head back to the market. The magical item shop you visited earlier is still there.\n";
            cout << "With your newfound gold, you decide to enter the shop and see what items are available for purchase.\n";
            cout << "Upon entering, the barker greets you warmly and shows you a variety of mana-infused items that will aid you in your journey.\n\n";
            cout << "Items for Sale:\n";
            int itemSel;
            while (!cont) { //shop loop
                if (dagger) {
                    cout << "(1) Charged Dagger - SOLD OUT\n\n";
                } else {
                    cout << "(1) Charged Dagger (15 gold): Increases your damage by 3.\n\n";
                }
                if (amulet) {
                    cout << "(2) Charged Amulet - SOLD OUT\n\n";
                } else {
                    cout << "(2) Charged Amulet (10 gold): Increases your max health by 5.\n\n";
                }
                cout << "(3) Common Potion (5 gold): Restores 20 health when used.\n\n";
                cout << "Select an item to purchase (1-3) or 4 to exit:\n";
                cin >> itemSel;
                if (itemSel == 1) {
                    if (dagger) {
                        cout << "You have already purchased the Charged Dagger.\n";
                        continue;
                    } else if (player.gold >= 15) { //verifies enough gold
                        player.damage += 3; //increases damage
                        player.gold -= 15; //deducts gold
                        cout << "You purchased the Charged Dagger! Your damage is now " << player.damage << ".\n";
                        dagger = true;
                        log << player.name << " purchased the Charged Dagger, increasing damage to " << player.damage << ".\n";
                    } else {
                        cout << "You don't have enough gold for that item.\n";
                    }
                } else if (itemSel == 2) {
                    if (amulet) {
                        cout << "You have already purchased the Charged Amulet.\n";
                        continue;
                    } else if (player.gold >= 10) {
                        player.maxHealth += 5;
                        player.health += 5;
                        player.gold -= 10;
                        cout << "You purchased the Charged Amulet! Your max health is now " << player.maxHealth << ".\n";
                        amulet = true;
                        log << player.name << " purchased the Charged Amulet, increasing max health to " << player.maxHealth << ".\n";
                    } else {
                        cout << "You don't have enough gold for that item.\n";
                    }
                } else if (itemSel == 3) {
                    if (player.gold >= 5) {
                        player.commonPotions++;
                        player.gold -= 5;
                        cout << "You purchased a Common Potion! You now have " << player.commonPotions << " Common Potions.\n";
                        log << player.name << " purchased a Common Potion, totaling " << player.commonPotions << ".\n";
                    } else {
                        cout << "You don't have enough gold for that item.\n";
                    }
                } else if (itemSel == 4) {
                    cout << "You exit the shop.\n";
                    cont = true;
                    log << player.name << " exited the magical item shop.\n";
                } else {
                    cout << "Invalid input.\n";
                }
            }
            cont = false;
        } else if (sel == 3) {
            cout << "-------------------------\n";
            cout << "Having settled your affairs in town, you decide it's time to continue your journey.\n";
            cont = true;
            log << player.name << " decided to move on.\n";
        } else {
            cout << "Invalid input.\n";
        }
    }
    cont = false;
    cout << "As night falls, you head to the inn to rest for the night, preparing yourself for the adventures that lie ahead.\n";
    cout << "Luckily, the innkeeper offers you a free stay for your heroic deeds earlier.\n";
    cout << "The second you lay your head down, a sense of dread fills you as dark tendrils of shadow creep into the room, coalescing into a menacing figure.\n";
    cout << "The tendrils wrap around you, suffocating you.\n";
    cout << "Select:\n(1) Fight for your life!\n(2) Accept your fate [GAME OVER].\n";
    log << player.name << " is confronted by Shadow Tendrils at the inn.\n";
    while (!cont) {
        cin >> sel;
        if (sel == 1) {
            cont = true;
        } else if (sel == 2) {
            cout << "You accept your fate as the shadows consume you. Your journey ends here.\n";
            cout << "[GAME OVER]\n";
            log << player.name << " chooses cowardice, resulting in game over.\n";
            log << "-------------------------\n";
            return QUIT;
        } else {
            cout << "Invalid input.\n";
        }
    }
    cont = false;
    Character shadowTendrils; //creating unbeatable enemy
    shadowTendrils.name = "Shadow Tendrils";
    shadowTendrils.health = 999999;
    shadowTendrils.maxHealth = 999999;
    shadowTendrils.damage = 20;
    shadowTendrils.priority = 3;
    shadowTendrils.gold = 0;
    fight(player, shadowTendrils);
    log << player.name << " chose to fight the Shadow Tendrils.\n";
    log << player.name << " was defeated by the Shadow Tendrils.\n";
    cout << "-------------------------\n";
    cout << "Despite your best efforts, the Shadow Tendrils prove too powerful. They overwhelm you, and your vision fades to black as you succumb to their grasp.\n";
    cout << "You laugh maniacally as the darkness invades your mind.\n";
    cout << "Just as you feel yourself slipping away, an overwhelming sensation of peace washes over you.\n";
    cout << "After a few seconds, you realize you can still move your limbs and breathe.\n";
    if (playerInf == 0) {
        cout << "A familiar voice rings out in your ear.\n";
        cout << ">\"You were not meant to perish just yet.\"\n";
        cout << ">\"[UNINTELLIGIBLE] broke the rules of causality by interfering with your fate.\"\n";
        cout << ">\"Fear not, for we shall grant you another chance at life. Use it wisely this time.\"\n";
    } else {
        cout << "The melodic voice from before rings out in your ear once more.\n";
        cout << ">\"Fascinating. It appears your journey is not yet over.\"\n";
        cout << ">\"The threads of fate are tangled, but we shall grant you another chance.\"\n";
        cout << ">\"Make the most of it, outsider.\"\n";
    }
    log << player.name << " was granted a second chance at life by the [UNINTELLIGIBLE], awakening in the inn.\n";
    log << "-------------------------\n";
    cout << "You awaken back in the town inn, unharmed but shaken.\n";
    cout << "End of Demo. Thank you for playing!\n";
    log << "-------------------------\n";

    return QUIT; //the end
}

State dead() {
    cout << "Somehow, you died in a way that is impossible. Congratulations!\n";
    return QUIT;
}

void fight(Character & player, Character & enemy) {
    if (player.priority < enemy.priority) {
        // Player strikes first
        if (player.skill == ASS) { //assassin skill
            cout << "Thanks to your Assassination skill, you strike first for double the damage!\n";
            cout << player.name << " attacks " << enemy.name << " for " << player.damage * 2 << " damage.\n";
            enemy.health -= player.damage * 2;
        } else {
            cout << player.name << " attacks " << enemy.name << " for " << player.damage << " damage.\n";
            enemy.health -= player.damage;
        }
        if (enemy.health <= 0) {
            cout << enemy.name << " has been defeated!\n";
            return;
        }
        cout << enemy.name << "'s health: " << enemy.health << "\n";
    } else {
        cout << enemy.name << " strikes first!\n";
    }
    while (player.health > 0 && enemy.health > 0) {
        // Enemy's turn
        cout << enemy.name << " attacks " << player.name << " for " << enemy.damage << " damage.\n";
        if (player.skill == GS) { //gathering storm skill
            int dodgeChance = rand() % 100;
            if (dodgeChance < player.dodgeChance) {
                cout << player.name << " dodged the attack, taking no damage!\n";
            } else if (dodgeChance < player.dodgeChance + 5) {
                cout << player.name << " partially dodged the attack, taking half damage!\n";
                player.health -= (enemy.damage / 2);
            } else {
                player.health -= enemy.damage;
            }
        } else {
            player.health -= enemy.damage;
        }
        if (player.health <= 0) {
            if (player.skill == PA) { //plot armor skill
                int surviveChance = rand() % 100;
                if (surviveChance < 50) {
                    player.health = 1;
                    cout << player.name << "'s Plot Armor skill activated! They survive the fatal attack with 1 health!\n";
                } else {
                    cout << player.name << " has been defeated!\n";
                    return;
                }
            } else {
                cout << player.name << " has been defeated!\n";
                return;
            }
        }
        cout << player.name << "'s health: " << player.health << "\n";

        // Player's turn
        if (player.skill == PA) { //plot armor critical strike
            int critChance = rand() % 100;
            if (critChance < 10) {
                cout << "Critical strike! ";
                cout << player.name << " attacks " << enemy.name << " for " << player.damage * 2 << " damage.\n";
                enemy.health -= player.damage * 2;
            } else {
                cout << player.name << " attacks " << enemy.name << " for " << player.damage << " damage.\n";
                enemy.health -= player.damage;
            }
        } else {
            cout << player.name << " attacks " << enemy.name << " for " << player.damage << " damage.\n";
            enemy.health -= player.damage;
        }
        if (enemy.health <= 0) {
            cout << enemy.name << " has been defeated!\n";
            cout << "You receive " << enemy.gold << " gold.\n";
            player.gold += enemy.gold;
            return;
        }
        cout << enemy.name << "'s health: " << enemy.health << "\n";
        Sleep(1500);
    }
}