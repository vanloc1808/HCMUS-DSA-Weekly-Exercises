#include <iostream>
#include <stack>
#include <queue>

using namespace std;

//This file implements the AVL Tree (aka balanced binary search tree)

struct Node {
    int key;
    Node *left;
    Node *right;
    int height;
};

Node* createNode(int data) {
    Node* node = new Node;
    node->key = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 0;
    return node;
}

int getHeight(Node* node) {
    if (node == NULL) {
        return -1;
    }
    return node->height;
}

void makeEmpty(Node*& node) {
    if (node == NULL) {
        return;
    }
    makeEmpty(node->left);
    makeEmpty(node->right);
    delete node;
    node = NULL;
}

void singleLeftRotate(Node* &pRoot) {
    Node* p = pRoot->right;
    pRoot->right = p->left;

    p->left = pRoot;

    pRoot->height = max(getHeight(pRoot->left), getHeight(pRoot->right)) + 1;

    p->height = max(getHeight(pRoot->right), getHeight(pRoot)) + 1;
}

void singleRightRotate(Node* &pRoot) {
    Node* p = pRoot->left;
    pRoot->left = p->right;

    p->right = pRoot;

    pRoot->height = max(getHeight(pRoot->left), getHeight(pRoot->right)) + 1;

    p->height = max(getHeight(pRoot->left), getHeight(pRoot)) + 1;
}

void doubleLeftRotate(Node*& pRoot) {
    singleRightRotate(pRoot->right);
    singleLeftRotate(pRoot);
}

void doubleRightRotate(Node* &pRoot) {
    singleLeftRotate(pRoot->left);
    singleRightRotate(pRoot);
}

void insert(Node* &pRoot, int data) {
    if (pRoot == NULL) {
        pRoot = createNode(data);
        return;
    }

    if (pRoot->key == data) {
        cout << "This value already exists in the tree\n";
        return;
    }

    if (data < pRoot->key) {
        insert(pRoot->left, data);

        if (getHeight(pRoot->left) - getHeight(pRoot->right) == 2) {
            if (data < pRoot->left->key) {
                singleRightRotate(pRoot);
            } else {
                doubleRightRotate(pRoot);
            }
        }
    } else {
        insert(pRoot->right, data);

        if (getHeight(pRoot->right) - getHeight(pRoot->left) == 2) {
            if (data > pRoot->right->key) {
                singleLeftRotate(pRoot);
            } else {
                doubleLeftRotate(pRoot);
            }
        }
    }

    pRoot->height = max(getHeight(pRoot->left), getHeight(pRoot->right)) + 1;
}

Node* findMin(Node* pRoot) {
    if (pRoot == NULL) {
        return NULL;
    }

    if (pRoot->left == NULL) {
        return pRoot;
    } 

    return findMin(pRoot->left);
}

Node* findMax(Node* pRoot) {
    if (pRoot == NULL) {
        return NULL;
    }

    if (pRoot->right == NULL) {
        return pRoot;
    }

    return findMax(pRoot->right);
}

//https://gist.github.com/Harish-R/097688ac7f48bcbadfa5
void remove(Node* pRoot, int data) {
    if (pRoot == NULL) {
        cout << "This value does not exist in the tree\n";
        return;
    }

    Node* temp;

    if (data < pRoot->key) {
        remove(pRoot->left, data);
    } else if (data > pRoot->key) {
        remove(pRoot->right, data);
    } else if (pRoot->left != NULL && pRoot->right != NULL) {
        //element found, has two children
        temp = findMin(pRoot->right);

        pRoot->key = temp->key;

        remove(pRoot->right, temp->key);
    } else {
        //element found, with <= 1 child
        temp = pRoot;

        if (pRoot->left == NULL) {
            pRoot = pRoot->right;
        } else if (pRoot->right == NULL) {
            pRoot = pRoot->left;
        }

        delete temp;
    }

    if (pRoot == NULL) {
        return;
    }

    pRoot->height = max(getHeight(pRoot->left), getHeight(pRoot->right)) + 1;

    //if the tree is unbalanced, 
    //if left node is deleted, right case
    if (getHeight(pRoot->left) - getHeight(pRoot->right) == 2) {
        //right right case
        if (getHeight(pRoot->left->left) - getHeight(pRoot->left->right) == 1) {
            singleLeftRotate(pRoot);
        } else {
            //right left case
            doubleLeftRotate(pRoot);
        }
    } else if (getHeight(pRoot->right) - getHeight(pRoot->left) == 2) {
        //left left case
        if (getHeight(pRoot->right->right) - getHeight(pRoot->right->left) == 1) {
            singleRightRotate(pRoot);
        } else {
            //left right case
            doubleRightRotate(pRoot);
        }
    }
}

bool isAVL(Node* pRoot) {
    if (pRoot == NULL) {
        return true;
    }

    if (abs(getHeight(pRoot->left) - getHeight(pRoot->right)) > 1) {
        return false;
    }

    return isAVL(pRoot->left) && isAVL(pRoot->right);
}

//BINARY SEARCH TREE OPERATIONS
//Pre-order traversal
void NLR(Node* pRoot) {
    if (pRoot == NULL) {
        return;
    }

    cout << pRoot->key << " ";
    NLR(pRoot->left);
    NLR(pRoot->right);
}

//In-order traversal
void LNR(Node* pRoot) {
    Node* p = pRoot;

    stack<Node*> s;

    while (p != NULL || s.empty() == false) {
        if (p != NULL) {
            s.push(p);
            p = p->left;
        } else {
            p = s.top();
            s.pop();

            cout << p->key << " ";
            p = p->right;
        }
    }
}

//Post-order traversal
void LRN(Node* pRoot) {
    Node* p = pRoot;
    Node* q = pRoot;

    stack<Node*> s;

    while (p != NULL) {
        for (; p->left; p = p->left) {
            s.push(p);
        }

        while (p->right == NULL || p->right == q) {
            cout << p->key << " ";

            q = p; //note the node that has just been processed

            if (s.empty()) {
                return;
            }

            p = s.top();
            s.pop();
        }

        s.push(p);
        p = p->right;
    }
}

//Level-order traversal
void levelOrder(Node* pRoot) {
    if (pRoot == NULL) {
        return;
    }

    queue<Node*> q;

    q.push(pRoot);

    while (q.empty() == false) {
        Node* p = q.front();
        q.pop();

        cout << p->key << " ";

        if (p->left != NULL) {
            q.push(p->left);
        }

        if (p->right != NULL) {
            q.push(p->right);
        }
    }
}

Node* search(Node* pRoot, int x) {
    if (pRoot == NULL) {
        return NULL;
    }

    if (pRoot->key == x) {
        return pRoot;
    }

    if (x < pRoot->key) {
        return search(pRoot->left, x);
    } else {
        return search(pRoot->right, x);
    }
}

int countNode(Node* pRoot) {
    if (pRoot == NULL) {
        return 0;
    }

    return 1 + countNode(pRoot->left) + countNode(pRoot->right);
}

int sumNode(Node* pRoot) {
    if (pRoot == NULL) {
        return 0;
    }

    return pRoot->key + sumNode(pRoot->left) + sumNode(pRoot->right);
}