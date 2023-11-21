#pragma once
template<typename Gr>
class EdgeAdjIterator {
public:
	using ValueType = typename Gr::ValueType;
	using EdgePtr = Edge<ValueType>*;
	using NodePtr = Node<ValueType>*;
	using ReferenceType = Edge<ValueType>&;
public:
	EdgeAdjIterator(EdgePtr ptr, NodePtr node) : _ptr(ptr), _node(node) { }

	EdgeAdjIterator& operator=(const EdgeAdjIterator& other) {
		_ptr = other._ptr;
		_node = other._node;
		return *this;
	}

	EdgeAdjIterator& operator++() {
		_ptr = _ptr->GetNext();
		return *this;
	}

	EdgeAdjIterator operator++(int) {
		EdgeAdjIterator iterator = *this;
		++(*this);
		return iterator;
	}

	EdgeAdjIterator& operator--() {
		_ptr = _ptr->GetPrev();
		return *this;
	}

	void Remove() {
		EdgeAdjIterator iter;
		iter = *this;
		iter++;
		_node->RemoveEdge(_ptr->GetId());
		_ptr = iter->_ptr;
		_node = iter->_node;
	}

	EdgeAdjIterator operator--(int) {
		EdgeAdjIterator iterator = *this;
		--(*this);
		return iterator;
	}

	EdgePtr operator->() {
		return _ptr;
	}

	ReferenceType operator*() {
		return *_ptr;
	}

	bool operator==(const EdgeAdjIterator& other) const {
		return _ptr == other._ptr;
	}

	bool operator!=(const EdgeAdjIterator& other) const {
		return _ptr != other._ptr;
	}
private:
	EdgePtr _ptr;
	NodePtr _node;
};