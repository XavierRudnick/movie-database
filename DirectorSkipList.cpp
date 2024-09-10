#include<iostream>
#include <vector>
#include "DirectorSkipList.hpp"
using namespace std;

// Constructor for DirectorSkipList with default capacity and levels
DirectorSkipList::DirectorSkipList() {
    
    capacity = DEFAULT_CAPACITY;
    levels = DEFAULT_LEVELS;
    head = new DirectorSLNode("noName" , DEFAULT_LEVELS); //new node with specific properties
    
}

// Constructor for DirectorSkipList with given capacity and levels
DirectorSkipList::DirectorSkipList(int _cap, int _levels) {
    
    capacity = _cap;
    levels = _levels;
    head = new DirectorSLNode("noName" , _levels);//new node with specific properties
}

// Destructor for DirectorSkipList that deletes all nodes in the skip list (but not the MovieNodes, which are shared with other data structures)

DirectorSkipList::~DirectorSkipList() {
    
    DirectorSLNode* prev;
    DirectorSLNode* curr;
    int help = 0;
    for(int i = 0; i<levels;i++){
        curr = head; //moving through list
        prev = nullptr;
    }
    delete head;  //deleting main node

}

// Inserts a movie node into the skip list with the specified director
void DirectorSkipList::insert(string director, MovieNode* _movie) {
    int n_levels = 1;
    while(n_levels < levels && rand()%2 == 0){ //generating levels
        n_levels++;
    }
    //creating all needed nodes
    DirectorSLNode* curr = new DirectorSLNode(director,n_levels); //ned node to insert
    DirectorSLNode* temp; //temp node to make sure movies added currectly
    DirectorSLNode* HP = head; //head node
    DirectorSLNode* update[levels-1]; //node of levels

    temp = search(director);

    if(temp != nullptr){
        curr->movies = temp->movies;
        curr->addMovie(_movie); // making sure movies work
    }
    else{
        curr->addMovie(_movie);
    }

    int count = 0;
    for(int i = levels; i >=0; i--){
        
        while(HP->next[i] != nullptr && HP->next[i]->director < director){
            HP = HP->next[i]; //finding the end of each skip list where sorted insertion is needed
        }
        update[i] = HP;
    
    }
    HP=HP->next[0]; //next null

        if(n_levels > levels){
            for(int i = levels+1; i <n_levels+1; i++){
                update[i] = head; //array of places to insert
            }
        }
        
        for(int i = 0; i <n_levels; i++){

        curr->next[i] = update[i]->next[i]; //inserting at needed levels
        update[i]->next[i] = curr;

        }
    

}

// Searches for a node in the skip list with the specified director
DirectorSLNode *DirectorSkipList::search(string director) {
    
    DirectorSLNode* curr;
    DirectorSLNode* prev;
    curr = head;
    for(int i = levels-1; i>=0; i--){
        while(curr->next[i] != nullptr && curr->next[i]->director < director){
            prev = curr; //finding the node moving through the list
            curr = curr->next[i];
        }
        //curr= curr->next[i];
    }
    curr = curr->next[0];
    if(curr != nullptr && curr->director == director){ //if node exists return, else nullptr
        return curr;
    }

    return nullptr;
}

// Pretty-prints the skip list
void DirectorSkipList::prettyPrint() {
    DirectorSLNode* curr;
    curr = head;
    int lineLength = 0;

    cout << "{";
    while(curr->next[0] != nullptr){ //printing skip_list
        cout << "director : " << curr->director;
        curr = curr->next[0];

        if(curr->next[0] != nullptr){
            cout << ":";

        }
        if(++lineLength %2==0){
            cout << endl;
        }
    }
    cout << endl;
}