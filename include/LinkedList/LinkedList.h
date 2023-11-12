#pragma once
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <utility>
#include <memory>
#include <windows.h>
#include <random>
#include <complex>

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;



template<typename T>
class LinkedList {
private:
    struct Node {
        T data;
        size_t ind;
        Node* next;
    };
    size_t _size;
    Node* _head;
    istream& input(istream& is);
public:
    LinkedList() : _size(0), _head(nullptr) {}

    LinkedList(const LinkedList& other) : _size(other._size), _head(nullptr) {
        if (!other._head) {
            return;
        }
        _head = new Node(*other._head);
        _head->data = other._head->data;
        Node* tmp = _head;
        Node* other_tmp = other._head->next;

        while (other_tmp != other._head) {
            tmp->next = new Node;
            *(tmp->next)= *other_tmp;

            tmp = tmp->next;
            other_tmp = other_tmp->next;
        }

        tmp->next = _head;
    }

    LinkedList(size_t size, T& low, T& high);

    ~LinkedList() {
        while (_size > 0) {
            Node* tmp = _head;
            _head = _head->next;
            delete tmp;
            --_size;
        }
    }

    size_t get_size() const {
        return _size;
    }

    size_t get_ind(size_t index) const {
        if (index < 0 || index >= _size)
            throw out_of_range("Invalid index!");
        Node* tmp = _head;
        for (size_t i = 0; i < index; ++i, tmp = tmp->next);
        return tmp->ind;
    }

    LinkedList& operator=(const LinkedList& other) {
        if (this == &other) {
            return *this;
        }

        LinkedList temp(other);
        std::swap(_size, temp._size);
        std::swap(_head, temp._head);

        return *this;
    }

    const T& operator[](size_t index) const {
        if (index < 0 || index >= _size)
            throw out_of_range("Invalid index!");
        Node tmp = _head;
        for (size_t i = 0; i < index; ++i, tmp = tmp->next);
        return tmp->data;
    }

    T& operator[](size_t index){
        if (index < 0 || index >= _size)
            throw out_of_range("Invalid index!");
        Node* tmp = _head;
        for (size_t i = 0; i < index;++i, tmp = tmp->next);
        return tmp->data;
    }

    void push_tail(T& value) {
        Node* item = new Node();
        item->data = value;
        item->ind = _size;
        if (!_head) {
            _head = item;
            _head->next = _head;
            ++_size;
            return;
        }
        item->next = _head;
        Node* tmp = _head;
        while(tmp->next != _head){
            tmp = tmp->next;
        }
        tmp->next = item;
        ++_size;
    }

    void push_tail(LinkedList Other) {
        if (_head == NULL || Other._head == NULL) {
            return;
        }
        Node* tmp1 = _head;
        Node* tmp2 = Other._head;
        while (tmp1->next != _head)
            tmp1 = tmp1->next;

        while (tmp2->next != Other._head) 
            tmp2 = tmp2->next;
        
        tmp1->next = Other._head;
        tmp2->next = _head;
        _size += Other._size;
        renumber();
    }

    void push_head(T& value) {
        Node* item = new Node();
        item->data = value;
        if (!_head) {
            _head = item;
            _head->next = _head;
            ++_size;
            return;
        }
        item->next = _head;
        Node* tmp = _head;
        while (tmp->next != _head) {
            tmp = tmp->next;
        }
        tmp->next = item;
        _head = item;
        ++_size;
        renumber();
    }

    void push_head(LinkedList Other) {
        if (_head == NULL || Other._head == NULL) {
            return;
        }
        Node* tmp1 = _head;
        Node* tmp2 = Other._head;
        while (tmp1->next != _head)
            tmp1 = tmp1->next;

        while (tmp2->next != Other._head)
            tmp2 = tmp2->next;

        tmp1->next = Other._head;
        tmp2->next = _head;
        _head = tmp2;
        _size += Other._size;
        renumber();
    }

    void pop_head() {
        if (!_head)
            throw invalid_argument("List is empty!");
        Node* tmp = _head->next;
        Node* tmp_end = _head;
        for (tmp_end; tmp_end->next != _head; tmp_end = tmp_end->next);
        delete _head;
        tmp_end->next = tmp;
        _head = tmp;
        --_size;
        renumber();
    }
    void pop_tail() {
        if (!_head)
            throw invalid_argument("List is empty!");
        Node* before_del_elem = _head;
        for (before_del_elem; before_del_elem->next->next != _head; before_del_elem = before_del_elem->next);
        Node* tmp_end = before_del_elem->next;
        delete tmp_end;
        before_del_elem->next = _head;
        --_size;
    }

    void delete_nodes(T& value);

    void delete_nulls();

    friend ostream& operator<<(std::ostream& os, const LinkedList<T>& List) {
        if (List._head == nullptr) {
            return os;
        }

        Node* tmp = List._head;
        os << "(";
        while (true) {
            os << tmp->data; /*<< "[" << tmp->ind <<"]";*/
            tmp = tmp->next;
            if (tmp == List._head)
                break;
            else
                os << "; ";
        }
        os << ")";
        std::cout << std::endl;
        return os;
    }
    friend istream& operator>>(istream& is, LinkedList<T>& List) {
        cout << "\nSize of vector:";
        is >> List._size;
        if (List._size == 0) {
            List._head = nullptr;
            List._size = 0;
            return is;
        }
        else
            return List.input();
    }

    void renumber() {
        Node* tmp = _head;
        for (size_t i = 0; i < _size; ++i, tmp = tmp->next) 
            tmp->ind = i;
    }
};

template<typename T>
void LinkedList<T>::delete_nodes(T& value) {
    if (!_head) {
        return;
    }
    Node* head = _head->next, * previous = _head;
    for (size_t i = 0; i <= _size; ++i) {
        if (head->data == value) {
            previous->next = head->next;
            delete head;
            head = previous->next;
            --_size;
        }
        else {
            head = head->next;
            previous = previous->next;
        }
    }
    if (_head->data == value) {
        previous->next = _head->next;
        delete _head;
        _head = previous->next;
        --_size;
    }
    renumber();
}
template<typename T>
void LinkedList<T>::delete_nulls() {
    if (!_head) {
        return;
    }
    T val_null = 0;
    Node* head = _head->next, * previous = _head;
    for (size_t i = 0; i <= _size; ++i) {
        if (head->data == val_null) {
            previous->next = head->next;
            delete head;
            head = previous->next;
            --_size;
        }
        else {
            head = head->next;
            previous = previous->next;
        }
    }
    if (_head->data == val_null) {
        previous->next = _head->next;
        delete _head;
        _head = previous->next;
        --_size;
    }
}

template<typename T>
T& representation_polynomial(LinkedList<T> List, T x) {
    List.delete_nulls();
    T sum = 0;
    for (size_t i = 0; i < List.get_size(); ++i) {
        sum += List[i] * pow(x, List.get_ind(i));
    }
    return sum;
}