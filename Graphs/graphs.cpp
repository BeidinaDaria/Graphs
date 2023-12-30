#include "graphs.h"

std::vector<int> Deikstra(graph g, int startVertex,int lastVertex) {
    std::vector<bool> visited(g.size,false);//���������� �������
    std::vector<int> distances(g.size, INT16_MAX); // ���������� ���� �� ��������� �������
    std::vector<int> path; // ���������� ����
    visited.resize(g.size);
    distances.resize(g.size);

    std::vector<vertex> vertices = g.vertices; // ������ ������ �����
    int temp, minindex, min;
    distances[startVertex] = 0;
    int k=0;
    // ��� ���������
    do {
        minindex = INT16_MAX;
        min = INT16_MAX;
        for (int i = 0; i < g.size; i++)
        { // ���� ������� ��� �� ������ � ��� ������ min
            if ((visited[i] == 0) && (distances[i] < min))
            { // ��������������� ��������
                min = distances[i];
                minindex = i;
            }
        }
        // ��������� ��������� ����������� ���
        // � �������� ���� �������
        // � ���������� � ������� ����������� ����� �������
        if (minindex != INT16_MAX)
        {
            for (auto edg:vertices[minindex].edgeList)
            {
                temp = min + edg.weight;
                if (temp < distances[edg.dest])
                {
                    distances[edg.dest] = temp;
                }
            }
            visited[minindex] = true;
        }
    } while (minindex < 10000);

    // �������������� ���� 
    path.insert(path.begin(), lastVertex);
    int weight = distances[lastVertex]; // ��� �������� �������

    while (lastVertex != startVertex) // ���� �� ����� �� ��������� �������
    {
        for (auto edg : vertices[lastVertex].edgeList)
        {
            temp = weight - edg.weight; // ���������� ��� ���� �� ���������� �������
            if (temp == distances[edg.dest]) // ���� ��� ������ � ������������
            {                 // ������ �� ���� ������� � ��� �������
                weight = temp; // ��������� ����� ���
                lastVertex = edg.dest;       // ��������� ���������� �������
                path.insert(path.begin(), edg.dest); // � ���������� �� � ������
                break;
            }
        }
    }
    return path;
}