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

void insert(RBNode* &pRoot, int key) {

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