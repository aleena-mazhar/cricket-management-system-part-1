#include<iostream> //used to perform input output operation
#include<fstream>  //used for file handling
#include<string>  //to use string datatype
#include<iomanip> //to use setw we include this library

using namespace std;

const int arraySize = 4; // Set array size for id, matches, runs, and sixes
const int numPlayers = 11; // Set the number of players, you can change this as needed
int rows = 0;

struct Player
{
    int id;
    string name;
    string team;
    string role;
};

struct Playersinfo
{
    Player data;
    int matches;
    int runs;
    int sixes;
};

struct Playersrecord
{
    Player data;
    Playersinfo data1;
    double average;
};

Player player;
Playersinfo playersinfo;
Playersrecord playersrecord;


void addfunction()

{

    ofstream fout; //to use file for storing output
    fout.open("players.txt", ios::app); //giving file name and also using append with it
    if (fout.is_open()) {
        cout << "enter player id = "; //asking user to enter player id 
        cin >> player.id; //storing value in id
        cout << "enter player name = "; //asking user to enter player id 
        cin >> player.name;  //storing value in name
        cout << "enter player team = "; //asking user to enter player id 
        cin >> player.team; //storing value in team
        cout << "enter player role = "; //asking user to enter player id 
        cin >> player.role; //storing value in role
        fout << player.id << setw(15) << player.name << setw(15) << player.team << setw(15) << player.role << endl; //storing values of all variables in file 
        // setw() is used to enter specified spaces between variables and entities 
        fout.close(); // closing the file
    }
    else {
        cout << "Error in opening file" << endl;//if there will be some error in opening in file it will display this message
    }
}


void viewfuntion()
{
    ifstream fin; //to use file for taking input
    fin.open("players.txt"); //opening file with the file name
    int id; //declraing variables
    string name; //declraing variables
    string team; //declraing variables 
    string role; //declraing variables
    //fin >> id >> name >> team >> role; //reading the values of variables from the file
    cout << "ID" << "\t" << setw(10) << "NAME" << "\t" << setw(10) << "TEAM" << "\t" << setw(10) << "ROLE" << endl; //displaying 
    //cout << id << "\t" << setw(10) << name << "\t" << setw(10) << team << "\t" << setw(10) << role << endl; //displaying
    while (fin >> id >> name >> team >> role) //using loop so we read every value from the file one by one 
    {
        // cout << "ID" << "\t" << setw(10) << "NAME" << "\t" << setw(10) << "TEAM" << "\t" << setw(10) << "ROLE" << endl; // displaying every variable and its entities 
        cout << id << "\t" << setw(10) << name << "\t" << setw(10) << team << "\t" << setw(10) << role << endl;  // displaying every variable and its entities
    }
    fin.close(); // closing the file

}
void findplayer()
{
    string IDIn, IDFile, record; //declraing variables
    cout << "Enter ID of player to find: "; //asking user to enter the id he wants to find
    cin >> IDIn; //storing value in IDIn

    ifstream fin; //to use file for taking input
    fin.open("players.txt"); //opening file with the file name

    while (fin >> IDFile)
    {
        if (IDFile == IDIn)
        {
            // Read and display the entire record associated with the matched name
            getline(fin, record); // Read the rest of the line 
            cout << "Match found:\n";
            cout << "ID" << "\t" << setw(13) << "NAME" << "\t" << setw(10) << "TEAM" << "\t" << setw(11) << "ROLE" << endl; // displaying every variable and its entities 
            cout << IDFile << "\t" << setw(10) << record << endl;

            fin.close(); // Close the file
            return;
        }
    }
    cout << "Match not found" << endl; // Display this when match is not found
    fin.close(); // Close the file
}

void updateplayer()
{
    string IDfind; //declraing variables
    cout << "Enter the ID of the player to update: "; //asking user to enter the id he wants to update
    cin >> IDfind; //storing value in IDfind

    ifstream fin;
    fin.open("players.txt"); // to use file for taking input
    ofstream temp;
    temp.open("temp.txt");  // Open the temporary file 

    string IDFile, record; //declraing variables

    bool matchFound = false; // Initialized to false, as no match has been found yet.

    while (fin >> IDFile) {
        if (IDFile == IDfind) {
            // Read and display the entire record associated with the matched ID
            getline(fin, record); // Read the rest of the line
            cout << "Match found:\n" << IDFile << record << endl;

            // Get updated information from the user
            int id; //declraing variable
            string name, team, role; //declraing variables

            cout << "enter player id = "; //asking user to enter player id 
            cin >> id; //storing value in id
            cout << "enter player name = "; //asking user to enter player id 
            cin >> name;  //storing value in name
            cout << "enter player team = "; //asking user to enter player id 
            cin >> team; //storing value in team   
            cout << "enter player role = "; //asking user to enter player id 
            cin >> role; //storing value in role
            // Write the updated information to the temp file with proper formatting
            temp << id << setw(15) << name << setw(15) << team << setw(15) << role << endl; //storing values of all variables in file using fout
            matchFound = true;  //if the idfile matches idfind bool will turn true
        }
        else {
            getline(fin, record); // Read the rest of the line
            temp << IDFile << record << endl; // Write non-matching records to the temporary file
        }
    }

    fin.close();   // Close the original file
    temp.close();  // Close the temp file

    if (!matchFound) //it will run when IDFile != IDfind
    {
        cout << "Match not found.\n"; //if id in file does not match the idfind it will display this
    }
    else {
        remove("players.txt");      // Remove the original file
        rename("temp.txt", "players.txt"); // Rename the temp file to the original file

    }
}

void deleteplayer()
{
    string IDfind; //declaring variables
    cout << "Enter the ID of the player to delete: "; //asking user to enter the id he wants to delete 
    cin >> IDfind; //storing value in variable

    ifstream fin;
    fin.open("players.txt"); //opeing file for taking input
    ofstream temp;
    temp.open("temp.txt", ios::app); // Open the temporary file in append mode

    bool matchFound = false; // Initialized to false, as no match has been found yet.

    string idfile, name, team, role; //declaring variables

    while (fin >> idfile >> name >> team >> role) {
        if (idfile == IDfind) {
            // Read and display the entire record associated with the matched ID
            cout << "Match found:\n" << idfile << setw(15) << name << setw(15) << team << setw(15) << role << endl;
            matchFound = true; //if the idfile matches idfind bool will turn true
        }
        else {
            temp << idfile << setw(15) << name << setw(15) << team << setw(15) << role << endl; // Write non-matching records to the temporary file
        }
    }

    fin.close();   // Close the original file
    temp.close();  // Close the temp file

    if (!matchFound) {
        cout << "Match not found.\n"; //if id in file does not match the idfind it will display this
    }
    else {
        remove("players.txt");      // Remove the original file
        rename("temp.txt", "players.txt"); // Rename the temp file to the original file
    }
}
void addfunction(int playerData[][arraySize])
{
    int* idPtr = &playerData[rows][0];
    int* matchesPtr = &playerData[rows][1];
    int* totalRunsPtr = &playerData[rows][2];
    int* totalSixesPtr = &playerData[rows][3];
    cout << "Enter player id: "; //asking user to enter player id 
    cin >> *idPtr;
    cout << "Enter player matches: "; //asking user to enter player matches
    cin >> *matchesPtr;
    cout << "Enter player total runs: "; //asking user to enter player runs
    cin >> *totalRunsPtr;
    cout << "Enter player total sixes: "; //asking user to enter player sixes
    cin >> *totalSixesPtr;
    rows++;
}
void viewfunction(const int playerData[][arraySize]) {


    cout << "ID" << "\t" << setw(10) << "Matches" << "\t" << setw(10) << "Runs" << "\t" << setw(10) << "Sixes" << endl;
    for (int i = 0; i < numPlayers; i++) {
        cout << playerData[rows][0] << "\t" << setw(10) << playerData[rows][1] << "\t" << setw(10) << playerData[rows][2] << "\t" << setw(10) << playerData[rows][3] << endl;
        // displaying every variable and its entities
        rows++; // incrementing row
    }
}

void findPlayer(const int playerData[][arraySize]) {
    int idToFind;
    cout << "Enter ID of player to find: "; //asking user to enter player id he wants to search
    cin >> idToFind;
    for (int i = 0; i < numPlayers; ++i) {
        if (playerData[i][0] == idToFind)
        {
            cout << "Match found:\n";
            // Using pointers to access the information
            const int* idPtr = &playerData[i][0];
            const int* matchesPtr = &playerData[i][1];
            const int* runsPtr = &playerData[i][2];
            const int* sixesPtr = &playerData[i][3];
            cout << "ID" << "\t" << setw(13) << "Matches" << "\t" << setw(10) << "Runs" << "\t" << setw(11) << "Sixes" << endl;
            cout << *idPtr << "\t" << setw(10) << *matchesPtr << "\t" << setw(10) << *runsPtr << "\t" << setw(10) << *sixesPtr << endl;
            return;
        }
    }
    cout << "Match not found" << endl; // When id not get matched we will display this

}

void updatePlayer(int playerData[][arraySize]) {
    int idToFind;
    cout << "Enter the ID of the player to update: "; //asking user to enter player id he wants to update
    cin >> idToFind;
    bool matchFound = false;
    for (int i = 0; i < numPlayers; ++i) {
        if (playerData[i][0] == idToFind) {
            cout << "Match found:\n";
            for (int j = 0; j < arraySize; ++j) {
                cout << playerData[i][j] << "\t";
            }
            cout << endl;
            // Using pointers to update the information
            int* idPtr = &playerData[i][0];
            int* matchesPtr = &playerData[i][1];
            int* runsPtr = &playerData[i][2];
            int* sixesPtr = &playerData[i][3];
            // asking user to reenter the data for updated player cout << "Enter new information:\n";
            cout << "Enter player id: ";
            cin >> *idPtr;
            cout << "Enter player Matches: ";
            cin >> *matchesPtr;
            cout << "Enter player Runs: ";
            cin >> *runsPtr;
            cout << "Enter player Sixes: ";
            cin >> *sixesPtr;
            matchFound = true;
        }
    }
    if (!matchFound) {
        cout << "Matchnot found.\n"; // when id dont get matched we will display this
    }
}
void firstmenu() //writing this function to ask user to perform which activity 
{

    cout << "1.to add player \n2.to view player\n 3.to find player\n 4.to update player\n 5.to delete player\n 6.back\n"; // asking user to press the following number to perform a certain task as given
    int option; // decalring variable
    cin >> option; // storing value in variable 
    switch (option) //using switch statement to use menu
    {
    case 1:
        cout << "CALLING ADD FUNCTION" << endl; // if user press 1 we will call the add function 
        addfunction(); // if user press 1 we will call the add function 
        break; // so other cases dont run 
    case 2:
        cout << "CALLING view FUNCTION" << endl; // if user press 2 we will call the view function
        viewfuntion(); // if user press 2 we will call the add function
        break; // so other cases dont run
    case 3:
        cout << "calling find function" << endl; // if user press 3 we will call the find function
        findplayer(); // if user press 3 we will call the add function
        break; // so other cases dont run
    case 4:
        cout << "calling update function" << endl; // if user press 4 we will call the update function
        updateplayer(); // if user press 4 we will call the add function
        break; // so other cases dont run

    case 5:
        cout << "calling delete function" << endl; // if user press 5 we will call the delete function
        deleteplayer();  // if user press 5 we will call the delete function
        break; // so other cases dont run */
    case 6:

        //exit(0); //to exit program after performing activities 
        break;
    default:
        cout << "invalid option" << endl; //if user select other number than given than we'll display this

    }
}

void secondmenu(int playerData[][arraySize])
//display options for second menu
{
    cout << "Cricket management system" << endl;
    cout << "1. to add player record\n2. to view player record\n3. to find player record\n4. to update player record\n5. back\n";
    int option;
    cin >> option;
    //switc case fro handling user choices
    switch (option) {
    case 1:
        cout << "CALLING ADD FUNCTION" << endl;
        addfunction(playerData);
        break;
    case 2:
        cout << "CALLING VIEW FUNCTION" << endl;
        viewfunction(playerData);
        break;
    case 3:
        cout << "Calling find function" << endl;
        findPlayer(playerData);
        break;
    case 4:
        cout << "Calling update function" << endl;
        updatePlayer(playerData);
        break;
    case 5:
        break;
    default:
        cout << "Invalid option. Try again." << endl;
    }
}
void mainmenu(int playerData[][arraySize]) {
    while (true) {
        cout << "Cricket management system" << endl; // giving my program a label
        cout << "Main Menu" << endl;
        cout << "1. Continue to Menu 1\n2. Continue to Menu 2\n3. Exit\n";
        int mainMenuOption;
        cin >> mainMenuOption;

        switch (mainMenuOption) {
        case 1:
            firstmenu();  // Fixed the function name
            break;
        case 2:
            cout << "CALLING MENU 2" << endl;
            secondmenu(playerData);  // Passed playerData to the function
            break;
        case 3:
            exit(0);
        default:
            cout << "Invalid option. Try again." << endl;
        }
    }
}

int main() {
    int playerData[numPlayers][arraySize]; // 2D array for player data
    for (int i = 0; i < numPlayers; i++)
    {
        for (int j = 0; j < arraySize; j++)
        {
            playerData[i][j] = 0;
        }
    }

    // Infinite loop to repeatedly display the menu
    while (true) {
        mainmenu(playerData);
    }

    return 0;
}