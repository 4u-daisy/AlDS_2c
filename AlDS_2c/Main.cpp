#include "Graph.h"
//#include "Sorting.h"

int main() {

	Graph _main(4);

	Vertex one(0);
	Vertex two(1);
	Vertex three(2);
	Vertex four(3);

	_main.AddVertex(one);
	_main.AddVertex(two);
	_main.AddVertex(three);
	_main.AddVertex(four);

	Data dataOne(2, 1, 0);
	Data dataTwo(7, 1, 2);
	Data dataThree(5, 2, 3);
	Data dataFour(4, 2, 1);

	Edge edgeOne(dataOne);
	Edge edgeTwo(dataTwo);
	Edge edgeThree(dataThree);
	Edge edgeFour(dataFour);

	_main.AddEdge(edgeOne);
	_main.AddEdge(edgeTwo);
	_main.AddEdge(edgeThree);
	_main.AddEdge(edgeFour);

	_main.FillImagineMatrix();

	_main.ImagineMatrix();

	_main.SearchWay(1, 3) == true ? std::cout << "\nTrue" : std::cout << "\False";

}