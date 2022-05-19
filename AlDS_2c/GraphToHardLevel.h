#include <iostream>
#include <vector>
#include <queue>
#include <string>

//TO DO: ADD ITERATORS FOR GRAPH

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
	Road(const double weight, const double pricaRoad, const RoadType roadType, 
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
		return _roadType * 10 + _priceRoad * 10 + _weight * 100;
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


/*
	summary

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
		if (!FindVertex(way.GetFirstVertex()))
			_vertices.push_back(way.GetFirstVertex());
		if (!FindVertex(way.GetSecondVertex()))
			_vertices.push_back(way.GetSecondVertex());
		return true;
	}
	bool AddEdge(const TVertex& vertexFirst, const TVertex& vertexSecond) {
		TEqual equal;
		if (equal(vertexFirst, vertexSecond)) return false;
		_way.push_back(Way<>(vertexFirst, vertexSecond, TEdge()));
		if (!FindVertex(vertexFirst))
			_vertices.push_back(vertexFirst);
		if (!FindVertex(vertexSecond))
			_vertices.push_back(vertexSecond);
		return true;
	}

	//bool RemoveVertex(const TVertex& vertex) {
	//	if (FindVertex(vertex))
	//		return false;
	//	
	//}

	//template<typename Selector>
	//double Method(TEdge edge, Selector weightSelector) {
	//	TEdge edge = …;
	//	double weight = weightSelector(edge);
	//	
	//}

	int GetIdByVertex(const TVertex& vertex) const {
		TEqual equal;
		for (auto i = 0; i < _size; i++) {
			if (equal(_vertices[i], vertex))
				return i;
		}

		return -1;
	}

	template<class Selector>
	bool FillMatrix() {
		_matr.resize(_size);		// Create zero matrix
		for (int i = 0; i < _size; i++) {
			_matr[i].resize(_size);
			std::fill(_matr[i].begin(), _matr[i].end(), 0);
		}

		//double a = Selector(_way[0][0]);

		for (auto i = 0; i < _way.size(); i++) {
			int idFirstVertex = GetIdByVertex(_way[i].GetFirstVertex());
			int idSecondVertex = GetIdByVertex(_way[i].GetSecondVertex());
			_matr[idFirstVertex][idSecondVertex] = Selector(_way[i].GetEdge());
		}

		return true;
	}

	bool ImagineMatrix() const {
		for (auto i = 0; i < _size; i++) {
			for (auto j = 0; j < _size; j++) {
				std::cout << _matr[i][j] << "	";
			}
			std::cout << "\n";
		}
	}


};


template<typename TEdge>
struct Selector {
	double operator()(const TEdge& edge) {
		return static_cast<double>(edge);
	}
};
template<>
struct Selector<Road> {
	double operator()(const Road& edge) {
		return edge.GetCost();
	}

};



//template<typename TWeightSelector>
//void Method(…, TWeightSelector weightSelector) {
//	TEdge edge = …;
//	double weight = weightSelector(edge);
//	…
//}


