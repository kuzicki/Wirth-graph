#pragma once
template<typename Gr>
class ConstEdgeIterator {
public:
	using ValueType = typename Gr::ValueType;
	using NodePtr = Node<ValueType>*;
	using EdgePtr = Edge<ValueType>*;
	using ReferenceType = Edge<ValueType>&;
public:
	ConstEdgeIterator(NodePtr ptr) : _ptr(ptr) {
		if (ptr != nullptr)
			_edgePtr = _ptr->GetTail();
		else
			_edgePtr = nullptr;
	}

	ConstEdgeIterator(NodePtr ptr, EdgePtr edgePtr) : _ptr(ptr), _edgePtr(edgePtr) {
	}

	ConstEdgeIterator& operator++() {
		if (_edgePtr->GetNext() != nullptr)
			_edgePtr = _edgePtr->GetNext();
		else {
			if (_ptr->GetNext() != nullptr) {
				_ptr = _ptr->GetNext();
				_edgePtr = _ptr->GetTail();
				if (_ptr->GetTail() == nullptr) {
					while (_ptr->GetTail() == nullptr) {
						if (_ptr->GetNext() != nullptr) {
							_ptr = _ptr->GetNext();
							_edgePtr = _ptr->GetTail();
						}
						else {
							_ptr = _ptr->GetNext();
							if (_ptr == nullptr) {
								_edgePtr = nullptr;
								break;
							}
							_edgePtr = _ptr->GetTail();
							break;
						}
					}
				}
			}
			else {
				_ptr = nullptr;
				_edgePtr = nullptr;
			}
		}
		return *this;
	}

	ConstEdgeIterator operator++(int) {
		ConstEdgeIterator iterator = *this;
		++(*this);
		return iterator;
	}

	ConstEdgeIterator& operator--() {
		if (_edgePtr->GetPrev() != nullptr)
			_edgePtr = _edgePtr->GetPrev();
		else {
			if (_ptr->GetPrev() != nullptr) {
				_ptr = _ptr->GetPrev();
				_edgePtr = _ptr->GetTail();
				if (_ptr->GetTail() == nullptr) {
					while (_ptr->GetTail() == nullptr) {
						if (_ptr->GetPrev() != nullptr) {
							_ptr = _ptr->GetPrev();
							_edgePtr = _ptr->GetTail();
						}
						else {
							_ptr = _ptr->GetPrev();
							if (_ptr == nullptr) {
								_edgePtr = nullptr;
								break;
							}
							_edgePtr = _ptr->GetTail();
							break;
						}
					}
				}
			}
			else {
				_ptr = nullptr;
				_edgePtr = nullptr;
			}
		}
		return *this;
	}

	ConstEdgeIterator operator--(int) {
		ConstEdgeIterator iterator = *this;
		--(*this);
		return iterator;
	}

	const EdgePtr operator->() {
		return _edgePtr;
	}

	const ReferenceType operator*() {
		return *_edgePtr;
	}

	bool operator==(const ConstEdgeIterator& other) const {
		return _ptr == other._ptr && _edgePtr == other._edgePtr;
	}

	bool operator!=(const ConstEdgeIterator& other) const {
		return _ptr != other._ptr || _edgePtr != other._edgePtr;
	}
private:
	NodePtr _ptr;
	EdgePtr _edgePtr;
};