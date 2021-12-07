#include <iostream>
#include "BST.h"
using namespace std;

int main() {
    Tree* t = new Tree();
    t->add(10);
    t->add(9);
    t->add(12);
    t->add(2);
    t->add(22);
    t->add(20);
    t->add(11);
    Node* a = t->search(10);
    t->deleteSearched(a);
}
