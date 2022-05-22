#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <stack>

// TO DO: ADD ITERATORS FOR GRAPH

// TO DO BELLAN-FORD AND REMOVE EDGE/VERTEX

#pragma once

/*
	summary
	This class is an example of a graph vertex
	The minimum information on the task is the name of the city and the count of people
	methods: gets/sets, =, >>, << 
	/summary
*/

class City {
private:
	std::string _cityName;
	unsigned int _countOfPeople;
	std::vector<int> _roads;

public:
	City() : _cityName("defaultName"), _countOfPeople(0) {};
	City(const std::string cityName, const  int countPeople) : _cityName(cityName),
															   _countOfPeople(countPeople) {};
	City(const City& city) {
		_cityName = city._cityName;
		_countOfPeople = city._countOfPeople;
	}

	std::string GetCityName() const { return _cityName; }
	unsigned int GetCountPeople() const { return _countOfPeople; }

	void SetCityName(const std::string newName) { _cityName = newName; }
	void SetCountOfPeople(const unsigned int newCount) { _countOfPeople = newCount; }

	//bool operator==(const City& rhs) const {
	//	return _cityName == rhs._cityName && _countOfPeople && rhs._countOfPeople;
	//}

	City& operator= (const City& rhs) {
		if (this == &rhs)
			return *this;
		_cityName = rhs._cityName;
		_countOfPeople = rhs._countOfPeople;
		return *this;
	}

};

std::istream& operator>> (std::istream& in, City& rhs) {
	std::string newName;
	unsigned int newPeople;
	std::cout << "\nInput city name: ";
	in >> newName;
	std::cout << "Input count of people: ";
	in >> newPeople;
	rhs.SetCityName(newName);
	rhs.SetCountOfPeople(newPeople);
	return in;
}
std::ostream& operator<< (std::ostream& out, const City& rhs) {
	out << "City name: " << rhs.GetCityName() << "\n";
	out << "Count of people: " << rhs.GetCountPeople();
	return out;
}

/*
	summary
	This class is an example of a graph edge
	The minimum information on the task is the status road
	methods: gets/sets, =, >>, <<
	/summary
*/

enum RoadType {
	asphalt,
	priming,
	earth,
};

class Road {
private:
	double _weight;
	double _priceRoad;
	RoadType _roadType;
	std::string _nameRoad;

public:
	Road() : _weight(0), _priceRoad(0), _roadType(asphalt), _nameRoad("Samara") {};
	Road(const double weight, const double pricaRoad, const RoadType roadType = asphalt,
							  const std::string nameRoad = "Samara") : _weight(weight),
							  _priceRoad(pricaRoad), _roadType(roadType), _nameRoad(nameRoad) {};
	Road(const Road& rhs) {
		_weight = rhs._weight;
		_priceRoad = rhs._priceRoad;
		_roadType = rhs._roadType;
		_nameRoad = rhs._nameRoad;
	}

	double GetWeight() const { return _weight; }
	double GetPricaRoad() const { return _priceRoad; }
	RoadType GetRoadType() const { return _roadType; }
	std::string getNameRoad() const { return _nameRoad; }

	void SetWeight(const double weight) { _weight = weight; }
	void SetPriceRoad(const double priceRoad) { _priceRoad = priceRoad; }
	void SetRoadType(const RoadType roadType) { _roadType = roadType; }
	void SetNameRoad(const std::string nameRoad) { _nameRoad = nameRoad; }

	double GetCost() const {
		return _roadType * 0 + _priceRoad * 0 + _weight * 1;
	}

	Road& operator=(const Road& rhs) {
		if (this == &rhs)
			return *this;
		_weight = rhs._weight;
		_priceRoad = rhs._priceRoad;
		_nameRoad = rhs._nameRoad;
		_roadType = rhs._roadType;
		return *this;
	}
};

std::istream& operator>> (std::istream& in, Road& rhs) {
	std::string newName;
	double weight, priceRoad;
	int roadType;
	std::cout << "Input road name: ";
	in >> newName;
	std::cout << "Input weight: ";
	in >> weight;
	std::cout << "Input price road: ";
	in >> priceRoad;
	std::cout << "Input road type: 1 - asphalt, 2 - priming, 3 - earth: ";
	in >> roadType;
	rhs.SetNameRoad(newName);
	rhs.SetPriceRoad(priceRoad);
	rhs.SetWeight(weight);

	if (roadType == 1)
		rhs.SetRoadType(asphalt);
	if (roadType == 2)
		rhs.SetRoadType(priming);
	if (roadType == 3)
		rhs.SetRoadType(earth);

	return in;
}
std::ostream& operator<< (std::ostream& out, const Road& rhs) {
	out << "Road name: " << rhs.getNameRoad() << "\n";
	out << "Road price " << rhs.GetPricaRoad() << "\n";
	out << "Road type: " << rhs.GetRoadType() << "\n";
	out << "Road weight: " << rhs.GetWeight();

	return out;
}


/*
	summary
	This class stores information about the way: vertices (source, destination) and the path.
	methods: gets/sets, =, >>, <<, ==, !=
	/summary
*/

template <class TVertex = City, class TEdge = Road, class TEqual = std::equal_to<TVertex>>
class Way {
	TVertex _from;
	TVertex _where;
	TEdge _edge;

public:
	Way() : _from(TVertex()), _where(TVertex()), _edge(TEdge()) {};
	Way(const TVertex from, const TVertex whereVertex, const TEdge edge) : _from(from), 
														_where(whereVertex), _edge(edge) {};

	TVertex GetFirstVertex() const { return _from; }
	TVertex GetSecondVertex() const { return _where; }
	TEdge GetEdge() const { return _edge; }

	void SetFirstVertex(TVertex from) { _from = from; }
	void SetSecondVertex(TVertex whereVertex) { _where = whereVertex; }
	void SetEdge(TEdge edge) { _edge = edge; }

	Way& operator=(const Way& rhs) {
		if (this == &rhs)
			return *this;
		_from = rhs._from;
		_where = rhs._where;
		_edge = rhs._edge;
		return *this;
	}

	bool operator==(const Way& rhs) const {
		TEqual equal;
		return equal(_from, rhs._from) && equal(_where, rhs._where);
	}
	bool operator!=(const Way& rhs) const {
		return !(this == rhs);
	}

};

template <class TVertex = City, class TEdge = Road, class TEqual = std::equal_to<TVertex>>
std::istream& operator>> (std::istream& in, Way<TVertex, TEdge, TEqual>& rhs) {
	TVertex a, b;
	TEdge e;

	std::cout << "First vertex: ";
	in >> a;
	std::cout << "Second vertex: ";
	in >> b;
	std::cout << "Edge: ";
	in >> e;

	rhs.SetFirstVertex(a);
	rhs.SetSecondVertex(b);
	rhs.SetEdge(e);

	return in;
}
template <class TVertex = City, class TEdge = Road, class TEqual = std::equal_to<TVertex>>
std::ostream& operator<< (std::ostream& out, const Way<TVertex, TEdge, TEqual>& rhs) {
	std::cout << "First vertex: ";
	out << rhs.GetFirstVertex();
	std::cout << "\nSecond vertex: ";
	out << rhs.GetSecondVertex();
	std::cout << "\nEdge: ";
	out << rhs.GetEdge();
	return out;
}


template<>
struct std::equal_to<City>
{
	size_t operator()(const City& lhs, const City& rhs) const
	{
		return lhs.GetCityName() == rhs.GetCityName() && rhs.GetCountPeople() == rhs.GetCountPeople();
	}
};
template<>
struct std::equal_to<Road>
{
	size_t operator()(const Road& lhs, const Road& rhs) const
	{
		return lhs.GetPricaRoad() == rhs.GetPricaRoad() && lhs.GetRoadType() == lhs.GetRoadType() &&
			lhs.GetWeight() == rhs.GetWeight();
	}
};

template<typename TEdge>
struct Selector {
	double operator()(const TEdge& edge) const {
		return static_cast<double>(edge);
	}
};
template<>
struct Selector<Road> {
	double operator()(const Road& edge) const {
		return edge.GetCost();
	}

};


/*
	summary
		This is a graph class. Represented as a list of vertices and a list of all ways. 
		Also, for simplicity, it is presented in the form of a matrix.

		In fact, I just couldn't write the Bellman-Ford adjacency list algorithm :(

		methods: gets/sets, =, >>, <<, ==, !=, find edge/vertex by id, get vertex by id, add/remove edge/vertex
		algorithms: Bellman-Ford, DSF, BSF
	/summary
*/

template <class TVertex = City, class TEdge = Road, class TEqual = std::equal_to<TVertex>, 
													class TEqualEdge = std::equal_to<TEdge>>
class Graph {
private:
	std::vector<TVertex> _vertices;
	std::vector<Way<TVertex, TEdge>> _way;
	size_t _size;

	std::vector<std::vector<double>> _matr;

public:
	Graph(): _size(0) {};
	Graph(const std::vector<Way<TVertex, TEdge>> ways, const std::vector<TVertex> vertices, 
		  const size_t size) : _way(ways), _size(size), _vertices(vertices) {};

	Graph(const Graph& rhs) {
		_way = rhs._way;
		_vertices = rhs._vertices;
		_size = rhs._size;
	}

	std::vector<Way<TVertex, TEdge>> GetWay() const { return _way; }
	size_t GetSize() const { return _size; }
	TVertex GetVertexById(const int id) const {
		if (id >= _size)
			throw(std::logic_error(""));
		return _vertices[id];
	}

	bool FindVertex(const TVertex& vertex) const {
		/*
			TO DO		add std::find adding iterators
		*/
		TEqual equal;
		for (auto i = 0; i < _size; i++) {
			if (equal(_vertices[i], vertex))
				return true;
		}
		return false;
	}
	bool FindEdge(const Way<>& way) const {
		TEqualEdge equal;
		for (auto i = 0; i < _way.size(); i++) {
			if (equal(way, _way[i]))
				return true;
		}

		return false;
	}

	bool AddVertex(const TVertex& vertex) {
		if (FindVertex(vertex))
			return false;

		_vertices.push_back(vertex);
		_size++;
		return true;
	}

	bool AddEdge(const Way<>& way) {
		_way.push_back(way);
		if (!FindVertex(way.GetFirstVertex())) {
			_vertices.push_back(way.GetFirstVertex());
			_size++;
		}
		if (!FindVertex(way.GetSecondVertex())) {
			_vertices.push_back(way.GetSecondVertex());
			_size++;
		}
		return true;
	}
	bool AddEdge(const TVertex& vertexFirst, const TVertex& vertexSecond) {
		TEqual equal;
		if (equal(vertexFirst, vertexSecond)) return false;
		_way.push_back(Way<>(vertexFirst, vertexSecond, TEdge()));
		if (!FindVertex(vertexFirst)) {
			_vertices.push_back(vertexFirst);
			_size++;
		}
		if (!FindVertex(vertexSecond)) {
			_vertices.push_back(vertexSecond);
			_size++;
		}
		return true;
	}

	int GetIdByVertex(const TVertex& vertex) const {
		TEqual equal;
		for (auto i = 0; i < _size; i++) {
			if (equal(_vertices[i], vertex))
				return i;
		}

		return -1;
	}

	template<class Selector = Road>
	double GetDoubleSelector(const Road& road) {
		double cost = Selector()(road);
		return cost;
	}

	/*
		summary
		Fill graph matrix
		/summary
	*/
	bool FillMatrix() {
		_matr.resize(_size);		// Create zero matrix
		for (auto i = 0; i < _size; i++) {
			_matr[i].resize(_size);
			std::fill(_matr[i].begin(), _matr[i].end(), INFINITY);
			_matr[i][i] = 0;

		}
		for (auto i = 0; i < _way.size(); i++) {
			auto idFirstVertex = GetIdByVertex(_way[i].GetFirstVertex());
			auto idSecondVertex = GetIdByVertex(_way[i].GetSecondVertex());
			auto a = GetDoubleSelector<Selector<Road>>(_way[i].GetEdge());
			_matr[idFirstVertex][idSecondVertex] = a;
		}

		return true;
	}
	bool ImagineMatrix() const {
		for (auto i = 0; i < _size; i++) {
			std::cout << "	" << _vertices[i].GetCityName() << " ";
		}
		std::cout << "\n";
		for (auto i = 0; i < _size; i++) {
			std::cout << _vertices[i].GetCityName() << " ";
			for (auto j = 0; j < _size; j++) {
				std::cout << _matr[i][j] << "	";
			}
			std::cout << "\n";
		}
		return true;
	}

	std::vector<int> GetNeighborVertex(const int index) const {
		std::vector<int> a;
		for (int i = 0; i < _size; i++) {
			if (_matr[index][i] != INFINITY)
				a.push_back(i);
		}
		return a;
	}

	/*
		summary
		Algorithms for traversing a graph represented by a matrix (DFS, BSF)
		/summary
	*/
	void DepthFirstSearch(const TVertex& from, std::vector<int>& used) const {
		auto _matrIndex = GetIdByVertex(from);
		if (used[_matrIndex] == 2)
			return;

		used[_matrIndex] = 2;		// 2 - обработана

		for (auto i = 0; i < _size; i++) {
			if (_matr[_matrIndex][i] != 0) {	// то есть путь существует
				if (used[i] != 2)
					used[i] = 1;		// 1 - в обработке
				const TVertex a = GetVertexById(i);
				std::cout << "\n" << _matrIndex << "and " << i;
				DepthFirstSearch(a, used);
			}
		}
	}
	std::vector<int> DepthFirstSearch(const TVertex& from, const TVertex& _where, std::vector<int>& used,
		std::vector<int>& res) const {
		TEqual equal;
		if (equal(from, _where))
			return res;
		auto _matrIndex = GetIdByVertex(from);
		if (used[_matrIndex] == 2)
			return res;

		used[_matrIndex] = 2;		// 2 - обработана
		for (auto i = 0; i < _size; i++) {
			if (_matr[_matrIndex][i] != INFINITY) {	// то есть путь существует
				if (used[i] != 2)
					used[i] = 1;		// 1 - в обработке
				const TVertex a = GetVertexById(i);
				res.push_back(_matrIndex);
				std::cout << "\n" << _matrIndex << "and " << i;
				return DepthFirstSearch(a, _where, used, res);
			}
		}
	}
	std::vector<std::pair<int, int>> BreadthFirstSearch(const TVertex& from, const int count = INT_MAX) const {
		std::vector<std::pair<int, int>> res;
		std::vector<bool> used(_size);
		std::fill(used.begin(), used.end(), false);
		std::queue<int> q;
		q.push(GetIdByVertex(from));
		used[GetIdByVertex(from)] = true;
		int currentCount = 1;
		while (!q.empty() && currentCount <= count) {
			auto v = q.front();
			q.pop();
			for (auto i = 0; i < _size; i++) {
				if (currentCount == count)
					return res;
				if (_matr[v][i] != INFINITY && !used[i]) {
					used[i] = true;
					q.push(i);
					std::pair<int, int> a(v, i);
					res.push_back(a);
				}
			}
			currentCount++;
		}
		return res;
	}

	/*
		summary
		Search for pairs of minimum values (weight, index)
		/summary
	*/
	std::pair<double, int> MinimimOfArray(std::vector<double> arr) {
		double min = INFINITY;   // 
		auto idMin = -1;
		for (auto i = 0; i < arr.size(); i++) {
			if (min > arr[i]) {
				min = arr[i];
				idMin = i;
			}
		}
		return std::pair<double, int>(min, idMin);
	}
	/*
		summary
		Path recovery from an array of shortest paths (for Bellman-Ford algorithm)
		Input Data:
			std::vector<int> - array of shortest paths
			start point (by index)
			end point (by index)
		/summary
	*/
	std::vector<int> PathRecovery(std::vector<int> v, int start, int end) {
		std::vector<int> res;
		res.push_back(end);
		auto pred = end;
		while (pred != start) {
			int predId = v[pred];
			res.push_back(predId);
			pred = predId;
		}

		std::reverse(res.begin(), res.end());

		for (auto i = 0; i < res.size(); i++) {
			std::cout << res[i] << " ";
		}

		return res;
	}

	/*
		summary
		Implementation of the Bellman-Ford algorithm on a matrix
		Input Data:
			start point (by index or TVertex)
			end point (by index or TVertex)
		/summary
	*/
	void BellmanFord(const TVertex& start, const TVertex& end) {
		BellmanFord(GetIdByVertex(start), GetIdByVertex(end));
	}
	void BellmanFord(const int start, const int end) {
		auto verticesCount = _size;

		std::vector<double> resCostWay(verticesCount);
		std::vector<double> labels;
		std::vector<int> previous(verticesCount);

		std::fill(resCostWay.begin(), resCostWay.end(), INFINITY);
		std::fill(previous.begin(), previous.end(), -1);
		previous[start] = 0;

		resCostWay[start] = 0.0;

		for (auto k = 0; k <= verticesCount - 1; k++) {
			for (auto i = 0; i < verticesCount; i++) {
				for (auto j = 0; j < verticesCount; j++) {
					labels.push_back(resCostWay[j] + _matr[j][i]);
				}
				auto r = MinimimOfArray(labels);
				if (resCostWay[i] > r.first) {
					resCostWay[i] = r.first;
					previous[i] = r.second;
				}
				labels.clear();
			}
		}

		std::cout << resCostWay[end] << "\n";
		PathRecovery(previous, start, end);
	}
};



//template<typename TWeightSelector>
//void Method(Е, TWeightSelector weightSelector) {
//	TEdge edge = Е;
//	double weight = weightSelector(edge);
//	Е
//}


