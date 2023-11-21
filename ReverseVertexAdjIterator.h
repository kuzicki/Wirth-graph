#pragma once
#pragma once

template<typename T>
class Graph;

template<typename Gr>
class ReverseVertexAdjIterator {
public:
	using ValueType = typename Gr::ValueType;
	using NodePtr = Node<ValueType>*;
	using EdgePtr = Edge<ValueType>*;
	using ReferenceType = Node<ValueType>&;
public:
	ReverseVertexAdjIterator(EdgePtr ptr, Graph<ValueType>* graph) : _ptr(ptr), _graph(graph) { 
		if (ptr == nullptr)
			return;
		while (_ptr->GetNext() != nullptr) {
			_ptr = _ptr->GetNext();
		}
	}

	ReverseVertexAdjIterator& operator=(const ReverseVertexAdjIterator& other) {
		_ptr = other._ptr;
		_graph = other._graph;
		return *this;
	}

	ReverseVertexAdjIterator& operator++() {
		_ptr = _ptr->GetPrev();
		return *this;
	}

	ReverseVertexAdjIterator operator++(int) {
		ReverseVertexAdjIterator iterator = *this;
		++(*this);
		return iterator;
	}

	ReverseVertexAdjIterator& operator--() {
		_ptr = _ptr->GetNext();
		return *this;
	}

	ReverseVertexAdjIterator operator--(int) {
		ReverseVertexAdjIterator iterator = *this;
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
		ReverseVertexAdjIterator iter(nullptr, nullptr);
		iter = *this;
		iter++;
		_graph->RemoveVertexPtr(_ptr->GetId());
		_ptr = iter._ptr;
	}

	bool operator==(const ReverseVertexAdjIterator& other) const {
		return _ptr == other._ptr;
	}

	bool operator!=(const ReverseVertexAdjIterator& other) const {
		return _ptr != other._ptr;
	}
private:
	EdgePtr _ptr;
	Graph<ValueType>* _graph;
};