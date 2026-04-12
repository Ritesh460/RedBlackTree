#include <iostream>
#include <cstring>
using namespace std;

enum Color { RED, BLACK };

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
  void readFromFile(char filename);
  void print();
};

//main(most of these functions aren't done but putting basic code for what I think will happen)
int main() {
  RBTree tree;
  int choice, value;
  char filename;
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
      tree.print();
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

/*
Steps to do:
1. Understand how red-black trees work
2. Create implementation of tree with parent pointer to the nodes
3. Maintain tree so it hands numbers up to 3 digits, no 0 and tree updates no matter what you do to it
4. Functions need to make are add(enter number to tree), read(read in a series of numbers from a file which should update tree properly after each one), print(print ree with number, red/black value, and parent)
5. Debug and comments
*/
