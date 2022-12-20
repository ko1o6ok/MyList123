#pragma once
#include <iostream>
using namespace std;
template <typename T>
struct Node {
    T value;
    Node<T>* nxt;
    explicit Node(T _v) {
        value = _v;
        nxt = nullptr;
    }
};
template <typename T>
class MyList {
public:
    Node<T>* first;
    Node<T>* last;
    MyList() {
        first = nullptr;
        last = nullptr;
    }
    bool empty() {
        return first == nullptr;
    }
    void push_back(T _v) {
        auto* t = new Node<T>(_v);
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
        auto* new_node = new Node<T>(val);
        Node<T>* s1 = this->operator[](pos - 1);
        Node<T>* s2 = s1->nxt;
        s1->nxt = new_node;
        new_node->nxt = s2;
    }
    void reverse() {
        // Длина должна быть >= 3 , иначе можно сразу переставить
        if (empty() || (first == last)) return; // Длина = 0 или 1, ничего делать не надо
        Node<T>* b = first->nxt;
        if (b == last) { // Длина = 2, можно элементарно переставить: a -> b => b -> a
            first->nxt = nullptr;
            last->nxt = first;
            Node<T>* temp;
            temp = first;
            first = last;
            last = temp;
            return;
        }
        // Кратко: алгоритм берёт набор узлов  ..<- a  b -> c -> и итеративно "сдвигает" его вниз,
        // после чего меняет концы местами
        // Сдвиг не в смысле значений, а в смысле направления указателей nxt
        // <- -> -> -> -> перейдёт в <- <- -> -> -> , что далее перейдёт в <- <- <- -> ->
        Node<T>* a = first;
        Node<T>* c = b->nxt;
        a->nxt = nullptr;
        while (c != last) {
            // Здесь происходит сдвиг узла
            b->nxt = a;
            a = b;
            b = c;
            c = c->nxt;
        }
        b->nxt = a;
        c->nxt = b;
        // А здесь я меняю концы местами
        Node<T>* temp;
        temp = first;
        first = last;
        last = temp;
        // first <- a b -> c -> ...

    }
    friend ostream& operator <<(ostream& ostr, MyList<T>& l) {
        if (l.empty()) {
            ostr << " " << endl;
            return ostr;
        }
        Node<T>* t = l.first;
        while (t) {
            ostr << t->value << "->";
            t = t->nxt;
        }
        ostr << endl;
        return ostr;
    }
    // Есть ли в этом списке цикл
    bool hasCycle() {
        // Лишь один элемент
        if (first == last)
            return false;
        // Два элемента
        if (first->nxt == last)
            return first == last->nxt;

        Node<T>* tortoise = first;
        Node<T>* hare = tortoise->nxt;
        
        //int tort_count = 1;
        //int hare_count = 2;
        while (tortoise != hare) {
            if (hare->nxt->nxt == nullptr)
                return false;
            tortoise = tortoise->nxt;
            //tort_count++;
            hare = hare->nxt->nxt;
            //hare_count += 2;
            //cout << "Tortoise: " << tort_count << "| Hare: " << hare_count << endl;
        }
        return true;
    }

    Node<T>* find_middle() {
        // Начинают с одной позиции
        Node<T>* tortoise = first;
        Node<T>* hare = first;
        // Если элемент только один, то он же и является серединой
        if (first == last)
            return first;
        // Для чётного числа элементов серединой будем считать левый из 2-х средних элементов
        // Это связано с тем, что заец в два раза быстрее черепахи и придёт именно туда
        while (hare->nxt->nxt != nullptr)
        {
            tortoise = tortoise->nxt;
            hare = hare->nxt->nxt;
            if (hare->nxt == nullptr)
                break;
        }
        return tortoise;
    }
    void perform_bubblesort() {
        // Только один элемент
        if (first == last)
            return;
        // Два элемента
        if (first->nxt == last) {
            if (first->value > last->value) {
                Node<T>* temp;
                temp = first;
                first = last;
                first->nxt = temp;
                last = temp;
                last->nxt = nullptr;
            }
            return;
        }
        // Теперь >= 3 элемента
        // Я иду тройками, чтобы устанавливать nxt предыд. элемента
        Node<T>* one;
        Node<T>* two;
        Node<T>* three;
        
        bool swapped;
        while (true)
        {
            swapped = false;
            one = first;
            two = one->nxt;
            if (two == nullptr)
                break;
            three = two->nxt;
            // Но всё равно нужно обработать первые 2 элемента
            if (one->value > two->value) {
                Node<T>* temp;
                temp = one;
                one = two;
                one->nxt = temp;
                two = temp;
                one->nxt = three;
                swapped = true;
            }
            
            //cout << *this << endl;
            while (three->nxt != nullptr) {
                cout << three->nxt << endl;
                if (two->value > three->value) {
                    one->nxt = three;
                    cout << one << ", " << two << ", " << three << endl;
                    swap_nodes(two, three);
                    cout << one->nxt << ", " << two->nxt << ", " << three->nxt << endl;
                    swapped = true;
                    one->nxt = three;
                    //cout << *this << endl;
                    one = three;
                    three = two->nxt;
                    
                }
                else {
                    one = one->nxt;
                    two = two->nxt;
                    three = three->nxt;
                }
                
            }
            
            if (swapped == false)
                break;
        }
    }
};

template <typename T>
void swap_nodes(Node<T>* n2, Node<T>* n3) {
    Node<T>* t1 = n3->nxt;
    Node<T>*  t2 = n2;
    n2 = n3;
    n2->nxt = t1;
    n3 = t2;
}