#pragma once
#include "Node.h"
#include "Edge.h"
#include "VertexAdjIterator.h"
#include "ReverseVertexAdjIterator.h"
#include "ConstVertexAdjIterator.h"
#include "VertexIterator.h"
#include "ReverseVertexIterator.h"
#include "ConstVertexIterator.h"
#include "EdgeIterator.h"
#include "ReverseEdgeIterator.h"
#include "ConstEdgeIterator.h"
#include "EdgeAdjIterator.h"
#include "ReverseEdgeAdjIterator.h"
#include "ConstEdgeAdjIterator.h"

template<typename T>
class Edge;

template<typename T>
class Node;

template<typename T>
class Graph {
public:
	using ValueType = T;
	using NodePtr = Node<T>*;
	using EdgePtr = Edge<T>*;
	using VertexIterator = VertexIterator<Node<T>>;
	using ReverseVertexIterator = ReverseVertexIterator<Node<T>>;
	using ConstVertexIterator = ConstVertexIterator<Node<T>>;
	using EdgeAdjIterator = EdgeAdjIterator<Edge<T>>;
	using ReverseEdgeAdjIterator = ReverseEdgeAdjIterator<Edge<T>>;
	using ConstEdgeAdjIterator = ConstEdgeAdjIterator<Node<T>>;
	using VertexAdjIterator = VertexAdjIterator<Node<T>>;
	using ReverseVertexAdjIterator = ReverseVertexAdjIterator<Node<T>>;
	using ConstVertexAdjIterator = ConstVertexAdjIterator<Node<T>>;
	using EdgeIterator = EdgeIterator<Edge<T>>;
	using ReverseEdgeIterator = ReverseEdgeIterator<Edge<T>>;
	using ConstEdgeIterator = ConstEdgeIterator<Node<T>>;
public:
	Graph() : _head(nullptr), _tail(nullptr) { }

	Graph(const Graph& other) {
		if (other._head == nullptr) {
			_head = nullptr;
			_tail = nullptr;
			return;
		}
		Node<T>* iterationNode = other._head;
		while (iterationNode != nullptr) {
			AddVertex(iterationNode->GetKey());
			iterationNode = iterationNode->GetNext();
		}
		iterationNode = other._head;
		while (iterationNode != nullptr) {
			Edge<T>* iterationEdge = iterationNode->GetTail();
			while (iterationEdge != nullptr) {
				AddEdge(iterationNode->GetKey(), iterationEdge->GetId()->GetKey());
				iterationEdge = iterationEdge->GetNext();
			}
			iterationNode = iterationNode->GetNext();
		}
	}

	void Clear() {
		if (_head != nullptr) {
			Node<T>* iterationNode = _head->GetNext();
			Node<T>* prevNode = _head;
			while (iterationNode != nullptr) {
				delete prevNode;
				prevNode = iterationNode;
				iterationNode = iterationNode->GetNext();
			}
			delete prevNode;
			_head = nullptr;
			_tail = nullptr;
		}
	}

	Graph& operator=(const Graph& other) {
		Clear();
		
		if (other._head == nullptr) {
			_head = nullptr;
			_tail = nullptr;
			return *this;
		}
		Node<T>* iterationNode = other._head;
		while (iterationNode != nullptr) {
			AddVertex(iterationNode->GetKey());
			iterationNode = iterationNode->GetNext();
		}
		iterationNode = other._head;
		while (iterationNode != nullptr) {
			Edge<T>* iterationEdge = iterationNode->GetTail();
			while (iterationEdge != nullptr) {
				AddEdge(iterationNode->GetKey(), iterationEdge->GetId()->GetKey());
				iterationEdge = iterationEdge->GetNext();
			}
			iterationNode = iterationNode->GetNext();
		}
		return *this;
	}

	bool operator==(Graph& other) {
		if (GetEdgeCount() != other.GetEdgeCount() || GetVertexCount() != other.GetVertexCount()) {
			return false;
		}

		Node<T>* iter1 = _head;
		Node<T>* iter2 = other._head;
		while (iter1 != nullptr || iter2 != nullptr) {
			if (iter1->GetKey() != iter2->GetKey())
				return false;
			Edge<T>* edgeIter1 = iter1->GetTail();
			Edge<T>* edgeIter2 = iter2->GetTail();
			while (edgeIter1 != nullptr || edgeIter2 != nullptr) {
				if (edgeIter1->GetId()->GetKey() != edgeIter2->GetId()->GetKey()) {
					return false;
				}
				edgeIter1 = edgeIter1->GetNext();
				edgeIter2 = edgeIter2->GetNext();
			}
			iter1 = iter1->GetNext();
			iter2 = iter2->GetNext();
		}
		return true;
	}

	bool operator!=(Graph& other) {
		return !(*this == other);
	}

	~Graph() {
		if (_head == nullptr)
			return;
		Node<T>* iterationNode = _head->GetNext();
		Node<T>* prevNode = _head;
		while (iterationNode != nullptr) {
			delete prevNode;
			prevNode = iterationNode;
			iterationNode = iterationNode->GetNext();
		}
		delete prevNode;
	}

	bool Empty() {
		return _head == nullptr;
	}

	void AddVertex(T key) {
		Node<T>* newNode = new Node<T>(key);
		if (_head == nullptr) {
			_head = newNode;
			_tail = newNode;
			return;
		}

		_tail->AddNext(newNode);
		newNode->AddPrev(_tail);
		_tail = newNode;
	}

	void AddEdge(T firstKey, T secondKey) {
		Node<T>* firstNode = nullptr;
		Node<T>* secondNode = nullptr;
		if (findVertices(firstKey, secondKey, firstNode, secondNode)) {
			firstNode->AddEdge(secondNode);
			secondNode->IncreaseCount();
		}
	}

	void RemoveVertexPtr(NodePtr node) {
		Node<T>* iterNode = _head;
		while (iterNode != nullptr) {
			iterNode->RemoveEdge(node);
			iterNode = iterNode->GetNext();
		}

		if (node == _head && node == _tail) {
			delete node;
			_head = _tail = nullptr;
			return;
		}

		if (node == _head) {
			_head = _head->GetNext();
			_head->GetPrev() = nullptr;
			delete node;
			return;
		}

		if (node == _tail) {
			_tail = _tail->GetPrev();
			_tail->GetNext() = nullptr;
			delete node;
			return;
		}

		node->RemoveNode();
		delete node;
	}

	void RemoveVertex(T key) {
		Node<T>* node = nullptr;
		if (findVertex(key, node)) {
			Node<T>* iterNode = _head;
			while (iterNode != nullptr) {
				iterNode->RemoveEdge(node);
				iterNode = iterNode->GetNext();
			}
			if (node == _head && node == _tail) {
				delete node;
				_head = _tail = nullptr;
				return;
			}

			if (node == _head) {
				_head = _head->GetNext();
				_head->GetPrev() = nullptr;
				delete node;
				return;
			}

			if (node == _tail) {
				_tail = _tail->GetPrev();
				_tail->GetNext() = nullptr;
				delete node;
				return;
			}

			node->RemoveNode();
			delete node;
		}
	}

	VertexIterator BeginVertex() {
		return VertexIterator(_head, this);
	}

	VertexIterator EndVertex() {
		return VertexIterator(nullptr, this);
	}

	ReverseVertexIterator BeginReverseVertex() {
		return ReverseVertexIterator(_tail, this);
	}

	ReverseVertexIterator EndReverseVertex() {
		return ReverseVertexIterator(nullptr, this);
	}

	ConstVertexIterator BeginConstVertex() {
		return ConstVertexIterator(_head, this);
	}

	ConstVertexIterator EndConstVertex() {
		return ConstVertexIterator(nullptr, this);
	}

	VertexAdjIterator BeginAdjVertex(T firstKey) {
		NodePtr node;
		if (findVertex(firstKey, node))
			return VertexAdjIterator(node->GetTail(), this);
		else
			return VertexAdjIterator(nullptr, this);
	}

	VertexAdjIterator EndAdjVertex() {
		return VertexAdjIterator(nullptr, this);
	}

	ReverseVertexAdjIterator BeginReverseAdjVertex(T firstKey) {
		NodePtr node;
		if (findVertex(firstKey, node))
			return ReverseVertexAdjIterator(node->GetTail(), this);
		else
			return ReverseVertexAdjIterator(nullptr, this);
	}

	ReverseVertexAdjIterator EndReverseAdjVertex() {
		return ReverseVertexAdjIterator(nullptr, this);
	}

	ConstVertexAdjIterator BeginConstAdjVertex(T firstKey) {
		NodePtr node;
		if (findVertex(firstKey, node))
			return ConstVertexAdjIterator(node->GetTail(), this);
		else
			return ConstVertexAdjIterator(nullptr, this);
	}

	ConstVertexAdjIterator EndConstAdjVertex() {
		return ConstVertexAdjIterator(nullptr, this);
	}

	EdgeAdjIterator BeginAdjEdge(T firstKey) {
		NodePtr node;
		if (findVertex(firstKey, node))
			return EdgeAdjIterator(node->GetTail(), node);
		else
			return EdgeAdjIterator(nullptr, node);
	}

	EdgeAdjIterator EndAdjEdge() {
		return EdgeAdjIterator(nullptr, nullptr);
	}

	ReverseEdgeAdjIterator BeginReverseAdjEdge(T firstKey) {
		NodePtr node;
		if (findVertex(firstKey, node))
			return ReverseEdgeAdjIterator(node->GetTail(), node);
		else
			return ReverseEdgeAdjIterator(nullptr, node);
	}

	ReverseEdgeAdjIterator EndReverseAdjEdge() {
		return ReverseEdgeAdjIterator(nullptr, nullptr);
	}

	ConstEdgeAdjIterator BeginConstAdjEdge(T firstKey) {
		NodePtr node;
		if (findVertex(firstKey, node))
			return ConstEdgeAdjIterator(node->GetTail(), node);
		else
			return ConstEdgeAdjIterator(nullptr, node);
	}

	ConstEdgeAdjIterator EndConstAdjEdge() {
		return ConstEdgeAdjIterator(nullptr, nullptr);
	}

	EdgeIterator BeginEdge() {
		return EdgeIterator(_head);
	}

	EdgeIterator EndEdge() {
		return EdgeIterator(nullptr);
	}

	ReverseEdgeIterator BeginReverseEdge() {
		return ReverseEdgeIterator(_tail);
	}

	ReverseEdgeIterator EndReverseEdge() {
		return ReverseEdgeIterator(nullptr);
	}

	ConstEdgeIterator BeginConstEdge() {
		return ConstEdgeIterator(_head);
	}

	ConstEdgeIterator EndConstEdge() {
		return ConstEdgeIterator(nullptr);
	}

	void RemoveEdge(T firstKey, T secondKey) {
		Node<T>* firstNode = nullptr;
		Node<T>* secondNode = nullptr;
		if (findVertices(firstKey, secondKey, firstNode, secondNode)) {
			firstNode->RemoveEdge(secondNode);
			secondNode->DecreaseCount();
		}
	}

	bool isVertexExist(T key) {
		Node<T>* node;
		return findVertex(key, node);
	}

	bool isEdgeExist(T firstKey, T secondKey) {
		Node<T>* firstNode = nullptr;
		Node<T>* secondNode = nullptr;
		if (findVertices(firstKey, secondKey, firstNode, secondNode)) {
			Edge<T>* iterationNode = firstNode->GetTail();
			while (iterationNode != nullptr) {
				if (iterationNode->GetId()->GetKey() == secondKey) {
					return true;
				}
				iterationNode = iterationNode->GetNext();
			}
			return false;
		}

		return false;
	}

	size_t GetVertexCount() {
		Node<T>* iterationNode = _head;
		size_t count = 0;
		while (iterationNode != nullptr) {
			count++;
			iterationNode = iterationNode->GetNext();
		}
		return count;
	}

	size_t GetEdgeCount() {
		Node<T>* iterationNode = _head;
		size_t count = 0;
		while (iterationNode != nullptr) {
			Edge<T>* iterationEdge = iterationNode->GetTail();
			while (iterationEdge != 0) {
				count++;
				iterationEdge = iterationEdge->GetNext();
			}
			iterationNode = iterationNode->GetNext();
		}
		return count;
	}

	size_t GetDegreeVertex(T key) {
		Node<T>* node;
		size_t count = 0;
		if (findVertex(key, node)) {
			Edge<T>* iterationEdge = node->GetTail();
			while (iterationEdge != nullptr) {
				count++;
			}
			return node->GetCount() + count;
		}
		return 0;
	}

	std::pair<size_t, size_t> GetDegreeEdge(T firstKey, T secondKey) {
		Node<T>* node1 = nullptr;
		Node<T>* node2 = nullptr;
		size_t count1 = 0;
		size_t count2 = 0;
		if (findVertices(firstKey, secondKey, node1, node2)) {
			Edge<T>* iterationEdge = node1->GetTail();
			while (iterationEdge != nullptr) {
				count1++;
				iterationEdge = iterationEdge->GetNext();
			}
			iterationEdge = node2->GetTail();
			while (iterationEdge != nullptr) {
				count2++;
				iterationEdge = iterationEdge->GetNext();
			}
			return std::make_pair<size_t, size_t>(node1->GetCount() + count1, node2->GetCount() + count2);
		}
		return std::make_pair<size_t, size_t>(0, 0);
	}

	void Print() {
		Node<T>* iter = _head;
		while (iter != nullptr) {
			iter->Print();
			iter = iter->GetNext();
		}
	}

private:
	bool findVertex(T key, Node<T>*& node) {
		Node<T>* iterationNode = _head;
		while (iterationNode != nullptr) {
			if (iterationNode->GetKey() == key) {
				node = iterationNode;
				return true;
			}

			iterationNode = iterationNode->GetNext();
		}
		return false;
	}

	bool findVertices(T firstKey, T secondKey, Node<T>*& firstNode, Node<T>*& secondNode) {
		Node<T>* iterationNode = _head;
		while (iterationNode != nullptr) {
			if (iterationNode->GetKey() == firstKey) {
				firstNode = iterationNode;
			}
			if (iterationNode->GetKey() == secondKey) {
				secondNode = iterationNode;
			}

			if (firstNode != nullptr && secondNode != nullptr) {
				return true;
			}

			iterationNode = iterationNode->GetNext();
		}
		return false;
	}

	Node<T>* _head;
	Node<T>* _tail;
};

template class Graph<int>;