#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "MovieHashTable.hpp"
#include "DirectorSkipList.hpp"

using namespace std;

// Function prototypes
MovieNode* parseMovieLine(string line);
void readMovieCSV(string filename,  MovieHashTable &movieTable, DirectorSkipList &directorList);
void display_menu();


// Main function
int main(int argc, char* argv[]) { 
    if(argc != 4){
        cout << "Invalid num of inputs" << endl; //First check if the right amount of arguments are input
        cout << "Usage: ./<program name> <csv file> <hashtable size> <skiplist size>" << endl;
        return 0;
    }
    
    int choice = 0;
    int movieCount = 0;
    string movie;
    string movie2;
    string director;
    MovieHashTable hash = MovieHashTable(atoi(argv[2])); //creating all needed variables
    DirectorSkipList skipList = DirectorSkipList(atoi(argv[3]),10);
    readMovieCSV(argv[1],hash,skipList); // filling the hash and skiplist structures with inputed data

    do{
    display_menu();
    cin >> choice;
    switch(choice){
        case 1:
            cout << "Enter movie name : " << endl;
            cin.ignore();
            getline(cin,movie); // Ignore and getline to makre sure no errors occur
            cout << endl;
            if(hash.search(movie) != nullptr){ //if case to if node exists or not
                cout << "The director is " << hash.search(movie)->director << endl;
            }
            else{
                cout << "no movie in database" << endl;
            }
            cout << endl;
            break;
        case 2:
            cout << "Enter director name : " << endl;
            cin.ignore();
            getline(cin,director); // Ignore and getline to makre sure no errors occur
            cout << endl;
            if(skipList.search(director) != nullptr){ //if case to if node exists or not
                cout << director << " has directed " << skipList.search(director)->movies.size() << " movies"<< endl;
            }
            else{
                cout << director << " does not exist" << endl;
            }
            cout << endl;
            
            break;
        case 3:
            cout << "Enter movie name : " << endl;
            cin.ignore();
            getline(cin,movie); // Ignore and getline to makre sure no errors occur
            cout << endl;
            if(hash.search(movie) != nullptr){ //if case to if node exists or not
                cout << "The director is " << hash.search(movie)->description << endl;
            }
            else{
                cout << "no movie in database" << endl;
            }
            cout << endl;
            break;
        case 4:
            cout << "Enter director name : "  << endl;
            cin.ignore();
            getline(cin,director); // Ignore and getline to makre sure no errors occur
            cout << endl;
            if(skipList.search(director) != nullptr){ //if case to if node exists or not
                cout << director << " has the following movies " << endl;
                for(int i = 0; i < skipList.search(director)->movies.size(); i++){ //for loop to print all movies
                cout << i << ": ";
                cout << skipList.search(director)->movies[i]->title << endl;
                }
                cout << endl;
            }
            else{
                cout << director << " does not exist" << endl;
            }
            cout << endl;
            break;
        case 5:
            cout << "Thanks for using" << endl; // exit
            return 0;
            
        }   
    } while(choice >0 && choice<6);
   
}


// Function to parse a CSV line into a MovieNode object
MovieNode* parseMovieLine(string line) {
    stringstream ss(line);
    vector<string> fields;
    string field;

    // Loop through the characters in the line
    bool in_quotes = false;
    for (size_t i = 0; i < line.length(); ++i) {
        char c = line[i];
        if (c == '\"') {
            in_quotes = !in_quotes;
        } else if (c == ',' && !in_quotes) {
            // add field to vector and reset for next field
            fields.push_back(field);
            field.clear();
        } else {
            field += c;
            // handle double quotes inside a quoted field
            if (in_quotes && c == '\"' && i < line.length() - 1 && line[i+1] == '\"') {
                field += '\"'; // add the second double quote and skip it
                ++i;
            }
        }
    }
    fields.push_back(field);

    if (fields.size() != 12) {
        cerr << "Error: Invalid movie line format" << line << endl;
        return nullptr;
    }

    int rank = stoi(fields[0]);
    string title = fields[1];
    string genre = fields[2];
    string description = fields[3];
    string director = fields[4];
    string actors = fields[5];
    int year = stoi(fields[6]);
    int runtime = stoi(fields[7]);
    float rating = stof(fields[8]);
    int votes = stoi(fields[9]);
    float revenue = stof(fields[10]);
    int metascore = stoi(fields[11]);

    // Create a new MovieNode object with the parsed fields
    MovieNode* movie = new MovieNode(rank, title, genre, description, director, actors, year, runtime, rating, votes, revenue, metascore);
    return movie;
}

// Function to read a CSV file into a vector of MovieNode objects
void readMovieCSV(string filename,  MovieHashTable &movieTable, DirectorSkipList &directorList) {
    string line;
    int count = 0;
    
    ifstream in_file;
    in_file.open(filename);
    
    if(!in_file.is_open()) { //make sure file is opened
        cout << "file failed to open" << endl;
        return;
    }
    
    MovieNode* curr;
    while(getline(in_file, line)) {
        
        if(count > 0){
        curr = parseMovieLine(line);
        movieTable.insert(curr->title,curr); //insert the data
        directorList.insert(curr->director,curr);
        
        }
        else{
            count++;
        }
        
    }
    cout << "Number of collisions : " << movieTable.getCollisions() << endl; //printing collisions
    
    
    return;
}

// Function to display the menu options
void display_menu() {
    cout << "Please select an option" << endl; //menue display
    cout << "1. Find the director of movie" << endl;
    cout << "2. Find number of movies by director" << endl;
    cout << "3. Find description of movie" << endl;
    cout << "4. list movies by director" << endl;
    cout << "5. Quit" << endl;
    cout << endl;
    cout << "Enter an Option:" << endl;
    
}
