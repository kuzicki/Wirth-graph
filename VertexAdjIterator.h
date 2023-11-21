#pragma once

template<typename T>
class Graph;

template<typename Gr>
class VertexAdjIterator {
public:
	using ValueType = typename Gr::ValueType;
	using NodePtr = Node<ValueType>*;
	using EdgePtr = Edge<ValueType>*;
	using ReferenceType = Node<ValueType>&;
public:
	VertexAdjIterator(EdgePtr ptr, Graph<ValueType>* graph) : _ptr(ptr), _graph(graph) { }

	VertexAdjIterator& operator=(const VertexAdjIterator& other) {
		_ptr = other._ptr;
		_graph = other._graph;
		return *this;
	}

	VertexAdjIterator& operator++() {
		_ptr = _ptr->GetNext();
		return *this;
	}

	VertexAdjIterator operator++(int) {
		VertexAdjIterator iterator = *this;
		++(*this);
		return iterator;
	}

	VertexAdjIterator& operator--() {
		_ptr = _ptr->GetPrev();
		return *this;
	}

	VertexAdjIterator operator--(int) {
		VertexAdjIterator iterator = *this;
		--(*this);
		return iterator;
	}

	NodePtr operator->() {
		return _ptr->GetId();
	}

	ReferenceType operator*() {
		return *(_ptr->GetId());
	}

	void Remove() {
		VertexAdjIterator iter(nullptr, nullptr);
		iter = *this;
		iter++;
		_graph->RemoveVertexPtr(_ptr->GetId());
		_ptr = iter._ptr;
	}

	bool operator==(const VertexAdjIterator& other) const {
		return _ptr == other._ptr;
	}

	bool operator!=(const VertexAdjIterator& other) const {
		return _ptr != other._ptr;
	}
private:
	EdgePtr _ptr;
	Graph<ValueType>* _graph;
};