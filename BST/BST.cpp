// BST.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "BST.h"

int main()
{
    Tree* tree = new Tree();
    Data* a = new Data();
    a->dataChar = 'a';
    a->dataInt = 3;
    tree->add(*a);
    Data* b = new Data();
    b->dataInt = 2;
    b->dataChar = 'b';
    tree->add(*b);
    Data* c = new Data();
    c->dataInt = 4;
    c->dataChar = 'c';
    tree->add(*c);
    Data* d = new Data();
    d->dataInt = 5;
    d->dataChar = 'c';
    tree->add(*d);
    Data* e = new Data();
    e->dataInt = 3;
    e->dataChar = 'a';
    Leaf* l = tree->search(*e);
    tree->del(l);
    //tree->preorder();
    //tree->inorder();
    //tree->clean();
    //tree->height();
    tree->to_string();
    


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
