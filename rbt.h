#ifndef RBT_H
#define RBT_H
#include<iostream>
#include<assert.h>
using namespace std;

struct node
{
  int data; //contained number
  int color; //0 = Black, 1 = Red
  node* left;
  node* right;
  node* parent;
};

class rbt
{
 public:
  rbt(); //constructor
  ~rbt(); //destructor
  int insert(int data); //add int to tree & reconstruct
  int remove(int data); //remove a node from the tree
  int display(); //display tree
  int removeAll(); //for deconstructor, delete all nodes
  int findHeight(); //calculate height of bst
  int level(); //use in conjunction with findHeight to display the levels within the tree (visual rep)
 private:
  int height;
  node* root1;
  //general functions
  int rotateL(node* &p); //rotates segment of tree left
  int rotateR(node* &p); //rotates segment of tree right
  int display(node* root); //displays data of tree
  int findHeight(node* root); //finds height of tree, used with level function
  int level(node* root, int order); //displays visual representation of trees and their levels, data, and colors
  int getColor(node *&root); //gets a node's color
  int setColor(node* &root, int color); //changes a node's color
  
  //insertion functions
  int insert(node* &root, node* &temp); //inserts a node similar to BST
  int repair(node* &root, node* &temp); //repair on insertion, corrects coloring and placement
  
  //deletion functions
  int recover(node* &root); //repair on deletion, corrects coloring and placement
  int removeAll(node* &root); //clear entire tree (for deconstructor)
  node* inorderTraverse(node* &root); //traverses to find the successor of the chosen node, used in findRemove function
  node* findRemove(node* &root, int data);  //finds a node for deletion
};

#endif
