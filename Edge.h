#pragma once
template<typename T>
class Edge {
public:
	using ValueType = T;
	using NodePtr = Node<T>*;
	using EdgePtr = Edge<T>*;
public:
	Edge(Node<T>* id) : _next(nullptr), _id(id), _prev(nullptr) { }

	Edge(Node<T>* id, Edge* prev) : _next(nullptr), _id(id), _prev(prev) { }

	void AddNode(Node<T>* id) {
		if (_next != nullptr) {
			_next->AddNode(id);
			return;
		}
		_next = new Edge(id, this);
		id->IncreaseCount();
	}

	void RemoveNode(Node<T>* id) {
		if (_next != nullptr) {
			if (_next->GetId() != id)
				_next->RemoveNode(id);
			else {
				id->DecreaseCount();

				Edge* save = _next;
				this->_next = _next->_next;
				if (this->_next != nullptr)
					this->_next->_prev = this;

				delete save;
			}

		}

	}

	void DeleteAll() {
		if (_next != nullptr) {
			_next->DeleteAll();
			return;
		}
		_id->DecreaseCount();
		delete this;
	}

	Node<T>* GetId() {
		return _id;
	}

	Edge*& GetNext() {
		return _next;
	}

	Edge*& GetPrev() {
		return _prev;
	}

	void Print() {
		std::cout << _id->GetKey() << " ";
	}

private:
	Node<T>* _id;
	Edge<T>* _next;
	Edge<T>* _prev;
};