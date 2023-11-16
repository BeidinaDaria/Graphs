#include <iostream>
#include "graphs.h"
using namespace std;
int main()
{
    graph G;
    G.generateGraph(10000);
    G.printGraph();
    G.saveToFile("graph.txt");
    G.loadFromFile("graph.txt");
    vector<long long> res=Deikstra(G, 990);
    for (int i = 0; i < res.size(); i++)
        cout << i << " -> " << res[i] << endl;
    cout << "---------------------------------\n";
    res = Deikstra(G, 10);
    for (int i = 0; i < res.size(); i++)
        cout << i << " -> " << res[i] << endl;
    //G.printGraph();
    system("graph.txt");
    system("pause");
}
