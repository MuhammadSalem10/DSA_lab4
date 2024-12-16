#include <iostream>

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
    Node* getNodeByData(int data) {
        Node* current = root;
        while (current != NULL) {
            if (data == current->data) {
                return current;
            } else if (data > current->data) {
                current = current->Right;
            } else {
                current = current->Left;
            }
        }
        return NULL;
    }

    Node* getParent(Node* node) {
        Node* parent = root;
        while (parent != NULL) {
            if (parent->Left == node || parent->Right == node) {
                return parent;
            } else if (node->data > parent->data) {
                parent = parent->Right;
            } else {
                parent = parent->Left;
            }
        }
        return NULL;
    }

    Node* getMaxRight(Node* node) {
        Node* current = node;
        while (current->Right != NULL) {
            current = current->Right;
        }
        return current;
    }

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
                    current = current->Right;
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

    int getParentByData(int data) {
        Node* node = getNodeByData(data);
        if (node == root) {
            throw runtime_error("ROOT does not have a parent");
        }
        if (node != NULL) {
            Node* res = getParent(node);
            if (res != NULL) {
                return res->data;
            }
        }
        throw runtime_error("Not found");
    }

    void Remove(int data) {
        if (!root) {
            throw runtime_error("Tree is empty");
        }

        Node* nodeToDelete = getNodeByData(data);
        if (!nodeToDelete) {
            throw runtime_error("Not found");
        }

        if (nodeToDelete == root) {
            throw runtime_error("Can't delete the root node!");
        }

        Node* parent = getParent(nodeToDelete);

        if (nodeToDelete->Left == NULL && nodeToDelete->Right == NULL) {
            if (parent->Left == nodeToDelete) {
                parent->Left = NULL;
            } else {
                parent->Right = NULL;
            }
            delete nodeToDelete;
        }

        else if (nodeToDelete->Left == NULL || nodeToDelete->Right == NULL) {
            Node* child = (nodeToDelete->Left != NULL) ? nodeToDelete->Left : nodeToDelete->Right;

            if (parent->Left == nodeToDelete) {
                parent->Left = child;
            } else {
                parent->Right = child;
            }
            delete nodeToDelete;
        }

        else {
            Node* maxNode = getMaxRight(nodeToDelete->Left);
            int maxData = maxNode->data;
            Remove(maxData);
            nodeToDelete->data = maxData;
        }
    }

    void displayAll() {
        display(root);
    }

    ~Tree() {}
};

int main()
{
    Tree tree;

    try {
        tree.add(50);
        tree.add(30);
        tree.add(70);
        tree.add(20);
        tree.add(40);
        tree.add(60);
        tree.add(80);

        cout << "Tree before deletion: ";
        tree.displayAll();
        cout << endl;

        cout << "After Deleting node 30" << endl;
        tree.Remove(30);
        tree.displayAll();
        cout << endl;

        cout << "Deleting root node 50" << endl;
        tree.Remove(50);
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
