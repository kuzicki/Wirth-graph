#pragma once
template<typename Gr>
class ConstEdgeAdjIterator {
public:
	using ValueType = typename Gr::ValueType;
	using EdgePtr = Edge<ValueType>*;
	using NodePtr = Node<ValueType>*;
	using ReferenceType = Edge<ValueType>&;
public:
	ConstEdgeAdjIterator(EdgePtr ptr, NodePtr node) : _ptr(ptr), _node(node) { }

	ConstEdgeAdjIterator& operator=(const ConstEdgeAdjIterator& other) {
		_ptr = other._ptr;
		_node = other._node;
		return *this;
	}

	ConstEdgeAdjIterator& operator++() {
		_ptr = _ptr->GetNext();
		return *this;
	}

	ConstEdgeAdjIterator operator++(int) {
		ConstEdgeAdjIterator iterator = *this;
		++(*this);
		return iterator;
	}

	ConstEdgeAdjIterator& operator--() {
		_ptr = _ptr->GetPrev();
		return *this;
	}

	ConstEdgeAdjIterator operator--(int) {
		ConstEdgeAdjIterator iterator = *this;
		--(*this);
		return iterator;
	}

	const EdgePtr operator->() {
		return _ptr;
	}

	const ReferenceType operator*() {
		return *_ptr;
	}

	bool operator==(const ConstEdgeAdjIterator& other) const {
		return _ptr == other._ptr;
	}

	bool operator!=(const ConstEdgeAdjIterator& other) const {
		return _ptr != other._ptr;
	}
private:
	EdgePtr _ptr;
	NodePtr _node;
};