#include"rbt.h"

rbt::rbt()
{
  root1 = NULL; //constructor sets a node pointer "root1" to NULL
}

rbt::~rbt()
{
  removeAll(); //deconstructor deletes all nodes one by on
}

//Left rotator function
int rbt::rotateL(node* &p)
{
  node* child = p->right;
  
  p->right = child->left; //child's left child becomes p's right child
  if(p->right != NULL) //if parent's right child exists
    {
      p->right->parent = p; //parent's right child becomes p's parent
    }
  if(child != NULL)
    {
      child->parent = p->parent; //child becomes old p's grandparent
    }
  if(p->parent == NULL) //if p has no parent
    {
      root1 = child; //rotate so that child is the new root
    }
  else if(p == p->parent->left) //if p = is the left child of its grandfather
    {
      p->parent->left = child; //let p become new child
    }
  else //if p = the right child of its grandfather
    {
      p->parent->right = child; //let p become new child
    }
  child->left = p; //p becomes new left child of the old child
  p->parent = child; //new p's parent is old child
  return 1;
}

//Right rotator function
int rbt::rotateR(node* &p) //similar to rotateL
{
  node* child = p->left;
  
  p->left = child->right;
  if(p->left != NULL)
    {
      p->left->parent = p;
    }
  if(child != NULL)
    {
      child->parent = p->parent;
    }
  if(p->parent == NULL)
    {
      root1 = child;
    }
  else if(p == p->parent->left)
    {
      p->parent->left = child;
    }
  else
    {
      p->parent->right = child;
    }
  child->right = p;
  p->parent = child;
  return 1;
}

int rbt::insert(int data)
{
  //create a new node here
  node* newNode = new node;
  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->parent = NULL;
  newNode->color = 1; //default color to RED [1]
  insert(root1, newNode); //accesses insert(node*, node*)
  repair(root1, newNode); //fix the newly created tree
}

//Creates a node that passes a data value and a way to link with two other nodes
int rbt::insert(node* &root, node* &temp)
{
  if(root == NULL) //if node doesn't exist
    {
      root = temp; //from insert(int data), make the root = newNode (temp here)
      return 1;
    }
  //similar to a binary search tree
  else if(root->data > temp->data) //if the data in current node is smaller than what we're inserting
    {
      temp->parent = root; //set the parent
      return insert(root->left, temp); //recursively check again until NULL
    }
  else
    {
      temp->parent = root; //set parent
      return insert(root->right, temp); //recursion
    }      
}

//Corrects the coloring and placement of an inserted node to avoid violating RB principles
int rbt::repair(node* &root, node* &temp)
{
  node* p = NULL;
  node* gp = NULL;
  //in the conditions that...
  //1. There is not only one node in the tree
  //2. The color of temp (newNode) is red
  //3. The color of temp's parent is also red
  //   We deem it necessary to go through this loop and fix the tree
  while((temp != root) && (temp->color == 1) && (temp->parent->color == 1))
    {
      p = temp->parent; //parent
      gp = temp->parent->parent; //grandparent
      if(p == gp->left) //parent is left child of its grandparent
	{
	  node* unc = gp->right; //gp->right is uncle
	  if(unc != NULL && unc->color == 1) //if uncle exists & it's red
	    {
	      p->color = 0; //parent is orig. red
	      gp->color = 1; //gp is orig. black if parent was red
	      unc->color = 0; //uncle must be red within the reqs. of the while loop
	      temp = gp; //need to set temp = gp
	    }
	  else //if uncle is NULL & black
	    {
	      if(temp == p->right) //if temp = p's right child
		{
		  rotateL(p); //call rotateL function
		  temp = p;
		  p = temp->parent;
		}
	      rotateR(gp); //call rotateR function

	      //swap colors
	      int tempColor;
	      tempColor = p->color;
	      p->color = gp->color;
	      gp->color = tempColor;
	      temp = p;
	    }
	}
      else //parent is right child of its grandparent
	{
	  node* unc = gp->left; //gp->left is uncle
	  if(unc != NULL && unc->color == 1) //if uncle exists & it's red
	    {
	      p->color = 0; //parent is orig. red
	      gp->color = 1; //gp is orig. black if parent was red
	      unc->color = 0; //uncle must be red within the reqs. of the while loop
	      temp = gp; //need to set temp = gp
	    }
	  else
	    {
	      if(temp == p->left) //if temp = p's left child
		{
		  rotateR(p); //call rotateR
		  temp = p;
		  p = temp->parent;
		}
	      rotateL(gp); //call RotateL

	      //swap colors
	      int tempColor;
	      tempColor = p->color;
	      p->color = gp->color;
	      gp->color = tempColor;
	      temp = p;
	    }
	}
    }
  root->color = 0; //ALWAYS set the root to be black
}

//Display function
int rbt::display()
{
  return display(root1); //accesses display(node*)
}

//Displays data of all nodes, their colors, parents and children
int rbt::display(node* root)
{
  if(root == NULL) //if no root, don't do anything
    {
      return 0;
    }
  else //otherwise...
    {
      display(root->left); //recursively repeat, going to left node until at VERY leftmost node
      cout << root->data << " | ";//display data (if NULL, displays nothing)
      if(root->color == 0) //if node is black
	{
	  cout << "BLK | ";
	}
      else//if it's red
	{
	  cout << "RED | ";
	}
      if(root->parent != NULL) //if parent exists
	{
	  cout << "Parent: " << root->parent->data << " | "; //print the parent's data
	}
      else //if parent doesn't exist
	{
	  cout << "Parent: NULL | "; //print NULL
	}
      if(root->left != NULL) //if node's left child exists
	{
	  cout << "LChild: " << root->left->data << " | "; //print its left child's data
	}
      else //if not, NULL
	{
	  cout << "LChild: NULL | ";
	}
      if(root->right != NULL) //if node's right child exists
	{
	  cout << "RChild: " << root->right->data << endl; //print its right child's data
	}
      else //if not, NULL
	{
	  cout << "RChild: NULL\n";
	}
      display(root->right); //go to the right of node
      return 1;
    }
}

//Clears tree
int rbt::removeAll()
{
  return removeAll(root1); //accesses removeAll(node*)
}

int rbt::removeAll(node* &root)
{
  if(root != NULL) //if tree exists
    {
      removeAll(root->left); //recursion to delete the VERY leftmost node until all are deleted
      removeAll(root->right); //recursion to delete the VERY rightmost node until all are deleted
      delete root; //with the two removeAll() above, only the root remains; we delete it here
      root = NULL;
      return 1;
    }
}

//Finds height of the tree
int rbt::findHeight()
{
  return findHeight(root1); //accesses findHeight(node*)
}

int rbt::findHeight(node* root)
{
  if(root == NULL) //if root = NULL, do nothing
    {
      return 0;
    }
  if(root != NULL)
    {
      int leftHeight = 0; //using this to find the height of the left side of the root
      leftHeight = findHeight(root->left); //keeps moving to a lower level leftward
      
      int rightHeight = 0; //using this to find the height of the right side of the root
      rightHeight = findHeight(root->right); //keeps moving to a lower level rightward

      
      if(leftHeight > rightHeight) //compare which height is higher between left and right, and return the highest; if the same, it chooses rightHeight+1, even though they are the same value (so it don't matter)
	{
	  return leftHeight + 1;
	}
      else
	{
	  return rightHeight + 1;
	}
    }
}

//Displays visual tree with data, color, and level
int rbt::level()
{
  int height = findHeight(); //using findHeight(), sets height = the height of the tree
  cout << "\nLevel#:";
  for(int i = 0; i < height; i++) //for values i = 0 to whatever the height is, print the levels and the values that reside in them
    {
      cout << endl << "     " << (i+1) << ": ";
      level(root1, i); //access level(node*, int)
    }
  cout << endl;
  return 1;
}

int rbt::level(node* root, int order)
{
  if(root == NULL) //if root = NULL, do nothing
    {
      return 0;
    }
  if(root != NULL) //if root exists...
    {
      if(order == 0) //the root, printing "1: <root value>" in main
	{
	  cout << root->data; //print root
	  if(root->color == 1) //print color
	    {
	      cout << "R" << " ";
	    }
	  else
	    {
	      cout << "B" << " ";
	    }
	}
      else //if descendants of root, printing 2,3,4...: <values> in main
	{
	  level(root->left, order-1);
	  level(root->right, order-1);
	}
    }
}

//Takes information of a node's color
int rbt::getColor(node* &root)
{
  if(root == NULL) //if NULL, it is black
    {
      return 0; //0 - Black
    }
  return root->color; //if node exists, get color ( 1 - Red / 0 - Black)
}

//Alters a node's color (c is color, 0 - Black, 1 - Red, 2 - Double Black)
int rbt::setColor(node* &root, int c)
{
  if(root == NULL) //if NULL, do nothing
    {
      return 0;
    }
  //if not NULL
  root->color = c; //change node's color to "c"
  return root->color;
}

//Searches for successor of a deleted node
node* rbt::inorderTraverse(node* &root)
{
  node* temp = root;
  while(temp->left != NULL) //traverses while temp->left exists
    {
      temp = temp->left;
    }
  return temp; //return the "temp" node
}

//Finds the node to remove
node* rbt::findRemove(node* &root, int data)
{
  if(root == NULL) //if node doesn't exist
    {
      return root; //return NULL (root)
    }
  if(data < root->data) //if (searching) data is smaller than the data of the node
    {
      return findRemove(root->left, data);
    }
  if(data > root->data) //if (searching) data is larger than node data
    {
      return findRemove(root->right, data);
    }
  if(root->left == NULL || root->right == NULL) //if a child is NULL
    {
      return root;
    }
  node* temp = inorderTraverse(root->right); //temp = successor node
  root->data = temp->data; //match data between root and temp
  return findRemove(root->right, temp->data);
}

//Corrects the RB Tree after deletion
int rbt::recover(node* &root)
{
  if(root == NULL) //if no tree
    {
      return 0;
    }
  if(root == root1) //if only 1 element in the tree
    {
      root1 = NULL; //make NULL
      return 1;
    }
  
  if(getColor(root) == 1 || getColor(root->left) == 1 || getColor(root->right) == 1) //if node is red/left child is red/right child is red
    {
      node* child = NULL;

      if(root->left != NULL) //if left child exists
	{
	  child = root->left; //make child point to left child
	}
      else //if right child exists (left doesn't)
	{
	  child = root->right; //make child point to right child
	}
      if(root == root->parent->left) //if "root" is parent's left child
	{
	  root->parent->left = child; //link the parent's left child to "root's" child (root should be unconnected from tree)
	  if(child != nullptr) //if child exists
	    {
	      child->parent = root->parent; //link child and root's parent
	    }
	  setColor(child, 0); //make the child black
	  delete root;
	} 
      else //root is parent's right child
	{
	  root->parent->right = child; //parent's right child becomes root's child
	  if(child != nullptr) //if child exists
	    {
	      child->parent = root->parent; //link child to root's parent
	    }
	  setColor(child, 0); //set child to black
	  delete root;
	}
    }
  else //double black cases
    {
      node* sib = nullptr; //sibling
      node* p = nullptr; //parent
      node* temp = root; //temp ptr for root
      
      setColor(temp, 2); //sets temp color to 2 - Double Black
      while(temp != root1 && getColor(temp) == 2) //while temp isn't head of tree and temp is dbl black
	{
	  p = temp->parent; //parent assigned parent of temp
	  if(temp == p->left) //if temp is left child of parent
	    {
	      sib = p->right; //sibling is then the right
	      if(getColor(sib) == 1) //if sibling is red
		{
		  setColor(sib, 0); //set sibling to black
		  setColor(p, 1); //set parent to red
		  rotateL(p); //left rotate
		}
	      else //if sibling is black, sib's children are black
		{
		  if(getColor(sib->left) == 0 && getColor(sib->right) == 0)
		    {
		      setColor(sib, 1); //set sibling to red
		      if(getColor(p) == 1) //if parent is red
			{
			  setColor(p, 0); //set parent to black (recover from dbl black)
			}
		      else
			{
			  setColor(p, 2); //set parent to dbl black (transfer dbl black)
			}
		      temp = p; //temp = parent
		    }
		  else //no double black siblings
		    {
		      if(getColor(sib->right) == 0) //if sibling's right child is black
			{
			  setColor(sib->left, 0); //set sibling's left child to black
			  setColor(sib, 1); //set sibling to red
			  rotateR(sib); //rotate right
			  sib = p->right; //sibling is now parent's right child
			}
		      setColor(sib, p->color); //set sibling's color = parent's color
		      setColor(p, 0); //set parent to black
		      setColor(sib->right, 0); //set sibling's right child to black
		      rotateL(p); //rotate left
		      break; //break out of the loop
		    }
		}			  
	    }
	  else //if temp is right child of parent
	    {
	      sib = p->left; //then sibling is parent's left child
	      if(getColor(sib) == 1) //if sibling is red
		{
		  setColor(sib, 0); //set sibling to black
		  setColor(p, 1); //set parent to red
		  rotateR(p); //rotate right
		}
	      else //if sibling is black
		{
		  if(getColor(sib->left) == 0 && getColor(sib->right) == 0) //and children are black
		    {
		      setColor(sib, 1); //set sibling to red
		      if(getColor(p) == 1) //if parent is red
			{
			  setColor(p, 0); //set parent to black (recover from dbl black)
			}
		      else //if black
			{
			  setColor(p, 2); //set parent to dbl black (transfer dbl black)
			}
		      temp = p; //temp = parent
		    }
		  else //if children are not black
		    {
		      if(getColor(sib->left) == 0) //if sibling's left child is black
			{
			  setColor(sib->right, 0); //set sibling's right child is black
			  setColor(sib, 1); //set sibling to red
			  rotateL(sib); //rotate left
			  sib = p->left; //sibling is parent's left child
			}
		      setColor(sib, p->color); //sibling's color = parent's color now
		      setColor(p, 0); //set parent to black
		      setColor(sib->left, 0); //set sibling's left child to black
		      rotateR(p); //rotate right
		      break; //terminate, break out of the loop
		    }
		}
	    }
	} //while loop ends
      if(root == root->parent->left) //if the root is the left child of its parent 
	{
	  root->parent->left = NULL; //set NULL
	}
      else //if right child
	{
	  root->parent->right = NULL; //set NULL
	}
      delete root;
      setColor(root1, 0); //set the head of tree to black
      return 1;
    }
}

//removal function
int rbt::remove(int data)
{
  node* temp = findRemove(root1, data); //find matching node (data = root->data)
  recover(temp); //delete it, and correct to maintain RB Tree
  return 1;
}

