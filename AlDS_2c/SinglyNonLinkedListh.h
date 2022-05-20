#include <iostream>
/*
Task:
1. Написать функцию проверку того, упорядочен ли список
2. Упорядочивание элементов в списке
3. Рекурсивная функция вставка элемента на нужное место
4. Итеаративная вставка элемента 
*/

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
List<T>* ReverseList(List<T> * head)
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

template<class T>
bool CheckIncrement(List<T>*& head) {
	List<T>* p = head->_nextNode;
	List<T>* prevData = head;
	while (p) {
		if (p->_data < prevData->_data)
			return false;
		p = p->_nextNode;
		prevData = prevData->_nextNode;
	}
	return true;
}

template<class T>
List<T>* Sort(List<T>* root)
{
	List<T>* new_root = NULL;
	while (root != NULL)
	{
		List<T>* node = root;
		root = root->_nextNode;

		if (new_root == NULL || node->_data < new_root->_data)
		{
			node->_nextNode = new_root;
			new_root = node;
		}
		else
		{
			List<T>* current = new_root;
			while (current->_nextNode != NULL && !(node->_data < current->_nextNode->_data))
			{
				current = current->_nextNode;
			}
			node->_nextNode = current->_nextNode;
			current->_nextNode = node;
		}
	}

	return new_root;
}

template<class T>
List<T>* SearchById(List<T>* head, int id, int counter = 0) {
	if (!head)
		return head;
	if (counter < id)
		return SearchById(head->_nextNode, id, counter+1);
	return head;
}

template<class T>
List<T>* SearchByFirstElem(List<T>* head, T data) {
	if (!head)
		return NULL;

	if (head->_data == data)
		return head;

	return SearchById(head->_nextNode, data);
}

template<class T>
List<T>* InsertById(List<T>*& head, T data, int id, int counter = 0) {
	List<T>* elem = SearchById(head, id);
	if (!elem)
		return NULL;
	List<T>* next = elem->_nextNode;
	List<T>* newElem = new List<T>(data);
	elem->_nextNode = newElem;
	newElem->_nextNode = next;
	return head;
}

template<class T>
List<T>* InsertByIdNORec(List<T>*& head, T data, int id) {
	if (!head)
		return head;
	if (Size(head) < id)
		return NULL;
	List<T>* p = head;

	for (int i = 0;  i < id; i++) {
		p = p->_nextNode;
	}
	List<T>* next = p->_nextNode;
	List<T>* newElem = new List<T>(data);
	p->_nextNode = newElem;
	newElem->_nextNode = next;
	return head;
}

template<class T>
List<T>* InsertByIdNORec(List<T>*& head, List<T>*& data) {
	if (!head)
		return head;

	List<T>* p = head;
	while(p && p->_data != data->_data) {
		p = p->_nextNode;
	}

	List<T>* next = p->_nextNode;
	p->_nextNode = data;
	data->_nextNode = next;
	return head;
}
