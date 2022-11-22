#pragma once
#include <iostream>
using namespace std;
template <typename T>
struct Node {
	T value;
	Node<T>* nxt;
	Node(T _v){
		value = _v;
		nxt = nullptr;
	}
};
template <typename T>
class MyList {
public:
	Node<T>* first;
	Node<T>* last;
	MyList(){
		first = nullptr;
		last = nullptr;
	}
	bool empty() {
		return first == nullptr;
	}
	void push_back(T _v) {
		Node<T>* t = new Node<T>(_v);
		if (empty()) {
			first = t;
			last = t;
			return;
		}
		last->nxt = t;
		last = t;
	}
	Node<T>* find(T _v) {
		Node<T>* t = first;
		while (t && t->value != _v) t = t->nxt;
		return t ? t : nullptr;
	}
	void del_first() {
		if (empty()) return;
		Node<T>* t = first;
		first = t->nxt;
		delete t;
	}
	void del_last() {
		if (empty()) return;
		if (first == last) {
			del_first();
			return;
		}
		Node<T>* t = first;
		while (t->nxt != last) t = t->nxt;
		t->nxt = nullptr;
		delete last;
		last = t;
	}
	Node<T>* operator[](const int ind) {
		if (empty()) return nullptr;
		Node<T>* t = first;
		for (int i = 0; i < ind; i++) {
			t = t->nxt;
			if (!t) return nullptr;
		}
		return t;
	}
	void insert(T val, const int pos) {
		Node<T>* new_node = new Node<T>(val);
		Node<T>* s1 = this->operator[](pos-1);
		Node<T>* s2 = s1->nxt;
		s1->nxt = new_node;
		new_node->nxt = s2;
	}
	friend ostream& operator <<(ostream& ostr, MyList<T>& l) {
		if (l.empty()) {
			ostr << " " << endl;
			return ostr;
		}
		Node<T>* t = l.first;
		while (t) {
			ostr << t->value <<" ";
			t = t->nxt;
		}
		ostr << endl;
		return ostr;
	}
};