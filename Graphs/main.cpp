#include "graphs.h"
using namespace std;
int main()
{
    graph G;
    G.generateGraph(50);
    G.printGraph();
    G.saveToFile("graph.txt");
    G.loadFromFile("graph.txt");
    //G.printGraph();
    vector<int> res = Deikstra(G, 30,25);
    cout << res[0];
    for (int i = 1; i < res.size(); i++)
        cout << " -> " << res[i];
    cout << endl << "---------------------------------\n";
    system("pause");
}
