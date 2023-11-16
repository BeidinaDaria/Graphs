#pragma once

#include <list>
#include <vector>
#include <random>
#include <iostream>
#include <fstream>
#include <numeric>


using sizetype = size_t;
using weighttype = size_t;

//  Ребро
struct edge {
	//  Куда ведёт ребро
	sizetype dest;
	//  Вес ребра
	weighttype weight;
	edge(sizetype Dest, weighttype W) : dest(Dest), weight(W) {}
};

//  Вершина графа
class vertex {
public:
	//  Имя - это просто номер/индекс
	sizetype name;
	//  Список смежных вершин
	std::list<edge> adj;

	vertex(sizetype Name) : name(Name) {}
	
	//  Добавление ребра
	void addEdge(sizetype dest, weighttype w) {
		adj.push_back(edge(dest, w));
	}
};

//  Представление графа
class graph {
public:
	//  Количество вершин
	sizetype size;

	// Список вершин (со списками смежности)
	std::vector<vertex> vertices;
	
	//  Генерация случайного графа
	void generateGraph(sizetype Size) {
		size = Size;
		vertices.clear();
		vertices.reserve(size);
		//  Сразу заполняем вектор вершин
		for (sizetype i = 0; i < size; ++i)
			vertices.push_back(vertex(i));

		std::default_random_engine generator;
		std::uniform_int_distribution<sizetype> distribution(0, size-1);
		std::uniform_int_distribution<sizetype> distribution2(0, std::numeric_limits<sizetype>::max()/100000/size);

		//  Отметки рёбер, которые уже добавлены
		std::vector<sizetype> marks(size, std::numeric_limits<sizetype>::max());

		for (sizetype vert = 0; vert < size; ++vert) {
			
			//  Случайно добавляем рёбра
			for (size_t i = 0; i < size / 3; ++i) {
				sizetype dest = distribution(generator);
				weighttype w = distribution2(generator);
				
				//  Если это петля или такое ребро уже добавляли, то пропуск
				if (dest == vert || marks[dest] == vert) continue;

				vertices[vert].addEdge(dest, w);
				//vertices[dest].addEdge(vert, w);
				//  Значит, ребро из vert в dest уже было
				marks[dest] = vert;
			}
		}
	}

	void printGraph() {
		std::cout << "-----------Graph-----------\n  Size : " << size << std::endl;

		for (sizetype i = 0; i < size; ++i) {
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
		for (sizetype i = 0; i < size; i++) 
			if(vertices[i].adj.size() > 0)
			{
				out << i << ' ' << vertices[i].adj.size() << '\n';
				for (auto edg : vertices[i].adj)
					out << edg.dest << ' ' << edg.weight << '\n';
			}
		out.close();
	}

	void loadFromFile(std::string filename) {
		std::ifstream in(filename, std::ios_base::in);
		sizetype Size;
		in >> Size;
		size = Size;
		vertices.clear();
		vertices.reserve(size);
		for (sizetype i = 0; i < size; ++i)
			vertices.push_back(vertex(i));

		sizetype vert, N;
		while (in >> vert >> N) {
			for (sizetype i = 0; i < N; ++i) {
				sizetype dest;
				weighttype w;
				in >> dest >> w;
				vertices[vert].addEdge(dest, w);
			}
		}
		in.close();
	}
};