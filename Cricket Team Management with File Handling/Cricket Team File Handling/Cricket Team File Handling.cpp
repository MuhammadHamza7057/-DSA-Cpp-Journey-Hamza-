#include <iostream>
#include <deque>
#include <string>
#include <fstream> // For file handling
#include <filesystem> // To ensure directory exists
using namespace std;

// Class to represent a Player
class Player {
public:
    string name;
    int matchesPlayed;
    int totalScore;

    Player(string name, int matches, int score)
        : name(name), matchesPlayed(matches), totalScore(score) {}
};

// Class to manage the cricket team
class CricketTeam {
private:
    deque<Player> team;
    const int MAX_PLAYERS = 30;
    const string FILE_NAME = "E:\\BSE-3A\\DSA Lab\\Cricket Team File Handling\\player_information.txt";  // Fixed the file name

public:
    CricketTeam() {
        ensureDirectoryExists();
        loadFromFile(); // Load players from file at program startup
    }

    ~CricketTeam() {
        saveToFile(); // Save players to file before exiting
    }

    // Add a player to the team
    void addPlayer() {
        if (team.size() >= MAX_PLAYERS) {
            cout << "Error: Team is full! Cannot add more players.\n";
            return;
        }

        string name;
        int matches, score;

        cout << "Enter player name: ";
        cin.ignore();
        getline(cin, name);

        matches = getInput("Enter matches played: ");
        score = getInput("Enter total score: ");

        team.push_back(Player(name, matches, score));
        cout << "Player added successfully!\n";
    }

    // Remove a player by name
    void removePlayer() {
        if (team.empty()) {
            cout << "Error: Team is empty! No players to remove.\n";
            return;
        }

        string name;
        cout << "Enter the name of the player to remove: ";
        cin.ignore();
        getline(cin, name);

        for (auto it = team.begin(); it != team.end(); ++it) {
            if (it->name == name) {
                team.erase(it);
                cout << "Player removed successfully!\n";
                return;
            }
        }

        cout << "Error: Player not found in the team.\n";
    }

    // View all players in the team
    void viewPlayers() const {
        if (team.empty()) {
            cout << "No players in the team.\n";
            return;
        }

        cout << "Team Players:\n";
        cout << "--------------------------------\n";
        for (const auto& player : team) {
            cout << "Name: " << player.name
                << ", Matches: " << player.matchesPlayed
                << ", Total Score: " << player.totalScore << endl;
        }
        cout << "--------------------------------\n";
    }

    // Update a player's performance
    void updatePerformance() {
        if (team.empty()) {
            cout << "Error: Team is empty! No players to update.\n";
            return;
        }

        string name;
        cout << "Enter the name of the player to update: ";
        cin.ignore();
        getline(cin, name);

        for (auto& player : team) {
            if (player.name == name) {
                player.matchesPlayed = getInput("Enter new matches played: ");
                player.totalScore = getInput("Enter new total score: ");
                cout << "Player performance updated successfully!\n";
                return;
            }
        }

        cout << "Error: Player not found in the team.\n";
    }

    // Search for a player by name
    void searchPlayer() const {
        if (team.empty()) {
            cout << "Error: Team is empty! No players to search for.\n";
            return;
        }

        string name;
        cout << "Enter the name of the player to search: ";
        cin.ignore();
        getline(cin, name);

        for (const auto& player : team) {
            if (player.name == name) {
                cout << "Player Found:\n";
                cout << "Name: " << player.name
                    << ", Matches: " << player.matchesPlayed
                    << ", Total Score: " << player.totalScore << endl;
                return;
            }
        }

        cout << "Error: Player not found in the team.\n";
    }

private:
    // Helper function to get validated input
    int getInput(const string& prompt) {
        int value;
        while (true) {
            cout << prompt;
            cin >> value;
            if (!cin.fail() && value >= 0) {
                cin.ignore(1000, '\n');
                return value;
            }
            cout << "Error: Invalid input! Please enter a positive number.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }

  void ensureDirectoryExists() {
    const char* dirPath = "E:\\BSE-3A\\DSA Lab\\Cricket Team File Handling";

    // Check if the directory exists
    if ((dirPath) == 0) {
        cout << "Directory created successfully or already exists.\n";
    } else {
        cout << "Error: Unable to create directory.\n";
    }
}


    // Load player data from the file
    void loadFromFile() {
        ifstream file(FILE_NAME);
        if (!file.is_open()) {
            cout << "Warning: No file found. A new file will be created when data is saved.\n";
            return;
        }

        string name;
        int matches, score;
        while (getline(file, name, ',') && file >> matches && file.ignore() && file >> score) {
            file.ignore(1);  // Ignore the newline character after reading the score
            team.push_back(Player(name, matches, score));
        }

        file.close();
        cout << "Players loaded from file.\n";
    }

    // Save player data to the file
    void saveToFile() const {
        ofstream file(FILE_NAME);
        if (!file.is_open()) {
            cout << "Error: Unable to save data to file. Check your path or permissions.\n";
            return;
        }

        for (const auto& player : team) {
            file << player.name << "," << player.matchesPlayed << "," << player.totalScore << "\n";
        }

        file.close();
        cout << "Player data saved successfully.\n";
    }
};

// Main function
int main() {
    CricketTeam teamManager;
    int choice;

    do {
        cout << "=====================================\n";
        cout << "||         CRICKET TEAM            ||\n";
        cout << "||         MANAGEMENT SYSTEM       ||\n";
        cout << "=====================================\n";
        cout << "|| 1. Add Player                   ||\n";
        cout << "|| 2. Remove Player                ||\n";
        cout << "|| 3. View All Players             ||\n";
        cout << "|| 4. Update Performance           ||\n";
        cout << "|| 5. Search Player                ||\n";
        cout << "|| 6. Exit                         ||\n";
        cout << "=====================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 6) {
            cout << "Error: Invalid choice! Please select a valid option from the menu.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (choice) {
        case 1:
            teamManager.addPlayer();
            break;
        case 2:
            teamManager.removePlayer();
            break;
        case 3:
            teamManager.viewPlayers();
            break;
        case 4:
            teamManager.updatePerformance();
            break;
        case 5:
            teamManager.searchPlayer();
            break;
        case 6:
            cout << "Exiting the program. Goodbye!\n";
            break;
        default:
            cout << "Error: Unknown error occurred.\n";
        }
    } while (choice != 6);

    return 0;
}
