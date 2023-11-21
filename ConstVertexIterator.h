#pragma once
template<typename Gr>
class ConstVertexIterator {
public:
	using ValueType = typename Gr::ValueType;
	using NodePtr = Node<ValueType>*;
	using ReferenceType = Node<ValueType>&;
public:
	ConstVertexIterator(NodePtr ptr, Graph<ValueType>* graph) : _ptr(ptr), _graph(graph) { }

	ConstVertexIterator& operator++() {
		_ptr = _ptr->GetNext();
		return *this;
	}

	ConstVertexIterator operator++(int) {
		ConstVertexIterator iterator = *this;
		++(*this);
		return iterator;
	}

	ConstVertexIterator& operator--() {
		_ptr = _ptr->GetPrev();
		return *this;
	}

	ConstVertexIterator operator--(int) {
		ConstVertexIterator iterator = *this;
		--(*this);
		return iterator;
	}

	const NodePtr operator->() {
		return _ptr;
	}

	const ReferenceType operator*() {
		return *_ptr;
	}

	bool operator==(const ConstVertexIterator& other) const {
		return _ptr == other._ptr;
	}

	bool operator!=(const ConstVertexIterator& other) const {
		return _ptr != other._ptr;
	}
private:
	Graph<ValueType>* _graph;
	NodePtr _ptr;
};