#include <vector>
#include <iostream>

#pragma once

struct Data {
	int FirstIdVertex;
	int SecondIdVertex;

	int _weight;

	Data() : _weight(0) {};
	Data(int weight, int fare) : _weight(weight) {};
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

	//int GetWeightById() const { return _data._weight; }

};

class Vertex {
private:
	std::vector<Edge> _arrayEdge;
	int _id;
	int _size;			// КОЛИЧЕСТВО ИСХОДЯЩИХ РЕБЕР

public:
	Vertex() {
		_id = 0;
		_size = 0;
	}

	int GetId() const { return _id; }		// получение id вершины
	size_t EdgeCount() const { return _size; }	// размер получаем
	Edge GetEdgeById(const int id) { return _arrayEdge[id]; }

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

	const bool operator==(const Vertex& rhs) const {
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
	}

	Graph(const int size) {
		_arrayVertex.resize(size);
		_size = size;
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
	int FindMax() const {			// зачем это я так и не поняла
		int max = -1;
		int id = 0;

		for (int i = 0; i < _size; i++) {
			if (_arrayVertex[i].EdgeCount() > max) {
				max = _arrayVertex[i].EdgeCount();
				id = i;
			}
		}

		return id;
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

		for (int i = 0; i < _size; i++) {
			for (int j = 0; j < _arrayVertex[i].EdgeCount(); i++) {
				auto edge = _arrayVertex[i].GetEdgeById(i);
				_matr[edge.GetFirstVertexId()][edge.GetSecondVertexId()] = edge.Weight();
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

		auto iterFirstVertx = std::find(_arrayVertex.begin(), _arrayVertex.end(), newEdge.GetFirstVertexId());
		if (iterFirstVertx == _arrayVertex.end())
			throw(std::logic_error("Not found First Vertex"));

		int index = std::distance(_arrayVertex.begin(), iterFirstVertx);
		_arrayVertex[index].AddEdge(newEdge.GetData());
		
	}


};

