#ifndef LINKED_LIST__LINKEDLIST_H_
#define LINKED_LIST__LINKEDLIST_H_

#include <memory>
#include <ostream>

template<class T>
class List {
private:
	class Node {
	public:
		Node(T value, std::unique_ptr<Node> next)
			: value(std::move(value))
			, next(std::move(next)) {}

		T value;
		std::unique_ptr<Node> next;
	};

public:
	List()
		: _size(0) {}

	List(const std::initializer_list<T>& list) : List() {
		_size = list.size();
		if (_size == 0) {
			return;
		}

		auto iter = list.begin();
		_head = std::make_unique<Node>(*iter, nullptr);
		Node* current = _head.get();
		++iter;

		for (; iter < list.end(); ++iter) {
			current->next = std::make_unique<Node>(*iter, nullptr);
			current = current->next.get();
		}
	}

	List(const List& list) {
		_size = list._size;
		if (list._size == 0) {
			return;
		}

		Node* listCurrent = list._head.get();
		_head = std::make_unique<Node>(listCurrent->value, nullptr);
		Node* current = _head.get();
		listCurrent = listCurrent->next.get();

		for (size_t i = 0; i < list.size() - 1; ++i) {
			current->next = std::make_unique<Node>(listCurrent->value, nullptr);
			current = current->next.get();
			listCurrent = listCurrent->next.get();
		}
	}

	List(List&& list) noexcept {
		_head = std::move(list._head);
		_size = list._size;
	}

	size_t size() const {
		return _size;
	}

	void insert(size_t index, T item) {
		if (index == 0) {
			_head = std::make_unique<Node>(std::move(item), std::move(_head));
		} else {
			Node& previous = nodeAt(index - 1);
			previous.next = std::make_unique<Node>(std::move(item), std::move(previous.next));
		}
		++_size;
	}

	void remove(size_t index) {
		if (index >= _size) {
			throw std::out_of_range("index is out of range");
		}

		if (index == 0) {
			_head = std::move(_head->next);
		} else {
			Node& previous = nodeAt(index - 1);
			previous.next = std::move(previous.next->next);
		}
		--_size;
	}

	const Node& nodeAt(size_t index) const {
		if (index >= _size) {
			throw std::out_of_range("index is out of range");
		}

		Node* current = _head.get();
		for (size_t i = 0; i < index; ++i) {
			current = current->next.get();
		}
		return *current;
	}

	Node& nodeAt(size_t index) {
		return const_cast<Node&>(const_cast<const List&>(*this).nodeAt(index));
	}

	T& operator[](size_t index) {
		return const_cast<T&>(const_cast<const List&>(*this)[index]);
	}

	const T& operator[](size_t index) const {
		return nodeAt(index).value;
	}

	friend std::ostream& operator<<(std::ostream& os, const List& list) {
		os << "{ ";
		for (size_t i = 0; i < list.size(); ++i) {
			os << list[i];
			if (i < list.size() - 1) {
				os << ", ";
			}
		}
		os << " }";
		return os;
	}

	bool operator==(const List& rhs) const {
		if (size() != rhs.size()) {
			return false;
		}

		Node* left = _head.get();
		Node* right = rhs._head.get();
		for (size_t i = 0; i < size(); ++i) {
			if (left->value != right->value) {
				return false;
			}

			left = left->next.get();
			right = right->next.get();
		}

		return true;
	}

private:
	std::unique_ptr<Node> _head;
	size_t _size;
};

#endif //LINKED_LIST__LINKEDLIST_H_
