#include <vector>
#include <iostream>
#include <string>

#pragma once

/*
	03.06

	1. Определить среднее число ребер, исходящее из списка смежности
	2. Распечатать в графе все вершины, имеющие петли
	3. Распечатать все "висячие" вершины в графе


*/


class Graph {

	struct Edge { // ребро
		float weight; // вес ребра
		int vertex; // индекс вершины, в которую ведет ребро
		Edge* next; // поле связи
	};

	struct Vertex { // вершина
		std::string caption; // название вершины
		Edge* edges; // список исходящих ребер
	};

	Vertex* verts; // массив вершин
	int size; // количество вершин



	int TEST_TaskOne(const int index) const {
		if (index < 0 && size <= index)
			throw(std::logic_error("index out of range"));
		
		double count = 0;

		for (int i = 0; i < size; i++) {
			Edge* current = verts[i].edges;
			while (current) {
				if (current->vertex == index) {
					count += current->weight;
				}
				current = current->next;

			}
		}

		return count ;
	}

	void TEST_TaskTwo(const int v1, const int v2) const {

		if (size == 0) 
			throw "no elemenets";
		Edge* tmp = verts[v1].edges;
		while (tmp) {
			if (tmp->vertex == v2) {
				std::cout << tmp->weight << "\n";
				tmp = tmp->next;
			}
			
		}

		tmp = verts[v2].edges;
		while (tmp) {
			if (tmp->vertex == v1) {
				std::cout << tmp->weight << "\n";
				tmp = tmp->next;
			}

		}
	}

	double TEST_TaskThree() const {

		if (size == 0)
			return 0;

		size_t count = 0;

		for (auto i = 0; i < count; i++) {
			Edge* tmp = verts[i].edges;
			while (tmp != NULL) {
				count++;
				tmp = tmp->next;
			}
		}
		return (double)count / size;
	}

	int TEST_TaskFour() const {
		if (size == 0)
			return -1;

		int count = 0;
		for (auto i = 0; i < size; i++) {
			Edge* tmp = verts[i].edges;
			bool flag = true;
			while (tmp != NULL) {
				if (tmp->weight < 0) {
					flag = false;
					tmp = tmp->next;
				}
			}

			if (flag)
				count++;
		}

		return count;
	}

	void TEST_TaskFive() const {

		if (size < 0)
			return;
		int min = INT_MAX;

		for (auto i = 0; i < size; i++) {
			int currentMin = 0;
			Edge* current = verts[i].edges;

			while (current) {
				currentMin++;
				current = current->next;
			}

			if (currentMin < min) {
				min = currentMin;
			}
		}

	}

	void TEST_TaskSix(const int index) const {

		if (size < 0)
			return;
		for (auto i = 0; i < size; i++) {

			Edge* current = verts[i].edges;

			while (current) {
				if (current->vertex == index)
					std::cout << current->weight << "\n";
				current = current->next;
			}

		}

	}

	void TEST_TaskSeven() const {
		if (size == 0)
			return;

		for (auto i = 0; i < size; i++) {
			Edge* tmp = verts[i].edges;
			while (tmp != NULL) {
				if (tmp->weight < 0) {
					std::cout << tmp->vertex;
					break;
				}
			}

		}

	}

	int TEST_TaskEight(const int index) const {
		if (size == 0)
			return -1;
		int average = 0;
		int size = 0;
		Edge* tmp = verts[index].edges;
		while (tmp != NULL) {
			average += tmp->weight;
			size++;
		}
		return (double)average / size;

	}

	int TEST_TaskNine(const int index) const {
		if (index < 0 && size <= index)
			throw(std::logic_error("index out of range"));

		Edge* current = verts[index].edges;
		int count = 0;
		while (current) {
			count += current->weight;
			current = current->next;
		}
		return count;
	}



	void PrintTask2() const {
		for (auto i = 0; i < size; i++) {
			Edge* tmp = verts[i].edges;
			while (tmp != NULL) {
				if (i == tmp->vertex) {
					std::cout << i << "\n";
				}
			}
		}
	}

	void PrintTask3() const {
		std::vector<int> res(size, 0);

		for (auto i = 0; i < size; i++) {
			Edge* tmp = verts[i].edges;
			while (tmp != NULL) {
				res[tmp->vertex]++;
				tmp = tmp->next;
			}
		}

		for (auto i = 0; i < res.size(); i++) {
			if (res[i] == 1 && verts[i].edges == NULL)
				std::cout << verts[i].caption;
		}
	}








};


/*
struct Data {
	int FirstIdVertex;
	int SecondIdVertex;

	int _weight;

	Data() : _weight(0), FirstIdVertex(0), SecondIdVertex(0) {};
	Data(int weight, int firstIdVertex, int secondIdVertex) : _weight(weight), FirstIdVertex(firstIdVertex),
																			SecondIdVertex(secondIdVertex) {};
};
class Edge {
private:
	Data _data;

public:

	Edge() {
		_data._weight = 0;
		_data.FirstIdVertex = 0;
		_data.SecondIdVertex = 0;
	}
	Edge(const int vFirst, const int vSecond) {
		_data.FirstIdVertex = vFirst;
		_data.SecondIdVertex = vSecond;
		_data._weight = 0;
	}
	Edge(const Data& data) {
		_data.FirstIdVertex = data.FirstIdVertex;
		_data.SecondIdVertex = data.SecondIdVertex;
		_data._weight = data._weight;
	}

	int Weight() { return _data._weight; }
	bool ChangeWeight(const int newWeight) {
		_data._weight = newWeight;
		return true;
	}

	Data GetData() const { return _data; }

	int GetFirstVertexId() const { return _data.FirstIdVertex; }
	int GetSecondVertexId() const { return _data.SecondIdVertex; }

	bool operator==(const Edge& rhs) const {
		return true;
	}

	//int GetWeightById() const { return _data._weight; }

};
class Vertex {
private:
	std::vector<Edge> _arrayEdge;
	size_t _id;
	size_t _size;			// КОЛИЧЕСТВО ИСХОДЯЩИХ РЕБЕР

public:
	Vertex() {
		_id = 0;
		_size = 0;
	}
	Vertex(const size_t id) {
		_id = id;
		_size = 0;
	}

	size_t GetId() const { return _id; }		// получение id вершины
	size_t EdgeCount() const { return _size; }	// размер получаем
	Edge GetEdgeById(const size_t id) { return _arrayEdge[id]; }
	const std::vector<Edge>& GetEdge() const { return _arrayEdge; }

	bool AddEdge(const Vertex& secondVertex) {
		auto newEdge = Edge(_id, secondVertex._id);
		_arrayEdge.push_back(newEdge);
		_size++;
		return true;
	}
	bool AddEdge(const Data& data) {
		auto newEdge =  Edge(data);
		_arrayEdge.push_back(newEdge);
		_size++;
		return true;
	}

	bool DeleteEdge(const Edge& deletedEdge) {
		auto iterDeleted = std::find(_arrayEdge.begin(), _arrayEdge.end(), deletedEdge);
		_arrayEdge.erase(iterDeleted, iterDeleted.operator++());
	}

	bool operator==(const Vertex& rhs) const {

		if (_size != rhs._size)
			return false;

		for (size_t i = 0; i < _size; i++) {
			// TO DO
		}

		return true;
	}

};
class Graph {
private:
	std::vector<Vertex> _arrayVertex;
	size_t _size;			// всегда менять размер СРАЗУ
							// оставлять size константным, т.е. возможность его задания в самом начале ?
	int** _matr;

public:
	Graph() {
		_size = 0;
		_matr = nullptr;
	}

	Graph(const int size) {
		//_arrayVertex.resize(size);
		_size = size;
		_matr = nullptr;
	}

	size_t CountVertex() const {
		return _size;
	}
	size_t CountEdge() const {
		size_t size = 0;
		for (int i = 0; i < _size; i++) {
			size += _arrayVertex[i].EdgeCount();
		}
	}
	size_t FindMax() const {			// зачем это я так и не поняла
		size_t max = -1;
		size_t id = 0;

		for (size_t i = 0; i < _size; i++) {
			if (_arrayVertex[i].EdgeCount() > max) {
				max = _arrayVertex[i].EdgeCount();
				id = i;
			}
		}

		return id;
	}
	size_t FindById(const int id) const {
		for (size_t i = 0; i < _size; i++) {
			if (_arrayVertex[i].GetId() == id)
				return i;
		}
		return -1;
		// or 
		//throw(std::logic_error("Not found"));
	}

	bool FillImagineMatrix() {
		_matr = new int* [_size];
		for (int i = 0; i < _size; i++)
			_matr[i] = new int[_size];

		for (int i = 0; i < _size; i++) {
			for (int j = 0; j < _size; j++) {
				_matr[i][j] = 0;

			}
		}

		for (size_t i = 0; i < _size; i++) {
			for (size_t j = 0; j < _arrayVertex[i].EdgeCount(); j++) {
				auto edge = _arrayVertex[i].GetEdgeById(j);

				int elemOne = edge.GetFirstVertexId();
				int elemTwo = edge.GetSecondVertexId();
				int weight = edge.Weight();
				_matr[elemOne][elemTwo] = weight;
			}
		}

		return true;
	}

	bool ImagineMatrix() const {
		for (int i = 0; i < _size; i++) {
			for (int j = 0; j < _size; j++) {
				std::cout << _matr[i][j] << "	";
			}
			std::cout << "\n";
		}

		return true;
	}

	bool AddVertex(const Vertex& newVertex) {
		_arrayVertex.push_back(newVertex);
		return true;
	}

	bool AddEdge(const Edge& newEdge) {		// мне кажется костыльно ................
		// проверить существуют ли ребра и хранит ли это ребро какую либо инф-цию
		_arrayVertex[FindById(newEdge.GetFirstVertexId())].AddEdge(newEdge.GetData());

		return true;
	}

	bool SearchWay(const int from, const int where) const {

		if (from == where)
			return true;

		auto id = FindById(from);
		auto edgeList = _arrayVertex[id].GetEdge();

		for (size_t i = 0; i < edgeList.size(); i++) {
			return SearchWay(edgeList[i].GetSecondVertexId(), where);
		}

		return false;
	}

};

*/
/*9
		if (from.GetId() == where.GetId())
			return true;

		size_t id = FindById(from.GetId());

		for (size_t i = 0; i < _arrayVertex[id].EdgeCount(); i++) {

			auto vertex = _arrayVertex[id].GetEdge()[i];

			SearchWay(, where);  //from.GetEdge()[i].GetSecondVertexId()
		}
*/