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

	iterator fictitious_head() { return iterator(head); };
	iterator begin() { return iterator(head->next); };
	iterator end() { return iterator(nullptr); };
	const_iterator cfictitious_head() const { return const_iterator(head); }
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
		node* copy_current = copy->head;
		while (copy_current != nullptr) {
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