#pragma once
#include <iostream>

template<typename T>
class Edge;

template<typename T>
class Node {
public:
	using ValueType = T;
	using NodePtr = Node<T>*;
	using EdgePtr = Edge<T>*;
public:
	Node(T key) : _next(nullptr), _prev(nullptr), _tail(nullptr), _key(key), _count(0) { }

	~Node() {
		if (_tail != nullptr)
			_tail->DeleteAll();
	}

	void AddNext(Node* next) {
		_next = next;
	}

	void AddPrev(Node* prev) {
		_prev = prev;
	}

	Node*& GetNext() {
		return _next;
	}

	Node*& GetPrev() {
		return _prev;
	}

	T GetKey() {
		return _key;
	}

	void IncreaseCount() {
		_count++;
	}

	void DecreaseCount() {
		_count--;
	}

	size_t GetCount() {
		return _count;
	}

	void AddEdge(Node* newNode) {
		if (_tail != nullptr)
			_tail->AddNode(newNode);
		else {
			_tail = new Edge<T>(newNode);
		}
	}

	void RemoveEdge(Node* secondNode) {
		if (_tail != nullptr) {
			if (_tail->GetId() == secondNode) {
				Edge<T>* next = _tail->GetNext();
				delete _tail;
				_tail = next;
				return;
			}
			if (_tail->GetNext() != nullptr)
				_tail->RemoveNode(secondNode);
			else {
				delete _tail;
				_tail = nullptr;
			}
		}
	}

	EdgePtr GetTail() {
		return _tail;
	}

	void RemoveNode() {
		_next->_prev = _prev;
		_prev->_next = _next;
	}

	void Print() {
		std::cout << GetKey() << ": ";
		EdgePtr iter = _tail;
		while (iter != nullptr) {
			iter->Print();
			iter = iter->GetNext();
		}
	}

private:
	NodePtr _next;
	NodePtr _prev;
	EdgePtr _tail;
	T _key;
	size_t _count;
};
