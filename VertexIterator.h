#pragma once
template<typename Gr>
class VertexIterator {
public:
	using ValueType = typename Gr::ValueType;
	using NodePtr = Node<ValueType>*;
	using ReferenceType = Node<ValueType>&;
public:
	VertexIterator(NodePtr ptr, Graph<ValueType>* graph) : _ptr(ptr), _graph(graph) { }

	VertexIterator& operator++() {
		_ptr = _ptr->GetNext();
		return *this;
	}

	VertexIterator operator++(int) {
		VertexIterator iterator = *this;
		++(*this);
		return iterator;
	}

	VertexIterator& operator--() {
		_ptr = _ptr->GetPrev();
		return *this;
	}

	VertexIterator operator--(int) {
		VertexIterator iterator = *this;
		--(*this);
		return iterator;
	}

	void Remove() {
		VertexIterator iter(_ptr, _graph);
		iter++;
		_graph->RemoveVertexPtr(_ptr);
		_ptr = iter._ptr;
	}

	NodePtr operator->() {
		return _ptr;
	}

	ReferenceType operator*() {
		return *_ptr;
	}

	bool operator==(const VertexIterator& other) const {
		return _ptr == other._ptr;
	}

	bool operator!=(const VertexIterator& other) const {
		return _ptr != other._ptr;
	}
private:
	Graph<ValueType>* _graph;
	NodePtr _ptr;
};