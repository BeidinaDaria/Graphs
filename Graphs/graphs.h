#include <vector>
#include <random>
#include <iostream>
#include <fstream>
#include <numeric>
#include <list>

using sizet = int;
using weightt = int;

//  �����
struct edge {
	//  ���� ���� �����
	sizet dest;
	//  ��� ����� (���������� ��� ��������� �������)
	weightt weight;
	edge(sizet Dest, weightt W) : dest(Dest), weight(W) {}
	
};

//  ������� �����
struct vertex {
	//  ��� - ��� ������ �����/������ �������
	sizet name;
	//  ������ ����
	std::list<edge> edgeList;

	vertex(sizet Name) : name(Name) {}

	//  ���������� �����
	void addEdge(sizet dest, weightt w) {
		edgeList.push_back(edge(dest, w));
	}
};

//  ������������� �����
struct graph {
	//  ���������� ������
	sizet size;

	// ������ ������ (�� �������� ��������� - ������ �����, ������ �� ���� �������)
	std::vector<vertex> vertices;

	//  ��������� ���������� �����
	void generateGraph(sizet Size) {
		size = Size;
		int k;
		vertices.clear();//������� ������ �� ������� ��������
		vertices.reserve(size);//��������� ������
		//  ����� ��������� ������ ������
		for (sizet i = 0; i < size; ++i)
			vertices.push_back(vertex(i));//���������� ������ ����� ��������� �����

		//  ������� ����, ������� ��� ���������
		std::vector<sizet> marks(size, std::numeric_limits<sizet>::max());
		srand(time(NULL));
		sizet dest;
		weightt w;

		for (sizet vert = 0; vert < size; ++vert) {
			k = rand()%10+1;
			//  �������� ��������� ����
			for (size_t i = 0; i < k; ++i) {
				dest = rand()%size;
				w = rand() % 10+1;

				//  ���� ��� ����� ��� ����� ����� ��� ���������, �� �������
				if (dest == vert || marks[dest] == vert) continue;

				vertices[vert].addEdge(dest, w);
				//  ������, ����� �� vert � dest ��� ����
				marks[dest] = vert;

				//���� ����������������, ������� ������������ ����: �� ����, ������ ����� 
				// ����� �������� ������ � ����� �����������  
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
		std::ofstream out(filename, std::ios_base::out);//���������� ���������� ������� ������ � ����
		out << size << '\n';//���������� ���������� ������
		for (sizet i = 0; i < size; i++)
			if (vertices[i].edgeList.size() > 0){

				// ���������� ����� ������� � ���������� �����, ��������� �� ��
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