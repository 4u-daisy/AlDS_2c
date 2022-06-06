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



/*
	summary
		This is a graph class. Represented as a list of vertices and a list of all ways.
		Also, for simplicity, it is presented in the form of a matrix.

		In fact, I just couldn't write the Bellman-Ford adjacency list algorithm :(

		methods: gets/sets, =, >>, <<, ==, !=, find edge/vertex by id, get vertex by id, add/remove edge/vertex
		algorithms: Bellman-Ford, DSF, BSF
	/summary
*/

template <class TVertex>
struct ResultSearchPath {
	double _weight;
	std::vector<TVertex> _path;

	ResultSearchPath() {
		_weight = 0;
	}
	ResultSearchPath(const double weight, const std::vector<TVertex> path) {
		_weight = weight;
		_path = path;
	}
};

template <class TVertex, class TEdge, class TEqual = std::equal_to<TVertex>,
	class TEqualEdge = std::equal_to<TEdge>>
	class Graph {
	private:
		std::vector<TVertex> _vertices;
		std::vector<Path<TVertex, TEdge, TEqual>> _ways;


		TVertex GetVertexById(const int index) const {
			if (index >= _vertices.size())
				throw(std::logic_error(""));
			return _vertices[index];
		}
		int GetIndexByVertex(const TVertex& vertex) const {
			TEqual equal;
			for (auto i = 0; i < _vertices.size(); i++) {
				if (equal(_vertices[i], vertex))
					return i;
			}
			return -1;
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
			Path recovery from an array of shortest paths (for Bellman-Ford algorithm)
			Input Data:
				std::vector<int> - array of shortest paths
				start point (by index)
				end point (by index)
			/summary
		*/
		std::vector<TVertex> PathRecovery(std::vector<int> v, int start, int end) const {
			std::vector<int> res;
			res.push_back(end);
			auto pred = end;
			while (pred != start) {
				auto predId = v[pred];
				res.push_back(predId);
				pred = predId;
			}

			std::vector< TVertex> aaaaaa;

			for (int i = res.size() - 1; i >= 0; i--) {
				aaaaaa.push_back(_vertices[res[i]]);
			}

			return aaaaaa;
		}


		/*
				std::cout << resCostWay[end] << "\n";
			return PathRecovery(previous, start, end);
		*/

	public:
		Graph() = default;


		std::vector<Path<TVertex, TEdge, TEqual>> GetWay() const { return _ways; }
		size_t GetSize() const { return _vertices.size(); }

		bool FindVertex(const TVertex& vertex) const {
			/*
				TO DO		add std::find adding iterators
			*/
			TEqual equal;
			for (auto i = 0; i < _vertices.size(); i++) {
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
			return true;
		}

		bool AddEdge(const Path<TVertex, TEdge, TEqual>& way) {
			_ways.push_back(way);
			if (!FindVertex(way.GetSource())) {
				_vertices.push_back(way.GetSource());
			}
			if (!FindVertex(way.GetDestination())) {
				_vertices.push_back(way.GetDestination());
			}
			return true;
		}
		bool AddEdge(const TVertex& vertexFirst, const TVertex& vertexSecond) {
			TEqual equal;
			if (equal(vertexFirst, vertexSecond)) return false;
			_ways.push_back(Path<>(vertexFirst, vertexSecond, TEdge()));
			if (!FindVertex(vertexFirst)) {
				_vertices.push_back(vertexFirst);
			}
			if (!FindVertex(vertexSecond)) {
				_vertices.push_back(vertexSecond);
			}
			return true;
		}

		bool RemoveVertex(const TVertex& vertex) {
			int id = GetIndexByVertex(vertex);
			if (id == -1)
				return false;
			_vertices.erase(_vertices.begin() + id);
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


		/*
			summary
			Algorithms for traversing a graph represented by a matrix (DFS, BSF)
			/summary
		*/

		std::vector<std::pair<TVertex, TVertex>> BreadthFirstSearch(const TVertex& source) const {
			std::vector<std::pair<TVertex, TVertex>> res;

			std::queue<TVertex> q;
			q.push(source);

			std::vector<int> used(_vertices.size());
			std::fill(used.begin(), used.end(), 0);

			while (!q.empty()) {

				TVertex v = q.front();
				used[GetIndexByVertex(v)] = 2;
				q.pop();

				for (auto i = 0; i < _ways.size(); i++) {
					auto indexDestinationVertex = GetIndexByVertex(_ways[i].GetDestination());

					if (_ways[i].GetSource() == v && used[indexDestinationVertex] != 2) {
						res.push_back(std::pair<TVertex, TVertex>(v, _ways[i].GetDestination()));
						if (used[indexDestinationVertex] != 1) {
							used[indexDestinationVertex] = 1;
							q.push(_ways[i].GetDestination());
						}
					}
				}
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
		template<class WeightSelector = Selector<TEdge>>
		ResultSearchPath<TVertex> BellmanFord(const TVertex& source, const TVertex& destination) const {
			if (GetIndexByVertex(destination) == -1)	//если в графе такой вершины вообще нет
				return ResultSearchPath<TVertex>();
			WeightSelector convert;
			std::vector<int> minimalPaths(_vertices.size());
			std::fill(minimalPaths.begin(), minimalPaths.end(), INT_MAX);
			minimalPaths[GetIndexByVertex(source)] = 0;

			std::vector<double> d(_vertices.size());	// d - rename
			std::fill(d.begin(), d.end(), INFINITY); // d[v] = INFINITY;
			d[GetIndexByVertex(source)] = 0;	// d[s] = 0;

			for (auto i = 1; i < _vertices.size(); i++) {
				for (auto j = 0; j < _ways.size(); j++) {
					int tmpSource = GetIndexByVertex(_ways[j].GetSource());
					int tmpDestination = GetIndexByVertex(_ways[j].GetDestination());
					double weight = convert(_ways[j].GetEdge());

					if (d[tmpDestination] > d[tmpSource] + weight) {
						d[tmpDestination] = d[tmpSource] + weight;
						minimalPaths[tmpDestination] = tmpSource;
					}
				}
			}

			if (d[GetIndexByVertex(destination)] == INFINITY)	// если пути не существует
				return ResultSearchPath<TVertex>();

			return ResultSearchPath<TVertex>(d[GetIndexByVertex(destination)], PathRecovery(minimalPaths,
				GetIndexByVertex(source), GetIndexByVertex(destination)));
		}

		template<class WeightSelector = Selector<TEdge>>
		ResultSearchPath<TVertex> Dijkstra(const TVertex& source, const TVertex& destination) const {
			if (GetIndexByVertex(destination) == -1)	
				return ResultSearchPath<TVertex>();

			std::vector<int> minimalPaths(_vertices.size());
			std::fill(minimalPaths.begin(), minimalPaths.end(), INT_MAX);
			minimalPaths[GetIndexByVertex(source)] = 0;

			std::vector<double> d(_vertices.size());
			std::fill(d.begin(), d.end(), INFINITY);

			std::vector<bool> used(_vertices.size());
			std::fill(used.begin(), used.end(), false);
			WeightSelector convert;

			d[GetIndexByVertex(source)] = 0;

			for (int i = 0; i < _vertices.size(); i++) {
				int v = -1;

				for (int j = 0; j < _vertices.size(); j++) {
					if (!used[j] && (v == -1 || d[j] < d[v]))
						v = j;
				}

				if (0 > v && d[v] == INFINITY)
					break;

				used[v] = true;

				for (int e = 0; e < _ways.size(); e++) {
					TEqual equal;
					if (!equal(GetVertexById(v), _ways[e].GetSource())) 
						continue;
					double weight = convert(_ways[e].GetEdge());
					if (d[v] + weight < d[GetIndexByVertex(_ways[e].GetDestination())]) {
						d[GetIndexByVertex(_ways[e].GetDestination())] = d[v] + weight;
						minimalPaths[GetIndexByVertex(_ways[e].GetDestination())] = i;
					}
				}


			}

			if (d[GetIndexByVertex(destination)] == INFINITY)	// если пути не существует
				return ResultSearchPath<TVertex>();

			return ResultSearchPath<TVertex>(d[GetIndexByVertex(destination)], PathRecovery(minimalPaths,
				GetIndexByVertex(source), GetIndexByVertex(destination)));
		}


};


/*
func dijkstra(s):
	for v∈V
		d[v] = ∞
		used[v] = false
	d[s] = 0
	for i∈V
		v = null
		for j∈V                        // найдём вершину с минимальным расстоянием
			if !used[j] and (v == null or d[j] < d[v])
				v = j
		if d[v] == ∞
			break
		used[v] = true
		for e : исходящие из v рёбра     // произведём релаксацию по всем рёбрам, исходящим из v
			if d[v] + e.len < d[e.to]
				d[e.to] = d[v] + e.len
*/

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



//bool operator==(const City& rhs) const {
//	return _cityName == rhs._cityName && _countOfPeople && rhs._countOfPeople;
//}

// TO DO ADD ITERATORS FOR GRAPH

