#pragma once
template<typename Gr>
class EdgeIterator {
public:
	using ValueType = typename Gr::ValueType;
	using NodePtr = Node<ValueType>*;
	using EdgePtr = Edge<ValueType>*;
	using ReferenceType = Edge<ValueType>&;
public:
	EdgeIterator(NodePtr ptr) : _ptr(ptr) {
		if (ptr != nullptr)
			_edgePtr = _ptr->GetTail();
		else
			_edgePtr = nullptr;
	}

	EdgeIterator(NodePtr ptr, EdgePtr edgePtr) : _ptr(ptr), _edgePtr(edgePtr) {
	}

	EdgeIterator& operator++() {
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

	EdgeIterator operator++(int) {
		EdgeIterator iterator = *this;
		++(*this);
		return iterator;
	}

	EdgeIterator& operator--() {
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

	void Remove() {
		EdgeIterator iter(_ptr, _edgePtr);
		iter++;
		_ptr->RemoveEdge(_edgePtr->GetId());
		_ptr = iter._ptr;
		_edgePtr = iter._edgePtr;
	}

	EdgeIterator operator--(int) {
		EdgeIterator iterator = *this;
		--(*this);
		return iterator;
	}

	EdgePtr operator->() {
		return _edgePtr;
	}

	ReferenceType operator*() {
		return *_edgePtr;
	}

	bool operator==(const EdgeIterator& other) const {
		return _ptr == other._ptr && _edgePtr == other._edgePtr;
	}

	bool operator!=(const EdgeIterator& other) const {
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