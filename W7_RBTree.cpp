//Reference 1: https://www.programiz.com/dsa/insertion-in-a-red-black-tree
//Reference 2: to be told later, if available

#include <iostream>

struct RBNode{
    int key;

    bool color; //black = false

    RBNode* parent;

    RBNode* left;

    RBNode* right;
};

RBNode* nil;

RBNode* getNode(int key, bool color, RBNode* nil) {
    RBNode* p = new RBNode;
    p->key = key;
    p->color = color;
    p->parent = nil;
    p->left = nil;
    p->right = nil;

    return p;
}

void leftRotate(RBNode* &pRoot, RBNode* ref) {
    RBNode* p = ref->right;
    ref->right = p->left;

    if (p->left != nil) {
        p->left->parent = ref;
    }

    p->parent = ref->parent;

    if (ref->parent == nil) {
        pRoot = p;
    } else if (ref == ref->parent->left) {
        ref->parent->left = p;
    } else {
        ref->parent->right = p;
    }

    p->left = ref;
    ref->parent = p;
}

void rightRotate(RBNode* &pRoot, RBNode* ref) {
    RBNode* p = ref->left;
    ref->left = p->right;

    if (p->right != nil) {
        p->left->parent = ref;
    }

    p->parent = ref->parent;

    if (ref->parent == nil) {
        pRoot = p;
    } else if (ref == ref->parent->right) {
        ref->parent->right = p;
    } else {
        ref->parent->left = p;
    }

    p->right = ref;
    ref->parent = p;
}

void insertLeftAdjust(RBNode* &pRoot, RBNode* ref) {
    RBNode* p = ref->parent->parent->right;

    if (p->color == true) {
        ref->parent->color = false;

        p->color = false;

        ref->parent->parent->color = true;

        ref = ref->parent->parent;
    } else {
        if (ref == ref->parent->right) {
            ref = ref->parent;

            leftRotate(pRoot, ref);
        }

        ref->parent->color = false;

        ref->parent->parent->color = true;

        rightRotate(pRoot, ref->parent->parent);
    }
}

void insertRightAdjust(RBNode* &pRoot, RBNode* ref) {
    RBNode* p = ref->parent->parent->left;

    if (p->color == true) {
        ref->parent->color = false;

        p->color = false;

        ref->parent->parent->color = true;

        ref = ref->parent->parent;
    } else {
        if (ref == ref->parent->left) {
            ref = ref->parent;

            rightRotate(pRoot, ref);
        }

        ref->parent->color = false;

        ref->parent->parent->color = true;

        leftRotate(pRoot, ref->parent->parent);
    }
}

void inserFixedUp(RBNode*  &pRoot, RBNode* ref) {
    while (ref->parent->color == true) {
        if (ref->parent == ref->parent->parent->left) {
            insertLeftAdjust(pRoot, ref);
        } else {
            insertRightAdjust(pRoot, ref);
        }
    }

    pRoot->color = false;
}

void insert(RBNode* &pRoot, int key) {
    RBNode* ref = getNode(key, true, nil);

    //Binary search tree insertion
    //-----------------------------------------------------//
    RBNode* p = pRoot;
    RBNode* y = nil;

    while (p != nil) {
        y = p;

        if (ref->key < p->key) {
            p = p->left;
        } else {
            p = p->right;
        }
    }

    ref->parent = y;

    if (y == nil) {
        pRoot = ref;
    } else if (ref->key < y->key) {
        y->left = ref;
    } else {
        y->right = ref;
    }
    //-----------------------------------------------------//

    inserFixedUp(pRoot, ref);
}

int main() {
    RBNode* nil;

    nil = new RBNode;
    nil->color = false;
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;

    RBNode* root = nil;
}