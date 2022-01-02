//Reference: https://www.geeksforgeeks.org/priority-queue-using-linked-list/

#include <iostream>
#include <string>

using std::string;

//priority_queue using linked list
struct PQNode {
    string id;

    unsigned order;

    unsigned priority;

    PQNode* next;
};

PQNode* getNode(string id, unsigned priority) {
    PQNode* p = new PQNode;
    p->id = id;
    p->priority = priority;
    p->next = nullptr;

    return p;
}

bool isEmpty(PQNode* head, PQNode* pTail) {
    return (head == nullptr);
}

void insert(PQNode* &head, PQNode* &tail, string id, unsigned priority) {
    PQNode* p = getNode(id, priority);

    if (isEmpty(head, tail)) {
        p->order = 1;
        head = p;
        tail = p;
    } else {
        PQNode* cur = head;
        PQNode* prev = nullptr;

        while (cur != nullptr && cur->priority < priority) {
            prev = cur;
            cur = cur->next;
        }

        if (cur == head) {
            p->order = 1;
            p->next = head;

            head = p;
        } else {
            p->order = prev->order + 1;
            p->next = cur;

            prev->next = p;
        }

        if (cur == nullptr) {
            tail = p;
        } else {
            while (cur != nullptr) {
                cur->order++;
                cur = cur->next;
            }
        }
    }
}

PQNode* extract(PQNode* &head, PQNode* &tail) {
    if (isEmpty(head, tail)) {
        return nullptr;
    }

    PQNode* p = head;
    head = head->next;

    for (PQNode* cur = head; cur != nullptr; cur = cur->next) {
        cur->order--;
    }

    if (head == nullptr) {
        tail = nullptr;
    }

    return p;
}

void remove(PQNode* &head, PQNode* &tail, string ID) {
    PQNode* cur = head;
    PQNode* prev = nullptr;

    while (cur != nullptr && cur->id != ID) {
        prev = cur;
        cur = cur->next;
    }

    if (cur == nullptr) {
        return;
    }

    if (cur == head) {
        head = head->next;
    } else {
        prev->next = cur->next;
    }

    if (cur == tail) {
        tail = prev;
    }

    for (PQNode* p = cur->next; p != nullptr; p = p->next) {
        p->order--;
    }

    delete cur;
}

void changePriority(PQNode* head, PQNode* tail, string ID, int priority) {
    remove(head, tail, ID);

    insert(head, tail, ID, priority);
}

int main() {
    PQNode* head = nullptr;
    PQNode* tail = nullptr;

    insert(head, tail, "A", 1);
    insert(head, tail, "B", 2);
    insert(head, tail, "C", 4);
    insert(head, tail, "D", 3);
    insert(head, tail, "E", 0);

    for (PQNode* p = head; p != nullptr; p = p->next) {
        std::cout << p->id << " " << p->priority << " " << p->order << "\n";
    }

    remove(head, tail, "B");

    for (PQNode* p = head; p != nullptr; p = p->next) {
        std::cout << p->id << " " << p->priority << " " << p->order << "\n";
    }

    return 0;
}