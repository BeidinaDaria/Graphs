#include "graphs.h"

std::vector<int> Deikstra(graph g, int startVertex,int lastVertex) {
    std::vector<bool> visited(g.size,false);//посещенные вершины
    std::vector<int> distances(g.size, INT16_MAX); // кратчайшие пути из стартовой вершины
    std::vector<int> path; // кратчайший путь
    visited.resize(g.size);
    distances.resize(g.size);

    std::vector<vertex> vertices = g.vertices; // список вершин графа
    int temp, minindex, min;
    distances[startVertex] = 0;
    int k=0;
    // Шаг алгоритма
    do {
        minindex = INT16_MAX;
        min = INT16_MAX;
        for (int i = 0; i < g.size; i++)
        { // Если вершину ещё не обошли и вес меньше min
            if ((visited[i] == 0) && (distances[i] < min))
            { // Переприсваиваем значения
                min = distances[i];
                minindex = i;
            }
        }
        // Добавляем найденный минимальный вес
        // к текущему весу вершины
        // и сравниваем с текущим минимальным весом вершины
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

    // Восстановление пути 
    path.insert(path.begin(), lastVertex);
    int weight = distances[lastVertex]; // вес конечной вершины

    while (lastVertex != startVertex) // пока не дошли до начальной вершины
    {
        for (auto edg : vertices[lastVertex].edgeList)
        {
            temp = weight - edg.weight; // определяем вес пути из предыдущей вершины
            if (temp == distances[edg.dest]) // если вес совпал с рассчитанным
            {                 // значит из этой вершины и был переход
                weight = temp; // сохраняем новый вес
                lastVertex = edg.dest;       // сохраняем предыдущую вершину
                path.insert(path.begin(), edg.dest); // и записываем ее в массив
                break;
            }
        }
    }
    return path;
}