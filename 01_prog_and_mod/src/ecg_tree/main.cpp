// Uni ECG
// Übung 1
// 2.05.2021

#include "node.h"
#include <iostream>


int main()
{
    // SECTION - Aufgabe 1.1.2
    Node * root = new Node("root");

    // NOTE - Explizite Weise
    // Node * lc = new Node("left child");
    // Node * rc = new Node("right child");
    // root->add_child(lc);
    // root->add_child(rc);

    // NOTE - Implizite Weise
    root->add_child(new Node("left child"));
    root->add_child(new Node("right child"));

    delete root;
    // !SECTION - Aufgabe 1.1.2

    // ANCHOR - Aufgabe 1.2.1
    Node * auto_id = new Node();
    delete auto_id;

    // ANCHOR - Aufgabe 1.2.2
    Node * tree = create_complete_tree(2,4);

    // ANCHOR - Aufgabe 1.2.3
    // tree->print(std::cout);
    std::cout << tree;

    return 0;
}