#include<iostream>
#include <vector>
#include <math.h>
#include "MovieHashTable.hpp"
using namespace std;

// Constructor for MovieHashTable with default size
MovieHashTable::MovieHashTable() {
    table_size = DEFAULT_HTABLE_CAPACITY;
    table = new MovieNode*[DEFAULT_HTABLE_CAPACITY]; //creating dynamic movie node
    n_collisions = 0;
    for(int i = 0; i < DEFAULT_HTABLE_CAPACITY; i++){
        table[i] = nullptr;
    }
}

// Constructor for MovieHashTable with given size
MovieHashTable::MovieHashTable(int s) {
    table_size = s;
    table = new MovieNode*[table_size]; //creating dynamic movie node with size
    n_collisions = 0;
    for(int i = 0; i < table_size; i++){
        table[i] = nullptr;
    }
}

// Destructor for MovieHashTable that deletes all nodes in the hash table
MovieHashTable::~MovieHashTable() {
    MovieNode* prev;
    MovieNode* curr;

  for(int i = 0; i<table_size;i++){
    curr = table[i];
    prev = nullptr;
    
    while(curr != nullptr){ //deleting every node iterativly
      prev = curr;
      curr = curr->next;

      delete prev;
    }
  }
  delete []table;
}

// Hash function for MovieHashTable that returns an index in the hash table for a given movie title.
int MovieHashTable::hash(string title) {

    int hash = 0;
    int identikey = 110521257;
    for (int i = 0; i< title.length();  i++){
      hash = hash + title[i]; //classic ascii add up
    }
    hash = identikey * hash; //multiplying hash and new key
    return hash % table_size;
}

// Inserts a movie node into the hash table with the specified title
void MovieHashTable::insert(string title, MovieNode* movie) {
    MovieNode* temp = search(title);
  if(temp != nullptr){ //make sure no duplicates
    cout<< "Key exists" << endl;
    return;
  }
  else{
    MovieNode* newNode = movie; //duplicating movie node
    MovieNode* head = table[hash(title)]; //make sure the node insert one after another
    newNode->next = head;
    table[hash(title)] = newNode; //insert newNode into table hash index
  }
}

// Searches for a node in the hash table with the specified title
MovieNode* MovieHashTable::search(string title) {
    int k = hash(title);

    if(table[k] == nullptr){
      return nullptr; //make sure node exists
    }
    MovieNode* curr = table[k];
    while(curr != nullptr){
      if(curr->title == title){ //moving through table
        return curr;
      }
      setCollisions(); //adding collisions when occuring
      curr = curr->next;
    }
    return nullptr;
}

// Returns the number of collisions that have occurred during insertion into the hash table
int MovieHashTable::getCollisions() {
    
    return n_collisions;
}

// Increments the number of collisions that have occurred during insertion into the hash table
void MovieHashTable::setCollisions() {
    n_collisions++;
    return;
}
