


#include <iostream>
#include <stdexcept>
using namespace std;

struct Node {
    int data;
    Node* Left;
    Node* Right;

    Node(int _data): data(_data), Left(NULL), Right(NULL) {}
};

class Tree {
    Node* root;

private:
    void display(Node* node) {
        if (node == NULL) {
            return;
        }
        display(node->Left);
        cout << node->data << "  ";
        display(node->Right);
    }

public:
    Tree() {
        root = NULL;
    }

    void add(int data) {
        Node* newNode = new Node(data);
        Node* parent = NULL;
        if (root == NULL) {
            root = newNode;
        } else {
            Node* current = root;

            while (current != NULL) {
                parent = current;
                if (data > current->data) {
                    current = current->Right; // NULL
                } else {
                    current = current->Left;
                }
            }
            if (data > parent->data) {
                parent->Right = newNode;
            } else {
                parent->Left = newNode;
            }
        }
    }





    int findMin() {
        if (root == NULL) {
            throw runtime_error("Tree is empty");
        }
        Node* current = root;
        while (current->Left != NULL) {
            current = current->Left;
        }
        return current->data;
    }

    int findMax() {
        if (root == NULL) {
            throw runtime_error("Tree is empty");
        }
        Node* current = root;
        while (current->Right != NULL) {
            current = current->Right;
        }
        return current->data;
    }

    void displayAll() {
        display(root);
    }

    ~Tree() {}
};



int main() {
    Tree tree;

    try {
        tree.add(45);
        tree.add(16);
        tree.add(18);
        tree.add(22);
        tree.add(33);
        tree.add(40);
        tree.add(55);

        cout << "Tree elements: ";
        tree.displayAll();
        cout << endl;

        cout << "Min value: " << tree.findMin() << endl;
        cout << "Max value: " << tree.findMax() << endl;

    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
