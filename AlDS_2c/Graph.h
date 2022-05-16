#include <vector>
#include <iostream>

#pragma once

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

};

