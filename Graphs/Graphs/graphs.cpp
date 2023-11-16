#include "graphs.h"
#include <map>

std::vector<long long> Deikstra(graph G,int v) {
	std::vector<long long> S(G.size);//������ ���������� 
    std::vector<bool> Fl(G.size,false);//������ ���������� ������
    Fl[v] = true;
    auto it = G.vertices[v].adj.begin();
    for (int ind = 0; ind < G.vertices[v].adj.size(); ind++) {//���� �� ������ ��������� ������� �������
	    edge k = *it;//����� ������� �������
        S[k.dest] = k.weight;//��������� ���� � ������ ����������
        Fl[k.dest] = true;//������� � ���������
        it++;
	}
    bool f = true;//���� - ���� �� ������������ �������
    for (int ind = 0; ind < G.vertices[v].adj.size(); ind++){//���� �������� ������������ ������
        if (!Fl[ind]) {
            f = false;
            break;
        }
    }
    int pred = v;
    while (!f){//���� �� ��� ������� ��������
        for (int ind = 0; ind < G.vertices.size(); ind++) {//���� �� �������� �����
            if (!Fl[ind]) {//���� ������� �� ��������
                std::list<edge> th= G.vertices[ind].adj;//������ ��������� ������������ �������
                it = th.begin();
                for (int k = 0; k < th.size(); k++) {//���� �� ������ ��������� ������������ �������
                    if (Fl[it->dest]) {//���� ������� ���� ��������, �� ������� �� ������������ ������� ����� ��������� ���
                        if ((S[ind]==0)||(S[ind] > S[it->dest] + it->weight)) {//���� ��� �� ������� ������� ����� + ��� �� ���������� 
                            S[ind] = S[it->dest] + it->weight;
                            Fl[ind] = true;
                        }
                    }
                    it++;
                }
            }
        }
        f = true;
        for (int ind = 0; ind < G.vertices[v].adj.size(); ind++) {//���� �������� ������������ ������
            if (!Fl[ind]) {
                f = false;
                break;
            }
        }
    }
    return S;
}