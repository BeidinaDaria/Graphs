#include <vector>
#include <random>
#include <iostream>
#include <fstream>
#include <numeric>
#include <list>


using sizet = size_t;
using weightt = size_t;

//  Ребро
struct edge {
	//  Куда ведёт ребро
	sizet dest;
	//  Вес ребра
	weightt weight;
	edge(sizet Dest, weightt W) : dest(Dest), weight(W) {}
};

//  Вершина графа
class vertex {
public:
	//  Имя - это просто номер/индекс
	sizet name;
	//  Список смежных вершин
	std::list<edge> adj;

	vertex(sizet Name) : name(Name) {}

	//  Добавление ребра
	void addEdge(sizet dest, weightt w) {
		adj.push_back(edge(dest, w));
	}
};

//  Представление графа
class graph {
public:
	//  Количество вершин
	sizet size;

	// Список вершин (со списками смежности)
	std::vector<vertex> vertices;

	//  Генерация случайного графа
	void generateGraph(sizet Size) {
		size = Size;
		vertices.clear();
		vertices.reserve(size);
		//  Сразу заполняем вектор вершин
		for (sizet i = 0; i < size; ++i)
			vertices.push_back(vertex(i));

		std::default_random_engine generator;
		std::uniform_int_distribution<sizet> distribution(0, size - 1);
		std::uniform_int_distribution<sizet> distribution2(0, std::numeric_limits<sizet>::max() / 100000 / size);

		//  Отметки рёбер, которые уже добавлены
		std::vector<sizet> marks(size, std::numeric_limits<sizet>::max());

		for (sizet vert = 0; vert < size; ++vert) {

			//  Случайно добавляем рёбра
			for (size_t i = 0; i < size / 3; ++i) {
				sizet dest = distribution(generator);
				weightt w = distribution2(generator)%10;

				//  Если это петля или такое ребро уже добавляли, то пропуск
				if (dest == vert || marks[dest] == vert) continue;

				vertices[vert].addEdge(dest, w);
				vertices[dest].addEdge(vert, w);
				//vertices[dest].addEdge(vert, w);
				//  Значит, ребро из vert в dest уже было
				marks[dest] = vert;
			}
		}
	}

	void printGraph() {
		std::cout << "-----------Graph-----------\n  Size : " << size << std::endl;

		for (sizet i = 0; i < size; ++i) {
			std::cout << " " << i << " : ";
			for (auto edg : vertices[i].adj) {
				std::cout << edg.dest << "(" << edg.weight << ")  ";
			}
			std::cout << '\n';
		}
		std::cout << "---------------------------------------\n";
	}

	void saveToFile(std::string filename) {
		std::ofstream out(filename, std::ios_base::out);
		out << size << '\n';
		for (sizet i = 0; i < size; i++)
			if (vertices[i].adj.size() > 0)
			{
				out << i << ' ' << vertices[i].adj.size() << '\n';
				for (auto edg : vertices[i].adj)
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

std::vector<long long> Deikstra(graph G, int v);