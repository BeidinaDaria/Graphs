#include <vector>
#include <random>
#include <iostream>
#include <fstream>
#include <numeric>
#include <list>

using sizet = int;
using weightt = int;

//  Ребро
struct edge {
	//  Куда ведёт ребро
	sizet dest;
	//  Вес ребра (расстояние или стоимость проезда)
	weightt weight;
	edge(sizet Dest, weightt W) : dest(Dest), weight(W) {}
	
};

//  Вершина графа
struct vertex {
	//  Имя - это просто номер/индекс вершины
	sizet name;
	//  Список рёбер
	std::list<edge> edgeList;

	vertex(sizet Name) : name(Name) {}

	//  Добавление ребра
	void addEdge(sizet dest, weightt w) {
		edgeList.push_back(edge(dest, w));
	}
};

//  Представление графа
struct graph {
	//  Количество вершин
	sizet size;

	// Список вершин (со списками смежности - список ребер, идущих от этой вершины)
	std::vector<vertex> vertices;

	//  Генерация случайного графа
	void generateGraph(sizet Size) {
		size = Size;
		int k;
		vertices.clear();//очистка списка от прошлых значений
		vertices.reserve(size);//выделение памяти
		//  Сразу заполняем вектор вершин
		for (sizet i = 0; i < size; ++i)
			vertices.push_back(vertex(i));//заполнение списка всеми вершинами графа

		//  Отметки рёбер, которые уже добавлены
		std::vector<sizet> marks(size, std::numeric_limits<sizet>::max());
		srand(time(NULL));
		sizet dest;
		weightt w;

		for (sizet vert = 0; vert < size; ++vert) {
			k = rand()%10+1;
			//  Случайно добавляем рёбра
			for (size_t i = 0; i < k; ++i) {
				dest = rand()%size;
				w = rand() % 10+1;

				//  Если это петля или такое ребро уже добавляли, то пропуск
				if (dest == vert || marks[dest] == vert) continue;

				vertices[vert].addEdge(dest, w);
				//  Значит, ребро из vert в dest уже было
				marks[dest] = vert;

				//Если закомментировать, получим направленный граф: то есть, каждое ребро 
				// может работать только в одном направлении  
				vertices[dest].addEdge(vert, w);
				marks[vert] = dest;
			}
		}
	}

	void printGraph() {
		std::cout << "-----------Graph-----------\n  Size : " << size << std::endl;

		for (sizet i = 0; i < size; ++i) {
			std::cout << i << ": ";
			for (auto edg : vertices[i].edgeList) {
				std::cout << edg.dest << "(" << edg.weight << ")  ";
			}
			std::cout << '\n';
		}
		std::cout << "---------------------------------------\n";
	}

	void saveToFile(const char* filename) {
		std::ofstream out(filename, std::ios_base::out);//пользуемся встроенным классом вывода в файл
		out << size << '\n';//записываем количество вершин
		for (sizet i = 0; i < size; i++)
			if (vertices[i].edgeList.size() > 0){

				// записываем номер вершины и количество ребер, исходящих из неё
				out << i << ' ' << vertices[i].edgeList.size() << '\n';
				for (auto edg : vertices[i].edgeList)
					out << edg.dest << ' ' << edg.weight << '\n';
			}
		out.close();
	}

	void loadFromFile(std::string filename) {
		std::ifstream in(filename, std::ios_base::in);
		sizet Size;
		in >> Size;
		size = Size;
		vertices.clear();
		vertices.reserve(size);
		for (sizet i = 0; i < size; ++i)
			vertices.push_back(vertex(i));

		sizet vert, N;
		while (in >> vert >> N) {
			for (sizet i = 0; i < N; ++i) {
				sizet dest;
				weightt w;
				in >> dest >> w;
				vertices[vert].addEdge(dest, w);
			}
		}
		in.close();
	}
};

std::vector<int> Deikstra(graph g, int startVertex,int lastVertex);