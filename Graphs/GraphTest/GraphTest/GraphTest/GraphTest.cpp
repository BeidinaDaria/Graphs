// GraphTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Graph.h"

using namespace std;

int main()
{
    graph G;
    G.generateGraph(1000);
    //G.printGraph();
    G.saveToFile("graph.txt");
    G.loadFromFile("graph.txt");
    //G.printGraph();
    system("graph.txt");
    system("pause");
}

