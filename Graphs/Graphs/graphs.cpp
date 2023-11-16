#include "graphs.h"
#include <map>

std::vector<long long> Deikstra(graph G,int v) {
	std::vector<long long> S(G.size);//вектор результата 
    std::vector<bool> Fl(G.size,false);//вектор посещенных вершин
    Fl[v] = true;
    auto it = G.vertices[v].adj.begin();
    for (int ind = 0; ind < G.vertices[v].adj.size(); ind++) {//цикл по списку смежности искомой вершины
	    edge k = *it;//ребро искомой вершины
        S[k.dest] = k.weight;//занесение веса в вектор результата
        Fl[k.dest] = true;//отметка о посещении
        it++;
	}
    bool f = true;//флаг - есть ли непосещенные вершины
    for (int ind = 0; ind < G.vertices[v].adj.size(); ind++){//цикл проверка посещенности вершин
        if (!Fl[ind]) {
            f = false;
            break;
        }
    }
    int pred = v;
    while (!f){//пока не все вершины посещены
        for (int ind = 0; ind < G.vertices.size(); ind++) {//цикл по вершинам графа
            if (!Fl[ind]) {//если вершина не посещена
                std::list<edge> th= G.vertices[ind].adj;//список смежности непосещенной вершины
                it = th.begin();
                for (int k = 0; k < th.size(); k++) {//цикл по списку смежности непосещенной вершины
                    if (Fl[it->dest]) {//если вершина была посещена, от искомой до непосещенной вершины можно посчитать вес
                        if ((S[ind]==0)||(S[ind] > S[it->dest] + it->weight)) {//если вес от искомой вершины графа + вес от посещенной 
                            S[ind] = S[it->dest] + it->weight;
                            Fl[ind] = true;
                        }
                    }
                    it++;
                }
            }
        }
        f = true;
        for (int ind = 0; ind < G.vertices[v].adj.size(); ind++) {//цикл проверка посещенности вершин
            if (!Fl[ind]) {
                f = false;
                break;
            }
        }
    }
    return S;
}