//Reference 1: https://www.programiz.com/dsa/insertion-in-a-red-black-tree
//Reference 2: https://stackoverflow.com/questions/69748159/calculating-the-black-height-of-a-red-black-tree
//Reference 3: to be told later, if available

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

RBNode* createTree(int a[], int n) {
    RBNode* pRoot = nil;

    for (int i = 0; i < n; i++) {
        insert(pRoot, a[i]);
    }

    return pRoot;
}

RBNode* lookUp(RBNode* pRoot, int key) {
    RBNode* ans = pRoot;

    while (ans != nil) {
        if (ans->key == key) {
            return ans;
        }

        if (ans->key > key) {
            ans = ans->left;
        } else {
            ans = ans->right;
        }
    }

    return nil;
}

//height here is counted by the maximum number of NODES on paths
int height(RBNode* pRoot) {
    if (pRoot == nil) {
        return 1;
    } 
    
    return std::max(height(pRoot->left), height(pRoot->right)) + 1;
}

//black height is counted by the number of NODES on paths from the root to the leaves
int blackHeight(RBNode* pRoot) {
    if (pRoot == nil) {
        return 1;
    }

    int leftBlackHeight = blackHeight(pRoot->left);
    int rightBlackHeight = blackHeight(pRoot->right);

    if (leftBlackHeight != rightBlackHeight) {
        return 0;
    }

    if (pRoot->color == false) {
        leftBlackHeight++;
    }

    return leftBlackHeight;
}

void removeLeftAdjust(RBNode* pRoot, RBNode* ref) {
    RBNode* p = ref->parent->right;

    if (p->color == true) {
        p->color = false;

        ref->parent->color = true;

        leftRotate(pRoot, ref->parent);

        p = ref->parent->right;
    }

    if (p->right->color == false && p->left->color == false) {
        p->color = true;

        ref = ref->parent;
    } else {
        if (p->right->color == false) {
            p->left->color = false;
            p->color = true;
            
            rightRotate(pRoot, p);
            p = ref->parent->right;
        }

        p->color = ref->parent->color;

        ref->parent->color = false;

        p->right->color = false;

        leftRotate(pRoot, ref->parent);

        ref = pRoot;
    }
}

void removeRightAdjust(RBNode* pRoot, RBNode* ref) {
    RBNode* p = ref->parent->left;

    if (p->color == true) {
        p->color = false;

        ref->parent->color = true;

        rightRotate(pRoot, ref->parent);

        p = ref->parent->left;
    }

    if (p->left->color == false && p->right->color == false) {
        p->color = true;

        ref = ref->parent;
    } else {
        if (p->left->color == false) {
            p->right->color = false;
            p->color = true;

            leftRotate(pRoot, p);
            p = ref->parent->left;
        }

        p->color = ref->parent->color;

        ref->parent->color = false;

        p->left->color = false;

        rightRotate(pRoot, ref->parent);

        ref = pRoot;
    }
}

void removeFixedUp(RBNode* pRoot, RBNode* ref) {
    while ((ref->color == false) && (ref != pRoot)) {
        if (ref == ref->parent->left) {
            removeLeftAdjust(pRoot, ref);
        } else {
            removeRightAdjust(pRoot, ref);
        }
    }

    ref->color = false;
}

RBNode* minimum(RBNode* pRoot, RBNode* ref) {
    while (ref->left != nil) {
        ref = ref->left;
    }

    return ref;
}

RBNode* maximum(RBNode* pRoot, RBNode* ref) {
    while (ref->right != nil) {
        ref = ref->right;
    }

    return ref;
}

RBNode* treeSuccessor(RBNode* pRoot, RBNode* ref) {
    if (ref->right != nil) {
        return minimum(pRoot, ref->right);
    }

    RBNode* y = ref->parent;

    while (y != nil && ref == y->right) {
        ref = y;
        y = y->parent;
    }

    return y;
}

//return 0 if key does not appear in tree, therefore cannot remove
//return 1 if successfully remove
int remove(RBNode* pRoot, int key) {
    RBNode* pFind = lookUp(pRoot, key);

    if (pFind == nil) {
        return 0;
    }

    RBNode* y;
    if (pFind->left == nil || pFind->right == nil) {
        y = pFind;
    } else {
        y = treeSuccessor(pRoot, pFind);
    }
    
    RBNode* x;
    if (y->left != nil) {
        x = y->left;
    } else {
        x = y->right;
    }

    if (x != nil) {
        x->parent = y->parent;
    }

    if (y->parent == nil) {
        pRoot = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }

    if (y != pFind) {
        pFind->key = y->key;
    }

    if (y->color == false) {
        removeFixedUp(pRoot, x);
    }

    delete y;
}

int main() {
    nil = new RBNode;
    nil->color = false;
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;

    RBNode* root = nil;
}

//Remember to implement the priority queue using linked list on week 4