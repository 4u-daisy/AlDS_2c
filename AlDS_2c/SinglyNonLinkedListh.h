#include <iostream>

#pragma once

template <class T>
struct List
{
    T _data;
    List* _nextNode;

	List() {
		_data = 0;
		_nextNode = NULL;
	}
	List(T data) : _data(data), _nextNode(NULL) {};

};

template <class T>
void PushBack(T data, List<T>*& head) {

	List<T>* newList = new List<T>(data);

	if (head == NULL) {
		head = newList;
		return;
	}
	List<T>* p = head;
	while (p->_nextNode) {
		p = p->_nextNode;
	}
	p->_nextNode = newList;

}

template <class T>
void RemoveList(List<T>*& head) {
	while (head) {
		List<T>* p = head;
		head = head->_nextNode;
		delete(p);
	}
}

template <class T>
void Print(List<T>*& head) {
	List<T>* p = head;
	while (p) {
		std::cout << p->_data << "	";
		p = p->_nextNode;
	}
}

template <class T>
size_t Size(List<T>*& head) {
	size_t size = 0;
	List<T>* p = head;
	while (p) {
		size++;
		p = p->_nextNode;
	}
	return size;
}

template<class T>
List<T>* Func(List<T> * head)
{
	if (head == NULL) return NULL;
	List<T>* first = NULL;
	List<T>* last = NULL;
	while (head)
	{
		List<T>* end = head;
		List<T>* prev = NULL;
		while (end->_nextNode)
		{
			prev = end;
			end = end->_nextNode;
		}
		if (!first) first = end;
		else last->_nextNode = end;
		last = end;
		if (prev) prev->_nextNode = NULL;
		else
		{
			last->_nextNode = NULL;
			head = NULL;
		}
	}
	return first;
}