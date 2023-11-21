#pragma once
template<typename Gr>
class ReverseEdgeAdjIterator {
public:
	using ValueType = typename Gr::ValueType;
	using EdgePtr = Edge<ValueType>*;
	using NodePtr = Node<ValueType>*;
	using ReferenceType = Edge<ValueType>&;
public:
	ReverseEdgeAdjIterator(EdgePtr ptr, NodePtr node) : _ptr(ptr), _node(node) { 
		if (ptr == nullptr)
			return;
		while (_ptr->GetNext()) {
			_ptr = _ptr->GetNext();
		}
	}

	ReverseEdgeAdjIterator& operator=(const ReverseEdgeAdjIterator& other) {
		_ptr = other._ptr;
		_node = other._node;
		return *this;
	}

	ReverseEdgeAdjIterator& operator++() {
		_ptr = _ptr->GetPrev();
		return *this;
	}

	ReverseEdgeAdjIterator operator++(int) {
		ReverseEdgeAdjIterator iterator = *this;
		++(*this);
		return iterator;
	}

	ReverseEdgeAdjIterator& operator--() {
		_ptr = _ptr->GetNext();
		return *this;
	}

	void Remove() {
		ReverseEdgeAdjIterator iter(nullptr, nullptr);
		iter = *this;
		iter++;
		_node->RemoveEdge(_ptr->GetId());
		_ptr = iter._ptr;
		_node = iter._node;
	}

	ReverseEdgeAdjIterator operator--(int) {
		ReverseEdgeAdjIterator iterator = *this;
		--(*this);
		return iterator;
	}

	EdgePtr operator->() {
		return _ptr;
	}

	ReferenceType operator*() {
		return *_ptr;
	}

	bool operator==(const ReverseEdgeAdjIterator& other) const {
		return _ptr == other._ptr;
	}

	bool operator!=(const ReverseEdgeAdjIterator& other) const {
		return _ptr != other._ptr;
	}
private:
	EdgePtr _ptr;
	NodePtr _node;
};

