#include <iostream>
#include <fstream>
#include <vector>

typedef struct Leader* lref;
typedef struct Trailer* tref;

struct Leader {
    int key; //key of this leader node

    int count; //number of "precedences"

    lref next; //pointer to next leader node

    tref trails; //pointer to list of trailers
};

struct Trailer {
    lref id; //pointer to "successor" leader node

    tref next; //pointer to next trailer node
};

//simply find or addTail
lref find(lref& head, lref& tail, int x) {
    lref p = head;

    tail->key = x;

    while (p->key != x) {
        p = p->next;
    }

    if (p == tail) { //x not found, sentinel method
        tail = new Leader;

        p->count = 0;
        p->trails = NULL;
        p->next = tail;
    }

    return p;
}

void splitZeroFromList(lref& head, lref& tail) {
    lref cur = head;
    lref next = cur;
    
    head = NULL; //create virtual list with count of zeros

    while (next != tail) { //not include tail node
        cur = next;
        next = next->next;

        if (cur->count == 0) {
            //add head new list
            cur->next = head;
            head = cur;
        }
    }
}

//x < y aka x -> y
void input(lref& head, lref& tail, int x, int y) {
    //find and insert to list
    lref xNode = find(head, tail, x);
    lref yNode = find(head, tail, y);

    //add trailer by add head
    tref t = new Trailer;
    t->id = yNode;
    t->next = xNode->trails;

    xNode->trails = t;

    //increase the number of precedences
    yNode->count++;
}

void topoSort(lref& head, lref& tail) {
    splitZeroFromList(head, tail);

    lref p = head;

    while (p != NULL) {
        std::cout << p->key << " ";

        tref t = p->trails;

        p = p->next;

        //iterate through all the trailers
        while (t != NULL) {
            lref succNode = t->id;

            //decrease the number of precedences
            succNode->count--;

            //if the number of precedences is zero, move it the previous of p (current p)
            if (succNode->count == 0) {
                succNode->next = p;

                p = succNode;
            }

            t = t->next;
        }
    }
}

std::vector<std::pair<int, int>> parse(std::string fileName) {
    std::vector<std::pair<int, int>> pv;

    std::pair<int, int> p;
    char ch1, ch2, ch3;

    std::ifstream inFile;
    inFile.open(fileName);

    while (!inFile.eof()) {
        inFile >> ch1 >> p.first >> ch2 >> p.second >> ch3;

        if (inFile.eof()) {
            break;
        }

        pv.push_back(p);
    }

    inFile.close();

    return pv;
}

int main() {
    //create a dummy node
    lref head = new Leader;
    head->key = 0;
    head->count = 0;
    head->next = NULL;
    head->trails = NULL;

    lref tail = head; //sentinel

    std::vector<std::pair<int, int>> pv = parse("input.txt");

    for (int i = 0; i < pv.size(); i++) {
        input(head, tail, pv[i].first, pv[i].second);
    }

    topoSort(head, tail);
    std::cout << "\n";

    return 0;
}