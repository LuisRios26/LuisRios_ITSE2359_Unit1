#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int MIN_STAT = 1;
const int MAX_STAT = 20;
const int MAX_LEVEL = 10;

int main() {
    int choice = 0;
    bool keepRunning = true;

    bool characterCreated = false;
    string name = "";
    int classChoice = 0;
    string className = "";
    int level = 1;

    // Base stats
    int baseStr = 0, baseInt = 0, baseDex = 0, baseCon = 0;

    // Current stats used for calculations (after class bonus and level ups)
    int str = 0, intl = 0, dex = 0, con = 0;

    // class bonus values (display)
    int bonusStr = 0, bonusInt = 0, bonusDex = 0, bonusCon = 0;

    // Combat stats
    int hp = 0, mp = 0, def = 0;
    double atk = 0.0;

    do {
        // MAIN MENU
        cout << "\n=== GAMESTAT CHARACTER MANAGER ===\n";
        cout << "1. Create New Character\n";
        cout << "2. View Character Stats\n";
        cout << "3. Calculate Combat Ratings\n";
        cout << "4. Level Up Character\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        // Validate input 
        while (cin.fail() || choice < 1 || choice > 5) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid. Please enter a number from 1 to 5: ";
            cin >> choice;
        }
        cin.ignore(10000, '\n'); 

        switch (choice) {
            case 1: {
                cout << "\n=== CREATE NEW CHARACTER ===\n";
                cout << "Enter character name: ";
                getline(cin, name);
                cout << "\nSelect class:\n";
                cout << "1. Warrior\n";
                cout << "2. Mage\n";
                cout << "3. Rogue\n";
                cout << "4. Cleric\n";
                cout << "Enter choice (1-4): ";
                cin >> classChoice;

                while (cin.fail() || classChoice < 1 || classChoice > 4) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid choice. Enter 1-4: ";
                    cin >> classChoice;
                }
                cin.ignore(10000, '\n');

                level = 1;
                bonusStr = bonusInt = bonusDex = bonusCon = 0;

                // Name and Bonus
                switch (classChoice) {
                    case 1:
                        className = "Warrior";
                        bonusStr = 2;
                        break;
                    case 2:
                        className = "Mage";
                        bonusInt = 2;
                        break;
                    case 3:
                        className = "Rogue";
                        bonusDex = 2;
                        break;
                    case 4:
                        className = "Cleric";
                        bonusCon = 2;
                        break;
                }

                cout << "\nEnter base stats (1-20):\n";

                // Strength
                cout << "Strength: ";
                cin >> baseStr;
                while (cin.fail() || baseStr < MIN_STAT || baseStr > MAX_STAT) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid. Enter Strength (1-20): ";
                    cin >> baseStr;
                }

                // Intelligence
                cout << "Intelligence: ";
                cin >> baseInt;
                while (cin.fail() || baseInt < MIN_STAT || baseInt > MAX_STAT) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid. Enter Intelligence (1-20): ";
                    cin >> baseInt;
                }

                // Dexterity
                cout << "Dexterity: ";
                cin >> baseDex;
                while (cin.fail() || baseDex < MIN_STAT || baseDex > MAX_STAT) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid. Enter Dexterity (1-20): ";
                    cin >> baseDex;
                }

                // Constitution
                cout << "Constitution: ";
                cin >> baseCon;
                while (cin.fail() || baseCon < MIN_STAT || baseCon > MAX_STAT) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid. Enter Constitution (1-20): ";
                    cin >> baseCon;
                }
                cin.ignore(10000, '\n');

                // Apply class bonus
                str = baseStr + bonusStr;
                intl = baseInt + bonusInt;
                dex = baseDex + bonusDex;
                con = baseCon + bonusCon;
                characterCreated = true;
                cout << "\nCharacter created successfully!\n";
                cout << className << " class bonus applied.\n";
                break;
            }

            case 2: {
                // VIEW STATS
                if (!characterCreated) {
                    cout << "\nError: Create a character first (Option 1).\n";
                    break;
                }

                cout << "\n=== CHARACTER PROFILE ===\n";
                cout << "Name: " << name << "\n";
                cout << "Class: " << className << "\n";
                cout << "Level: " << level << "\n\n";

                cout << "Base Stats:\n";

                string labels[4] = {"Strength", "Intelligence", "Dexterity", "Constitution"};
                int baseVals[4] = {baseStr, baseInt, baseDex, baseCon};
                int bonusVals[4] = {bonusStr, bonusInt, bonusDex, bonusCon};
                int finalVals[4] = {str, intl, dex, con};

                for (int i = 0; i < 4; i++) {
                    cout << "  " << left << setw(13) << labels[i] << ": "
                         << right << setw(3) << baseVals[i];

                    if (bonusVals[i] != 0) {
                        cout << " (+" << bonusVals[i] << " Class Bonus) = " << finalVals[i];
                    }
                    cout << "\n";
                }

                cout << "\nCombat Stats:\n";
                cout << "  (Use option 3 to calculate and view combat ratings.)\n";
                break;
            }

            case 3: {
                if (!characterCreated) {
                    cout << "\nError: Create a character first (Option 1).\n";
                    break;
                }

                cout << "\n=== COMBAT RATINGS ===\n";
                cout << "Calculating stats for: " << name << " (Level " << level << " " << className << ")\n\n";

                hp = (con * 10) + (level * 5);
                mp = (intl * 10) + (level * 3);

                // Class bonuses
                if (classChoice == 1) { // Warrior
                    hp += 20;
                }
                if (classChoice == 2) { // Mage
                    mp += 30;
                }

                switch (classChoice) {
                    case 1: atk = str * 1.5; break;                 // Warrior
                    case 2: atk = intl * 1.3; break;                // Mage
                    case 3: atk = dex * 1.4; break;                 // Rogue
                    case 4: atk = (str + intl) * 0.8; break;        // Cleric
                }

                // Defense
                def = (con + dex) / 2;

                // Display
                cout << "Health Points: " << hp << " (Constitution " << con << " x 10 + Level " << level << " x 5";
                if (classChoice == 1) cout << " + Warrior Bonus 20";
                cout << ")\n";

                cout << "Mana Points:   " << mp << " (Intelligence " << intl << " x 10 + Level " << level << " x 3";
                if (classChoice == 2) cout << " + Mage Bonus 30";
                cout << ")\n";

                cout << "Attack Power:  " << fixed << setprecision(1) << atk << " (Class formula)\n";
                cout << "Defense:       " << def << " ((Constitution " << con << " + Dexterity " << dex << ") / 2)\n";
                break;
            }

            case 4: {
                // LEVEL UP
                if (!characterCreated) {
                    cout << "\nError: Create a character first (Option 1).\n";
                    break;
                }

                cout << "\n=== LEVEL UP ===\n";
                cout << "Current Level: " << level << "\n";

                if (level >= MAX_LEVEL) {
                    cout << "You are max level. Congratulations. (" << MAX_LEVEL << ").\n";
                    break;
                }

                int oldStr = str, oldInt = intl, oldDex = dex, oldCon = con;

                level++;

                // Increase stats
                int stats[4] = {str, intl, dex, con};
                for (int i = 0; i < 4; i++) {
                    stats[i] += 1;
                }
                str = stats[0];
                intl = stats[1];
                dex = stats[2];
                con = stats[3];

                cout << "New Level: " << level << "\n\n";
                cout << "Stats increased by +1:\n";
                cout << "Strength:     " << oldStr << " -> " << str << "\n";
                cout << "Intelligence: " << oldInt << " -> " << intl << "\n";
                cout << "Dexterity:    " << oldDex << " -> " << dex << "\n";
                cout << "Constitution: " << oldCon << " -> " << con << "\n";

                cout << "\nCombat stats recalculated! (Use option 3 to view.)\n";
                break;
            }

            case 5:
                cout << "\nThanks you for using GameStat! Goodbye!\n";
                keepRunning = false;
                break;
        }

    } while (keepRunning);

    return 0;
}
