#pragma once

template<typename T>
class Graph;

template<typename Gr>
class ConstVertexAdjIterator {
public:
	using ValueType = typename Gr::ValueType;
	using NodePtr = Node<ValueType>*;
	using EdgePtr = Edge<ValueType>*;
	using ReferenceType = Node<ValueType>&;
public:
	ConstVertexAdjIterator(EdgePtr ptr, Graph<ValueType>* graph) : _ptr(ptr), _graph(graph) { }

	ConstVertexAdjIterator& operator=(const ConstVertexAdjIterator& other) {
		_ptr = other._ptr;
		_graph = other._graph;
		return *this;
	}

	ConstVertexAdjIterator& operator++() {
		_ptr = _ptr->GetNext();
		return *this;
	}

	ConstVertexAdjIterator operator++(int) {
		ConstVertexAdjIterator iterator = *this;
		++(*this);
		return iterator;
	}

	ConstVertexAdjIterator& operator--() {
		_ptr = _ptr->GetPrev();
		return *this;
	}

	ConstVertexAdjIterator operator--(int) {
		ConstVertexAdjIterator iterator = *this;
		--(*this);
		return iterator;
	}

	const NodePtr operator->() {
		return _ptr->GetId();
	}

	const ReferenceType operator*() {
		return *(_ptr->GetId());
	}

	bool operator==(const ConstVertexAdjIterator& other) const {
		return _ptr == other._ptr;
	}

	bool operator!=(const ConstVertexAdjIterator& other) const {
		return _ptr != other._ptr;
	}
private:
	EdgePtr _ptr;
	Graph<ValueType>* _graph;
};