#include <iostream>

struct NODE {
    int key;
    NODE* pNext;
};

//define a circular linked list using pTail, because it can be easy to access both pTail and pHead
struct List {
    NODE* pTail;
};

NODE* createNode(int data) {
    NODE* ans = new NODE();

    if (!ans) {
        return nullptr;
    }

    ans->key = data;
    ans->pNext = nullptr;

    return ans;
}

void initList(List& l) {
    l.pTail = nullptr;
}

bool isEmpty(List l) {
    return (l.pTail == nullptr);
}

bool addHead(List& l, int data) {
    NODE* newNode = createNode(data);

    if (!newNode) {
        return false;
    }

    if (isEmpty(l)) {
        l.pTail = newNode;
        l.pTail->pNext = l.pTail;

        return true;
    }

    if (l.pTail->pNext == l.pTail) {
        l.pTail->pNext = newNode;
        newNode->pNext = l.pTail;

        return true;
    }

    NODE* oldHead = l.pTail->pNext;

    newNode->pNext = oldHead;

    l.pTail->pNext = newNode;

    return true;
}

bool addTail(List& l, int data) {
    NODE* newNode = createNode(data);

    if (!newNode) {
        return false;
    }


    if (isEmpty(l)) {
        l.pTail = newNode;
        l.pTail->pNext = l.pTail;

        return true;
    }

    if (l.pTail->pNext == l.pTail) {
        l.pTail->pNext = newNode;
        newNode->pNext = l.pTail;
        l.pTail = newNode;

        return true;
    }

    newNode->pNext = l.pTail->pNext;
    l.pTail->pNext = newNode;
    l.pTail = newNode;

    return true;

}

bool removeHead(List& l) {
    if (isEmpty(l)) {
        return false;
    }

    if (l.pTail->pNext == l.pTail) {
        delete l.pTail;
        l.pTail = nullptr;

        return true;
    }

    NODE* oldHead = l.pTail->pNext;
    l.pTail->pNext = oldHead->pNext;

    delete oldHead;
    oldHead = nullptr;

    return true;
}

bool removeTail(List& l) {
    if (isEmpty(l)) {
        return false;
    }

    if (l.pTail->pNext == l.pTail) {
        delete l.pTail;
        l.pTail = nullptr;

        return true;
    }

    NODE* oldTail = l.pTail;
    NODE* oldPrev = l.pTail;

    while (oldPrev->pNext != oldTail) {
        oldPrev = oldPrev->pNext;
    }

    oldPrev->pNext = oldTail->pNext;
    l.pTail = oldPrev;
    delete oldTail;
    oldTail = nullptr;


    return true;
}

bool addAfter(List& l, int data, int val) {
    if (isEmpty(l)) {
        return false;
    }

    if (l.pTail->pNext == l.pTail) {
        if (l.pTail->key == val) {
            addTail(l, data);

            return true;
        }
        else {
            return false;
        }
    }

    if (l.pTail->key == val) {
        addTail(l, data);

        return true;
    }

    //insertHere is the node that contains the key equal to val,
    //it will be pTail if there is no such node.
    NODE* insertHere = l.pTail;

    do {
        insertHere = insertHere->pNext;

        if (insertHere->key == val) {
            break;
        }
    } while (insertHere != l.pTail);

    if (insertHere == l.pTail) {
        return false;
    }

    NODE* newNode = createNode(data);
    newNode->pNext = insertHere->pNext;
    insertHere->pNext = newNode;

    return true;

}

bool removeAfter(List& l, int val) {
    if (isEmpty(l)) {
        return false;
    }

    if (l.pTail->pNext == l.pTail) {
        if (l.pTail->key == val) {
            removeTail(l);

            return true;
        }
        else {
            return false;
        }
    }

    if (l.pTail->key == val) {
        removeTail(l);

        return true;
    }

    //removeHere is the node that contains the key equal to val,
    //it will be pTail if there is no such node.
    NODE* removeHere = l.pTail;

    do {
        removeHere = removeHere->pNext;

        if (removeHere->key == val) {
            break;
        }
    } while (removeHere != l.pTail);

    if (removeHere == l.pTail) {
        return false;
    }

    NODE* before = removeHere;
    removeHere = removeHere->pNext;
    before->pNext = removeHere->pNext;
    delete removeHere;
    removeHere = nullptr;

    return true;

}

void printList(List l) {
    if (isEmpty(l)) {
        std::cout << "Empty list!";

        return;
    }

    if (l.pTail->pNext == l.pTail) {
        std::cout << l.pTail->key << "\n";

        return;
    }

    NODE* here = l.pTail->pNext;
    NODE* end = l.pTail->pNext;
    do {
        std::cout << here->key << " ";

        here = here->pNext;
    } while (here != end);

    std::cout << "\n";
}

int main() {
    List l;
    initList(l);
    addHead(l, 4);
    addHead(l, 7);
    addTail(l, 5);
    addTail(l, 9);
    printList(l);

    removeHead(l);
    removeTail(l);
    addHead(l, 8);
    addTail(l, 10);
    printList(l);

    addAfter(l, 6, 4);
    printList(l);
    removeAfter(l, 6);
    printList(l);

    return 0;
}