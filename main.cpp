#include <iostream>
#include <cstring>
using namespace std;

enum Color { //wanted to use enum because set values and organized
  RED, 
  BLACK 
};

//node struct
struct Node {
  int data;
  Color color;
  Node* left;
  Node* right;
  Node* parent;
  Node(int val);
};

//tree class + prototypes
class RBTree {
private:
  Node* root;
  void rotateLeft(Node* x);
  void rotateRight(Node* x);
  void fixInsert(Node* node);
  void printHelper(Node* node, int space);
public:
  RBTree();
  void add(int val);
  void readFromFile(char filename[]);
  void print();
};

//main functions will all commmands(add,print,read,quit)
int main() {
  RBTree tree;
  int choice;
  int value;
  char filename[300];
  bool running = true;
  while (running) {
    cout << "--- MENU ---";
    cout << "1. Add number" << endl;
    cout << "2. Read from file" << endl;
    cout << "3. Print tree" << endl;
    cout << "4. Exit " << endl;
    cout << "Choice: " << endl;
    cin >> choice;
    if (choice == 1) {
      cout << "Enter number (1–999): ";
      cin >> value;
      tree.add(value);
    }
    else if (choice == 2) {
      cout << "Enter filename: ";
      cin >> filename;
      tree.readFromFile(filename);
    }
    else if (choice == 3) {
      //tree.print();
    }
    else if (choice == 4) {
      running = false;
    }
    else {
      cout << "Invalid choice.";
    }
  }
  return 0;
}

//node implement
Node::Node(int val) {
  data = val;
  color = RED;
  left = right = parent = NULL;
}

RBTree::RBTree() {
  root = NULL;
}
//node moves left
void RBTree::rotateLeft(Node* x) {
  Node* y = x->right;
  x->right = y->left;

  if (y->left != NULL)
    y->left->parent = x;
  y->parent = x->parent;

  if (x->parent == NULL)
    root = y;

  else if (x == x->parent->left)
    x->parent->left = y;

  else
    x->parent->right = y;

  y->left = x;
  x->parent = y;
}
//node moves right
void RBTree::rotateRight(Node* x) {
  Node* y = x->left;
  x->left = y->right;

  if (y->right != NULL)
    y->right->parent = x;
  y->parent = x->parent;

  if (x->parent == NULL)
    root = y;

  else if (x == x->parent->right)
    x->parent->right = y;

  else
    x->parent->left = y;

  y->right = x;
  x->parent = y;
}
//inserting node
void RBTree::fixInsert(Node* node) {
  while (node != root && node->parent->color == RED) {
    Node* parent = node->parent;
    Node* grandparent = parent->parent;

    if (parent == grandparent->left) {
      Node* uncle = grandparent->right;
      if (uncle != NULL && uncle->color == RED) {
        parent->color = BLACK;
        uncle->color = BLACK;
        grandparent->color = RED;
        node = grandparent;
      }
      else {
        if (node == parent->right) {
          node = parent;
          rotateLeft(node);
        }
        parent->color = BLACK;
        grandparent->color = RED;
        rotateRight(grandparent);
      }
    }

    else {
      Node* uncle = grandparent->left;
      if (uncle != NULL && uncle->color == RED) {
        parent->color = BLACK;
        uncle->color = BLACK;
        grandparent->color = RED;
        node = grandparent;
      }
      else {
        if (node == parent->left) {
          node = parent;
          rotateRight(node);
        }
        parent->color = BLACK;
        grandparent->color = RED;
        rotateLeft(grandparent);
      }
    }

  }
  root->color = BLACK;
}

void RBTree::add(int val) {
  if (val < 1 || val > 999) {
    cout << "Invalid number.";
    return;
  }

  Node* newNode = new Node(val);
  Node* parent = NULL;
  Node* current = root;

  while (current != NULL) {
    parent = current;
    if (val < current->data) {
      current = current->left;
    }
    else {
      current = current->right;
    }
  }

  newNode->parent = parent;
  if (parent == NULL) {
    root = newNode;
  }
  else if (val < parent->data) {
    parent->left = newNode;
  }
  else {
    parent->right = newNode;
  }
  fixInsert(newNode);
}

void RBTree::readFromFile(char filename[]) {
  ifstream file(filename);
  if (!file) {
    cout << "Error opening file.";
    return;
  }
  int num;
  while (file >> num) {
    add(num);
  }
  file.close();
}
//have printhelper function
void RBTree::print() {
  //recurision or iteration?
}

//print functions is left
//void RBTree::print()
/*
Steps to do:
1. Understand how red-black trees work (done?this is hard :()
2. Create implementation of tree with parent pointer to the nodes(mostly done)
3. Maintain tree so it hands numbers up to 3 digits, no 0 and tree updates no matter what you do to it(done)
4. Functions need to make are add(enter number to tree), read(read in a series of numbers from a file which should update tree properly after each one), print(print ree with number, red/black value, and parent) (2/3 done)
5. Debug and comments(not done)
*/
