#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <queue>
#include <string>
#include <stack>

// TO DO SPLIT INTO 4 FILES

#pragma once

/*
	summary
	This class stores information about the way: vertices (source, destination) and the path.
	methods: gets/sets, =, >>, <<, ==, !=
	/summary
*/

template <class TVertex, class TEdge, class TEqual = std::equal_to<TVertex>>
class Path {
	TVertex _source;
	TVertex _destination;
	TEdge _edge;

public:
	Path() = default;
	Path(const TVertex from, const TVertex whereVertex, const TEdge edge) : _source(from),
		_destination(whereVertex), _edge(edge) {}

	TVertex GetSource() const { return _source; }
	TVertex GetDestination() const { return _destination; }
	TEdge GetEdge() const { return _edge; }

	void SetSource(TVertex from) { _source = from; }
	void SetDestination(TVertex whereVertex) { _destination = whereVertex; }
	void SetEdge(TEdge edge) { _edge = edge; }


	bool operator==(const Path& rhs) const {
		TEqual equal;
		return equal(_source, rhs._source) && equal(_destination, rhs._destination);
	}
	bool operator!=(const Path& rhs) const {
		return !(this == rhs);
	}

};

template <class TVertex, class TEdge, class TEqual>
std::istream& operator>> (std::istream& in, Path<TVertex, TEdge, TEqual>& rhs) {
	TVertex a, b;
	TEdge e;

	std::cout << "First vertex: ";
	in >> a;
	std::cout << "Second vertex: ";
	in >> b;
	std::cout << "Edge: ";
	in >> e;

	rhs.SetSource(a);
	rhs.SetDestination(b);
	rhs.SetEdge(e);

	return in;
}
template <class TVertex, class TEdge, class TEqual>
std::ostream& operator<< (std::ostream& out, const Path<TVertex, TEdge, TEqual>& rhs) {
	std::cout << "First vertex: ";
	out << rhs.GetSource();
	std::cout << "\nSecond vertex: ";
	out << rhs.GetDestination();
	std::cout << "\nEdge: ";
	out << rhs.GetEdge();
	return out;
}

template <class TVertex, class TEdge, class TEqual = std::equal_to<TVertex>>
std::vector<Path<TVertex, TEdge, TEqual>> ReadFromFileWays(const std::string fileName);

/*
	summary
		This is a graph class. Represented as a list of vertices and a list of all ways.
		Also, for simplicity, it is presented in the form of a matrix.

		In fact, I just couldn't write the Bellman-Ford adjacency list algorithm :(

		methods: gets/sets, =, >>, <<, ==, !=, find edge/vertex by id, get vertex by id, add/remove edge/vertex
		algorithms: Bellman-Ford, DSF, BSF
	/summary
*/

struct ResBellman {
	double _weight;
	std::vector<int> _path;

	ResBellman(const double w,const std::vector<int>& path) {
		_weight = w;
		_path = path;
	}
};

template <class TVertex, class TEdge, class TEqual = std::equal_to<TVertex>,
	class TEqualEdge = std::equal_to<TEdge>>
	class Graph {
	private:
		std::vector<TVertex> _vertices;
		std::vector<Path<TVertex, TEdge, TEqual>> _ways;
		size_t _size;

		std::vector<std::vector<double>> _matr;

		TVertex GetVertexById(const int index) const {
			if (index >= _vertices.size())
				throw(std::logic_error(""));
			return _vertices[index];
		}

		void DepthFirstSearch(const TVertex& from, std::vector<int>& used) const {
			auto _matrIndex = GetIdByVertex(from);
			if (used[_matrIndex] == 2)
				return;

			used[_matrIndex] = 2;
			for (auto i = 0; i < _size; i++) {
				if (_matr[_matrIndex][i] != 0) {
					if (used[i] != 2)
						used[i] = 1;
					const TVertex a = GetVertexById(i);
					std::cout << "\n" << _matrIndex << "and " << i;
					DepthFirstSearch(a, used);
				}
			}
		}
		int GetIdByVertex(const TVertex& vertex) const {
			TEqual equal;
			for (auto i = 0; i < _size; i++) {
				if (equal(_vertices[i], vertex))
					return i;
			}
			return -1;
		}

		void ClearMatrix() {
			for (auto i = 0; i < _matr.size(); i++) {
				_matr[i].clear();
			}
			_matr.clear();
		}

		bool RemoveWay(const TVertex& vertex) {
			TEqual equal;
			for (auto i = 0; i < _ways.size(); i++) {
				if (equal(vertex, _ways[i].GetSource()) || equal(vertex, _ways[i].GetDestination())) {
					_ways.erase(_ways.begin() + i);
					i--;
				}
			}
			return true;
		}

		/*
			summary
			Fill graph matrix
			/summary
		*/
		template<class WeightSelector = Selector<TEdge>>
		bool FillMatrix() {
			if (!_matr.empty()) ClearMatrix();

			_matr.resize(_size);		// Create zero matrix
			for (auto i = 0; i < _size; i++) {
				_matr[i].resize(_size);
				std::fill(_matr[i].begin(), _matr[i].end(), INFINITY);
				_matr[i][i] = 0;
			}
			for (auto i = 0; i < _ways.size(); i++) {
				WeightSelector convert;
				auto idFirstVertex = GetIdByVertex(_ways[i].GetSource());
				auto idSecondVertex = GetIdByVertex(_ways[i].GetDestination());
				auto a = convert(_ways[i].GetEdge());
				_matr[idFirstVertex][idSecondVertex] = a;
			}

			return true;
		}

		/*
			summary
			Search for pairs of minimum values (weight, index)
			/summary
		*/
		std::pair<double, int> MinimimOfArray(std::vector<double> arr) {
			double min = INFINITY;  
			auto indexMin = -1;
			for (auto i = 0; i < arr.size(); i++) {
				if (min > arr[i]) {
					min = arr[i];
					indexMin = i;
				}
			}
			return std::pair<double, int>(min, indexMin);
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

			return res;
		}

		ResBellman BellmanFord(const int start, const int end) {
			auto verticesCount = _size;

			std::vector<double> resCostWay(verticesCount);
			std::vector<double> labels;
			std::vector<int> previous(verticesCount);

			std::fill(resCostWay.begin(), resCostWay.end(), INFINITY);
			std::fill(previous.begin(), previous.end(), -1);
			previous[start] = 0;

			resCostWay[start] = 0.0;

			for (auto k = 1; k < verticesCount; k++) {
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

			return ResBellman(resCostWay[end], PathRecovery(previous, start, end));
		}

		/*
				std::cout << resCostWay[end] << "\n";
			return PathRecovery(previous, start, end);
		*/

	public:
		Graph() : _size(0) {};

		void ReadFromFile() {
			//std::vector<Path<TVertex, TEdge, TEqual>> b = ReadFromFileWays(std::string("test.txt"));
			//for (int i = 0; i < b.size(); i++) {
			//	AddEdge(b[i]);
			//}
		}

		std::vector<Path<TVertex, TEdge, TEqual>> GetWay() const { return _ways; }
		size_t GetSize() const { return _size; }

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
		bool FindEdge(const Path<TVertex, TEdge, TEqual>& way) const {
			TEqualEdge equal;
			for (auto i = 0; i < _ways.size(); i++) {
				if (equal(way, _ways[i]))
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

		bool AddEdge(const Path<TVertex, TEdge, TEqual>& way) {
			_ways.push_back(way);
			if (!FindVertex(way.GetSource())) {
				_vertices.push_back(way.GetSource());
				_size++;
			}
			if (!FindVertex(way.GetDestination())) {
				_vertices.push_back(way.GetDestination());
				_size++;
			}
			return true;
		}
		bool AddEdge(const TVertex& vertexFirst, const TVertex& vertexSecond) {
			TEqual equal;
			if (equal(vertexFirst, vertexSecond)) return false;
			_ways.push_back(Path<>(vertexFirst, vertexSecond, TEdge()));
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

		bool RemoveVertex(const TVertex& vertex) {
			int id = GetIdByVertex(vertex);
			if (id == -1)
				return false;
			_vertices.erase(_vertices.begin() + id);
			_size--;
			return RemoveWay(vertex);
		}
		bool RemoveEdge(const TEdge& edge) {
			TEqualEdge equal;
			for (auto i = 0; i < _ways.size(); i++) {
				if (equal(_ways[i].GetEdge(), edge) || equal(edge, _ways[i].GetEdge())) {
					_ways.erase(_ways.begin() + i);
					i--;
				}
			}
			return true;
		}


		bool ImagineMatrix() {
			FillMatrix();
			std::cout << std::string(10, ' ') << '|';
			for (auto i = 0; i < _size; i++) {
				std::cout << std::setw(10) << _vertices[i].GetCityName() << "|";
			}
			std::cout << "\n" << std::string((_size + 1) * 11, '-') << "\n";
			for (auto i = 0; i < _size; i++) {
				std::cout << std::setw(10) << _vertices[i].GetCityName() << "|";
				for (auto j = 0; j < _size; j++) {
					std::cout << std::setw(10) << _matr[i][j] << "|";
				}
				std::cout << "\n";
			}
			std::cout << std::string((_size + 1) * 11, '-') << "\n";
			return true;
		}

		/*
			summary
			Algorithms for traversing a graph represented by a matrix (DFS, BSF)
			/summary
		*/
		void DepthFirstSearch(const int from) const {
			FillMatrix();
			std::vector<int> used(_size);
			std::fill(used.begin(), used.end(), 0);

			DepthFirstSearch(GetVertexById(from), used);
		}
		std::vector<std::pair<int, int>> BreadthFirstSearch(const TVertex& from, const int count = INT_MAX) const {
			FillMatrix();
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
			Implementation of the Bellman-Ford algorithm on a matrix
			Input Data:
				start point (by index or TVertex)
				end point (by index or TVertex)
			/summary
		*/
		ResBellman BellmanFord(const TVertex& start, const TVertex& end) {
			FillMatrix();
			return BellmanFord(GetIdByVertex(start), GetIdByVertex(end));
		}

};

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
	size_t _countPeople;

public:
	City() : _cityName("defaultName"), _countPeople(0) {};
	City(const std::string cityName, const size_t countPeople) : _cityName(cityName),
		_countPeople(countPeople) {};
	City(const City& city) {
		_cityName = city._cityName;
		_countPeople = city._countPeople;
	}

	std::string GetCityName() const { return _cityName; }
	size_t GetCountPeople() const { return _countPeople; }

	void SetCityName(const std::string newName) { _cityName = newName; }
	void SetCountOfPeople(const size_t newCount) { _countPeople = newCount; }

	City& operator= (const City& rhs) {
		if (this == &rhs)
			return *this;
		_cityName = rhs._cityName;
		_countPeople = rhs._countPeople;
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
	Road(const double weight, const double priceRoad, const RoadType roadType = asphalt,
							  const std::string nameRoad = "Samara") : _weight(weight),
							  _priceRoad(priceRoad), _roadType(roadType), _nameRoad(nameRoad) {};
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

	if (roadType == 0)
		rhs.SetRoadType(asphalt);
	else if (roadType == 1)
		rhs.SetRoadType(priming);
	else
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
	double asphaltK = 1;
	double primingK = 1;
	double earthK=1;
	double priceK = 1;

	double operator()(const Road& edge) const {
		double w = edge.GetWeight();

		switch (edge.GetRoadType()) {
		case RoadType::asphalt:
			w *= asphaltK;
			break;
		case RoadType::priming:
			w *= primingK;
			break;
		case RoadType::earth:
			w *= earthK;
			break;
		}

		if(edge.GetPricaRoad() != 0)
			w *= priceK * edge.GetPricaRoad();

		return w;
	}
};






bool WriteToFile(const City& city, const std::string fileName) {
	std::ofstream out(fileName, std::ios::app);

	if (out.is_open())
	{
		out << city.GetCityName() << ' ' << city.GetCountPeople() << std::endl;
	}
	out.close();

	return true;
}
City ReadFromFileCity(const std::string fileName) {
	std::string cityName;
	size_t countOfPeople = 0;
	std::ifstream in(fileName); // окрываем файл дл€ чтени€
	if (in.is_open())
	{
		in >> cityName >> countOfPeople;
	}
	in.close();

	return City(cityName, countOfPeople);
}

bool WriteToFile(const std::vector<City> cities, const std::string fileName) {
	std::ofstream out(fileName, std::ios::app);

	if (out.is_open())
	{
		for (auto i = 0; i < cities.size(); i++) {
			out << cities[i].GetCityName() << ' ' << cities[i].GetCountPeople() << std::endl;
		}
	}
	out.close();

	return true;

}
std::vector<City> ReadFromFileCities(const std::string fileName) {
	std::vector<City> res;
	std::string cityName;
	unsigned int countOfPeople;
	std::ifstream in(fileName); // окрываем файл дл€ чтени€
	if (in.is_open())
	{
		while (in >> cityName >> countOfPeople)
		{
			res.push_back(City(cityName, countOfPeople));
		}
	}
	in.close();
	return res;
}

bool WriteToFile(const std::vector<Road> roads, const std::string fileName) {

	std::ofstream out(fileName, std::ios::app);

	if (out.is_open())
	{
		for (auto i = 0; i < roads.size(); i++) {
			out << roads[i].getNameRoad() << ' ' << roads[i].GetPricaRoad() << ' ' << roads[i].GetRoadType() <<
				' ' << roads[i].GetWeight() << std::endl;
		}
	}
	out.close();

	return true;

}
std::vector<Road> ReadFromFileRoads(std::string fileName) {
	std::vector<Road> res;
	double weight;
	double priceRoad;
	int roadType;
	std::string nameRoad;

	std::ifstream in(fileName); // окрываем файл дл€ чтени€
	if (in.is_open())
	{
		while (in >> nameRoad >> priceRoad >> roadType >> weight)
		{
			Road tmp(weight, priceRoad);
			tmp.SetNameRoad(nameRoad);
			if (roadType == 0)
				tmp.SetRoadType(asphalt);
			if (roadType == 1)
				tmp.SetRoadType(priming);
			if (roadType == 2)
				tmp.SetRoadType(earth);
			res.push_back(tmp);
		}
	}
	in.close();
	return res;
}

//template <class TVertex, class TEdge, class TEqual = std::equal_to<TVertex>>
//std::vector<Path<TVertex, TEdge, TEqual>> ReadFromFileWays(const std::string fileName) {
//	std::cout << "NO";
//	return std::vector();
//}

std::vector<Path<City, Road>> ReadFromFileWays(const std::string fileName) {
	std::vector<Path<City, Road>> res;

	std::ifstream in(fileName);
	if (in.is_open())
	{
		std::vector<City> cOne = ReadFromFileCities("test0.txt");
		std::vector<City> cTwo = ReadFromFileCities("test1.txt");
		std::vector<Road> road = ReadFromFileRoads("test2.txt");
		for (auto i = 0; i < road.size(); i++) {

			res.push_back(Path<City, Road>(cOne[i], cTwo[i], road[i]));
		}
	}
	in.close();
	return res;
}


//bool WriteToFile(const std::vector<Path<City, Road>> ways, const std::string fileName) {
//
//	std::ofstream out(fileName);
//
//	if (out.is_open())
//	{
//		std::vector<City> cOne;
//		std::vector<City> cTwo;
//		std::vector<Road> road;
//
//		for (auto i = 0; i < ways.size(); i++) {
//			cOne.push_back(ways[i].GetSource());
//			cTwo.push_back(ways[i].GetDestination());
//			road.push_back(ways[i].GetEdge());
//		}
//		WriteToFile(cOne, "test0.txt");
//		WriteToFile(cTwo, "test1.txt");
//		WriteToFile(road, "test2.txt");
//	}
//	out.close();
//
//	return true;
//
//}
//std::vector<Path<City, Road>> ReadFromFileWays(const std::string fileName) {
//	std::vector<Path<City, Road>> res;
//
//	std::ifstream in(fileName); 
//	if (in.is_open())
//	{
//		std::vector<City> cOne = ReadFromFileCities("test0.txt");
//		std::vector<City> cTwo = ReadFromFileCities("test1.txt");
//		std::vector<Road> road = ReadFromFileRoads("test2.txt");
//		for (auto i = 0; i < road.size(); i++) {
//
//			res.push_back(Path<City, Road>(cOne[i], cTwo[i], road[i]));
//		}
//	}
//	in.close();
//	return res;
//}
//
//
//


//template<typename TWeightSelector>
//void Method(Е, TWeightSelector weightSelector) {
//	TEdge edge = Е;
//	double weight = weightSelector(edge);
//	Е
//}


/*
	void DepthFirstSearch(const int from, const int _where) const {
		std::vector<int> used(_size);
		std::fill(used.begin(), used.end(), 0);
		std::vector<int> res;
		DepthFirstSearch(GetVertexById(from), GetVertexById(_where), used, res);
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
*/

/*
	std::vector<int> GetNeighborVertex(const int index) const {
		std::vector<int> a;
		for (int i = 0; i < _size; i++) {
			if (_matr[index][i] != INFINITY)
				a.push_back(i);
		}
		return a;
	}
*/

//bool operator==(const City& rhs) const {
//	return _cityName == rhs._cityName && _countOfPeople && rhs._countOfPeople;
//}

// TO DO ADD ITERATORS FOR GRAPH

