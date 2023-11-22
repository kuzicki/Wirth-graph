#pragma once
template<typename Gr>
class ReverseEdgeIterator {
public:
	using ValueType = typename Gr::ValueType;
	using NodePtr = Node<ValueType>*;
	using EdgePtr = Edge<ValueType>*;
	using ReferenceType = Edge<ValueType>&;
public:
	ReverseEdgeIterator(NodePtr ptr) : _ptr(ptr) {
		if (ptr != nullptr) {
			while (_ptr->GetTail() == nullptr) {
				_ptr = _ptr->GetPrev();
			}
			_edgePtr = _ptr->GetTail();
		}
		else
			_edgePtr = nullptr;
	}

	ReverseEdgeIterator(NodePtr ptr, EdgePtr edgePtr) : _ptr(ptr), _edgePtr(edgePtr) {
	}

	ReverseEdgeIterator& operator++() {
		if (_edgePtr->GetPrev() != nullptr)
			_edgePtr = _edgePtr->GetPrev();
		else {
			if (_ptr->GetPrev() != nullptr) {
				_ptr = _ptr->GetPrev();
				_edgePtr = _ptr->GetTail();
				CheckPrev();
			}
			else {
				_ptr = nullptr;
				_edgePtr = nullptr;
			}
		}
		return *this;
	}

	ReverseEdgeIterator operator++(int) {
		ReverseEdgeIterator iterator = *this;
		++(*this);
		return iterator;
	}

	ReverseEdgeIterator& operator--() {
		if (_edgePtr->GetNext() != nullptr)
			_edgePtr = _edgePtr->GetNext();
		else {
			if (_ptr->GetNext() != nullptr) {
				_ptr = _ptr->GetNext();
				_edgePtr = _ptr->GetTail();
				CheckNext();
			}
			else {
				_ptr = nullptr;
				_edgePtr = nullptr;
			}
		}
		return *this;
	}

	void Remove() {
		EdgeIterator iter(_ptr, _edgePtr);
		iter++;
		_ptr->RemoveEdge(_edgePtr->GetId());
		_ptr = iter._ptr;
		_edgePtr = iter._edgePtr;
	}

	ReverseEdgeIterator operator--(int) {
		ReverseEdgeIterator iterator = *this;
		--(*this);
		return iterator;
	}

	EdgePtr operator->() {
		return _edgePtr;
	}

	ReferenceType operator*() {
		return *_edgePtr;
	}

	bool operator==(const ReverseEdgeIterator& other) const {
		return _ptr == other._ptr && _edgePtr == other._edgePtr;
	}

	bool operator!=(const ReverseEdgeIterator& other) const {
		return _ptr != other._ptr || _edgePtr != other._edgePtr;
	}
private:
	void CheckPrev() {
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

	void CheckNext() {
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

	NodePtr _ptr;
	EdgePtr _edgePtr;
};