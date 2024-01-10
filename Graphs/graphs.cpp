#include "graphs.h"

std::vector<int> Deikstra(graph g, int startVertex,int lastVertex) {
    std::vector<bool> visited(g.size,false);//ïîñåùåííûå âåðøèíû
    std::vector<int> distances(g.size, INT16_MAX); // êðàò÷àéøèå ïóòè èç ñòàðòîâîé âåðøèíû
    std::vector<int> path; // êðàò÷àéøèé ïóòü
    visited.resize(g.size);
    distances.resize(g.size);

    std::vector<vertex> vertices = g.vertices; // ñïèñîê âåðøèí ãðàôà
    int temp, minindex, min;
    distances[startVertex] = 0;
    int k=0;
    // Øàã àëãîðèòìà
    do {
        minindex = INT16_MAX;
        min = INT16_MAX;
        for (int i = 0; i < g.size; i++)
        { // Åñëè âåðøèíó åù¸ íå îáîøëè è âåñ ìåíüøå min
            if ((visited[i] == 0) && (distances[i] < min))
            { // Ïåðåïðèñâàèâàåì çíà÷åíèÿ
                min = distances[i];
                minindex = i;
            }
        }
        // Äîáàâëÿåì íàéäåííûé ìèíèìàëüíûé âåñ
        // ê òåêóùåìó âåñó âåðøèíû
        // è ñðàâíèâàåì ñ òåêóùèì ìèíèìàëüíûì âåñîì âåðøèíû
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
    } while (minindex < INT16_MAX);

    // Âîññòàíîâëåíèå ïóòè 
    path.insert(path.begin(), lastVertex);
    int weight = distances[lastVertex]; // âåñ êîíå÷íîé âåðøèíû

    while (lastVertex != startVertex) // ïîêà íå äîøëè äî íà÷àëüíîé âåðøèíû
    {
        for (auto edg : vertices[lastVertex].edgeList)
        {
            temp = weight - edg.weight; // îïðåäåëÿåì âåñ ïóòè èç ïðåäûäóùåé âåðøèíû
            if (temp == distances[edg.dest]) // åñëè âåñ ñîâïàë ñ ðàññ÷èòàííûì
            {                 // çíà÷èò èç ýòîé âåðøèíû è áûë ïåðåõîä
                weight = temp; // ñîõðàíÿåì íîâûé âåñ
                lastVertex = edg.dest;       // ñîõðàíÿåì ïðåäûäóùóþ âåðøèíó
                path.insert(path.begin(), edg.dest); // è çàïèñûâàåì åå â ìàññèâ
                break;
            }
        }
    }
    return path;
}
