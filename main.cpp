//Red Black Tree Tree, By Stone Yang, 3/26
//Creates a sorted & colored binary tree that allows the user to add, remove, and display
//while maintaining a balanced structure
#include<iostream>
#include<string.h>
#include<fstream>
#include"rbt.h"
using namespace std;

bool getFileData(int* numbers, bool* valid, rbt* tree);

int main()
{
  rbt tree; //creating tree (constructor sets root = NULL)
  char readChoice[10]; //choice
  bool valid = true; //to allow the user to retry after failure
  bool repeat = true; //to allow phase 2 to repeat
  int numbers[200];
  
  //Phase 1:
  //Purpose: prompt user to choose a file, extract data & create the first tree
  do
    {
      cout << "Red-Black Tree\n";
      cout << "Choose a file of ints to insert.\n";
      getFileData(numbers, &valid, &tree);
    }while(valid == false);

  //Phase 2:
  //Purpose: display the tree created in Phase 1
  cout << "Tree successfully generated!\n Your Red-Black Tree:\n";
  tree.display();
  tree.level();

  //Phase 3:
  //Purpose: prompt user to make additional edits (removing nodes, inserting nodes, re-displaying the tree)
  while(repeat == true)
    {
      int number = 0;
      cout << "INSERT a node, DELETE a node, DISPLAY the tree, or QUIT.\n";
      cin.getline(readChoice, 10);
      
      //ignore case-sensitivity of readChoice
      for(int i = 0; i < strlen(readChoice); i++)
	{
	  readChoice[i] = toupper(readChoice[i]);
	}
      
      if(strcmp(readChoice, "INSERT") == 0)
	{
	  cout << "Add a number into the tree: ";
	  cin >> number;
	  cin.ignore();
	  tree.insert(number); //inserts into the tree
	}      
      else if(strcmp(readChoice, "DISPLAY") == 0)
	{
	  cout << endl;
	  tree.display(); //displays numbers inorder
	  tree.level(); //displays visual tree levels
	}
      else if(strcmp(readChoice, "DELETE") == 0)
	{
	  cout << "Enter a number to delete: ";
	  cin >> number;
	  cin.ignore();
	  tree.remove(number);
	}
      else if(strcmp(readChoice, "QUIT") == 0)
	{
	  repeat = false; //stop loop, end program
	}
      else
	{
	  cout << "Invalid command, try again.\n"; //when you misspell one of those 4 words
	}
    }
  return 0;
}

//function to get values from a file
bool getFileData(int* numbers, bool* valid, rbt* tree)
{
  char fileName[50];
  int value;
  ifstream file;
  
  //prompt user to insert the name of the file to be used
  cout << "Enter the name of file to use (be sure values are separated by ','): ";
  cin.getline(fileName, 50);
  file.open(fileName);
  
  //if file is not open (does not exist)
  if(!file.is_open())
    {
      cout << "Cannot find file.\n";
      *valid = false;
      return valid; //return "false" to valid, and loop in the main until "true"
    }
  else
    {
      if(file)
	{
	  file >> value;
	  file.ignore();
	}
      while(!file.eof() && file) //while the file has not "hit" the end line
	{
	  tree->insert(value); //read ints from the file and insert into the tree
	  file >> value; 
	  file.ignore();
	}
      file.close();
      *valid = true;
      return valid; //return "true" to valid, continue to phase 2
    }
}
