#pragma once
#include <iostream>
#include <iterator>

template <typename T>
class list {
private:
	struct node {
		T data;
		node* next;

		node(const T& value = T()) : data(value) {}
		node(const node& copy) : data(copy.data) {}
	};

	node* head = new node();
	size_t _size;

	void _merge(node*& first, node*& second);
	void merge_sort(node*& first);

public:
	class iterator {
	public:
		using value_type = T;
		using reference = T&;
		using pointer = T*;
		using iterator_category = std::forward_iterator_tag;

		iterator(node* copy) : _node(copy) {}

		iterator operator++() { _node = _node->next; return *this; }
		iterator operator++(int) { iterator temp = *this; ++(*this); return temp; }
		bool operator==(const iterator& it) const { return _node == it._node; }
		bool operator!=(const iterator& it) const { return _node != it._node; }
		reference operator*() const { return _node->data; }
		reference operator->() const { return _node->data; }
	private:
		node* _node;
	};

	class const_iterator {
	public:
		using value_type = T;
		using reference = const T&;
		using pointer = const T*;
		using iterator_category = std::forward_iterator_tag;

		const_iterator(node* copy) : _node(copy) {}

		const_iterator operator++() { _node = _node->next; return *this; }
		const_iterator operator++(int) { const_iterator temp = *this; ++(*this); return temp; }
		bool operator==(const const_iterator& it) const { return _node == it._node; }
		bool operator!=(const const_iterator& it) const { return _node != it._node; }
		reference operator*() const { return _node->data; }
		reference operator->() const { return _node->data; }
	private:
		node* _node;
	};

	iterator dummy_head() { return iterator(head); };
	iterator begin() { return iterator(head->next); };
	iterator end() { return iterator(nullptr); };
	const_iterator cdummy_head() const { return const_iterator(head); }
	const_iterator cbegin() const { return const_iterator(head->next); }
	const_iterator cend() const { return const_iterator(nullptr); }

	list() { head->next = nullptr; }

	list(size_t _size) : _size(_size) {
		node* current = head;
		for (size_t i = 0; i < _size; ++i) {
			current->next = new node();
			current = current->next;
		}
		current->next = nullptr;
	}

	list(const list& copy) : _size(copy._size) {
		node* current = head;
		node* copy_current = copy.head;
		while (copy_current->next != nullptr) {
			current->next = new node(copy_current->next->data);
			current = current->next;
			copy_current = copy_current->next;
		}
		current->next = nullptr;
	}

	size_t size() const { return _size; };
	bool empty() const { return _size == 0; };

	void clear() {
		node* current = head;
		node* temp = head;
		while (current->next != nullptr) {
			temp = current->next;
			delete current;
			current = temp;
		}
		head->next = nullptr;
		_size = 0;
	}

	void push_front(const T& value) {
		node* new_node = new node(value);
		new_node->next = head->next;
		head->next = new_node;
		++_size;
	}

	void pop_front() {
		node* to_delete = head->next;
		head->next = to_delete->next;
		delete to_delete;
		--_size;
	}

	T& front() {
		return head->next->data;
	}

	iterator erase_after(const iterator& idx) {
		node* to_delete = idx._node->next;
		idx._node->next = to_delete->next;
		delete to_delete;
		--_size;
		return iterator(idx._node->next);
	}

	void merge(list other) {
		_size += other._size;
		_merge(head->next, other.head->next);
		other.head->next = nullptr;
	}

	void sort() {
		merge_sort(head->next);
	}

	friend std::ostream& operator<<(std::ostream& out, const list& list) {
		node* current = list.head;
		while (current->next != nullptr) {
			out << current->next->data;
			out << " ";
			current = current->next;
		}
		return out;
	}

	~list() { clear(); }
};

template<typename T>
void list<T>::_merge(node*& first, node*& second) {
	node* begin = new node();
	node* current = begin;
	node* left = first;
	node* right = second;
	while (left != nullptr && right != nullptr) {
		if (left->data <= right->data) {
			current->next = left;
			left = left->next;
		}
		else {
			current->next = right;
			right = right->next;
		}
		current = current->next;
	}
	if (left == nullptr) {
		while (right != nullptr) {
			current->next = right;
			right = right->next;
			current = current->next;
		}
	}
	else if (right == nullptr) {
		while (left != nullptr) {
			current->next = left;
			left = left->next;
			current = current->next;
		}
	}

	current->next = nullptr;
	first = begin->next;
}

template<typename T>
void list<T>::merge_sort(node*& first) {
	if (first == nullptr || first->next == nullptr) return;
	node* mid = first;
	node* fast = first->next;
	node* second;
	while (fast->next != nullptr) {
		mid = mid->next;
		fast = fast->next;
		if (fast->next == nullptr) break;
		fast = fast->next;
	}
	second = mid->next;
	mid->next = nullptr;
	merge_sort(first);
	merge_sort(second);
	_merge(first, second);
}