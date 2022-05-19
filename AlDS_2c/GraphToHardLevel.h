#include <iostream>
#include <vector>
#include <queue>
#include <string>


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

public:
	City() : _cityName("defaultName"), _countOfPeople(0) {};
	City(std::string cityName, unsigned int countPeople) : _cityName(cityName), _countOfPeople(countPeople) {};
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
	The minimum information on the task is the name of the city and the count of people
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
	Road(double weight, double pricaRoad, RoadType roadType, std::string nameRoad = "Samara") : _weight(weight),
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


template<>
struct std::equal_to<City>
{
	size_t operator()(const City& lhs, const City& rhs) const
	{
		return ((lhs.GetCityName() == rhs.GetCityName()) && rhs.GetCountPeople() == rhs.GetCountPeople());
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

