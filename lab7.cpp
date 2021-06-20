#include <iostream>
#include "heap.hpp"
#include "classes.h"

int main()
{
    Group g1("A");
    Group g2("B");
    Group g3("C");
    Group g4("D");
    Group g5("E");
    Group g6("F");
    Group g7("G");
    Group g8("H");
    Group g9("I");
    Group g10("J");
    BinominalHeap<Group> tree;

    tree.Insert(g1);
    tree.Insert(g2);
    tree.Insert(g3);
    tree.Insert(g4);
    tree.Insert(g5);
    tree.Insert(g6);
    tree.Insert(g7);
    tree.Insert(g8);
    tree.Insert(g9);
    tree.Print();
    std::cout << std::endl;
    tree.Insert(g10);
    std::cout << "NEW TREE\n";
    tree.Print();
    std::cout << std::endl;

    std::cout << "EXTRACT MIN\n";
    tree.ExtractMin();
    tree.Print();
    return 0;
}


