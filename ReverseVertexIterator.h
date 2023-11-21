#pragma once
template<typename Gr>
class ReverseVertexIterator {
public:
	using ValueType = typename Gr::ValueType;
	using NodePtr = Node<ValueType>*;
	using ReferenceType = Node<ValueType>&;
public:
	ReverseVertexIterator(NodePtr ptr, Graph<ValueType>* graph) : _ptr(ptr), _graph(graph) { }

	ReverseVertexIterator& operator++() {
		_ptr = _ptr->GetPrev();
		return *this;
	}

	ReverseVertexIterator operator++(int) {
		ReverseVertexIterator iterator = *this;
		++(*this);
		return iterator;
	}

	ReverseVertexIterator& operator--() {
		_ptr = _ptr->GetNext();
		return *this;
	}

	ReverseVertexIterator operator--(int) {
		ReverseVertexIterator iterator = *this;
		--(*this);
		return iterator;
	}

	void Remove() {
		ReverseVertexIterator iter(_ptr, _graph);
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

	bool operator==(const ReverseVertexIterator& other) const {
		return _ptr == other._ptr;
	}

	bool operator!=(const ReverseVertexIterator& other) const {
		return _ptr != other._ptr;
	}
private:
	Graph<ValueType>* _graph;
	NodePtr _ptr;
};