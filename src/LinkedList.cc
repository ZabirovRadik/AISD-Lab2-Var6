
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <random>
#include <complex>
#include <LinkedList/LinkedList.h>



template<>
LinkedList<complex<double>>::LinkedList(size_t size, complex<double>& low, complex<double>& high) : _size(size), _head(nullptr) {
    if (size == 0) {
        return;
    }
    if (low.real() > high.real() || low.imag() > high.imag())
        throw std::invalid_argument("High < low");

    _head = new Node;
    srand((size_t)time(NULL) + rand());
    double rand_real = low.real() + static_cast<double>(rand()) * static_cast<double>(high.real() - low.real()) / RAND_MAX;
    srand((size_t)time(NULL) + rand());
    double rand_imag = low.imag() + static_cast<double>(rand()) * static_cast<double>(high.imag() - low.imag()) / RAND_MAX;
    _head->data = complex<double>(rand_real, rand_imag);
    _head->ind = 0;

    Node* tmp = _head;

    for (size_t i = 1; i < size; ++i) {
        tmp->next = new Node;
        srand((size_t)time(NULL) + i + 9349);
        rand_real = low.real() + static_cast<double>(rand()) * static_cast<double>(high.real() - low.real()) / RAND_MAX;
        srand((size_t)time(NULL) + i + rand());
        rand_imag = low.imag() + static_cast<double>(rand()) * static_cast<double>(high.imag() - low.imag()) / RAND_MAX;
        tmp->next->data = complex<double>(rand_real, rand_imag);
        tmp->next->ind = i;

        tmp = tmp->next;
    }

    tmp->next = _head;
}


template<>
LinkedList<complex<float>>::LinkedList(size_t size, complex<float>& low, complex<float>& high) : _size(size), _head(nullptr) {
    if (size == 0) {
        return;
    }
    if (low.real() > high.real() || low.imag() > high.imag())
        throw std::invalid_argument("High < low");

    _head = new Node;
    srand((size_t)time(NULL) + 1000);
    float rand_real = low.real() + static_cast<float>(rand()) * static_cast<float>(high.real() - low.real()) / RAND_MAX;
    srand((size_t)time(NULL) + rand());
    float rand_imag = low.imag() + static_cast<float>(rand()) * static_cast<float>(high.imag() - low.imag()) / RAND_MAX;
    _head->data = complex<float>(rand_real, rand_imag);
    _head->ind = 0;

    Node* tmp = _head;

    for (size_t i = 1; i < size; ++i) {
        tmp->next = new Node;
        srand((size_t)time(NULL) + i);
        rand_real = low.real() + static_cast<float>(rand()) * static_cast<float>(high.real() - low.real()) / RAND_MAX;
        srand((size_t)time(NULL) + i + rand());
        rand_imag = low.imag() + static_cast<float>(rand()) * static_cast<float>(high.imag() - low.imag()) / RAND_MAX;
        tmp->next->data = complex<float>(rand_real, rand_imag);
        tmp->next->ind = i;

        tmp = tmp->next;
    }
    tmp->next = _head;
}

template<>
LinkedList<double>::LinkedList(size_t size, double& low, double& high) : _size(size), _head(nullptr) {
    if (size == 0) {
        return;
    }
    if (low > high)
        throw std::invalid_argument("High < low");

    _head = new Node;
    srand((size_t)time(NULL) + rand());
    _head->data = low + double(rand()) * double(high - low) / RAND_MAX;
    Node* tmp = _head;
    _head->ind = 0;

    for (size_t i = 1; i < size; ++i) {
        tmp->next = new Node;
        srand((size_t)time(NULL) + i + rand());
        tmp->next->data = low + double(rand()) * double(high - low) / RAND_MAX;
        tmp->next->ind = i;
        tmp = tmp->next;
    }

    tmp->next = _head;
}

template<>
LinkedList<float>::LinkedList(size_t size, float& low, float& high) : _size(size), _head(nullptr) {
    if (size == 0) {
        return;
    }
    if (low > high)
        throw std::invalid_argument("High < low");

    _head = new Node;
    srand((size_t)time(NULL) + rand());
    _head->data = low + float(rand()) * float(high - low) / RAND_MAX;
    Node* tmp = _head;
    _head->ind = 0;

    for (size_t i = 1; i < size; ++i) {
        tmp->next = new Node;
        srand((size_t)time(NULL) + i + rand());
        tmp->next->data = low + float(rand()) * float(high - low) / RAND_MAX;
        tmp->next->ind = i;
        tmp = tmp->next;
    }

    tmp->next = _head;
}

template<typename T>
LinkedList<T>::LinkedList(size_t size, T& low, T& high) : _size(size), _head(nullptr) {
    if (size == 0) {
        return;
    }
    if (low > high)
        throw std::invalid_argument("High < low");
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<T> dis(low, high);
    _head = new Node;
    _head->data = dis(gen);
    Node* tmp = _head;
    _head->ind = 0;

    for (size_t i = 1; i < size; ++i) {
        tmp->next = new Node;
        tmp->next->data = dis(gen);
        tmp->next->ind = i;
        tmp = tmp->next;
    }

    tmp->next = _head;
}

template<>
istream& LinkedList<complex<double>>::input(istream& is) {
    for (size_t i = 0; i < _size; ++i) {
        cout << "shall we continue??(Y/N) ";
        char c;
        is >> c;
        if (c == 'N') {
            return is;
        }
        cout << "enter " << i + 1 << " el: ";
        double real, im;
        is >> real >> im;
        complex<double> z(real, im);
        push_tail(z);
    }
}

template<>
istream& LinkedList<complex<float>>::input(istream& is) {
    for (size_t i = 0; i < _size; ++i) {
        cout << "shall we continue??(Y/N) ";
        char c;
        is >> c;
        if (c == 'N') {
            return is;
        }
        cout << "enter " << i + 1 << " el: ";
        float real, im;
        is >> real >> im;
        complex<float> z(real, im);
        push_tail(z);
    }
}

template<typename T>
istream& LinkedList<T>::input(istream& is) {
    for (size_t i; i < _size; ++i) {
        cout << "Shall we continue?(Y/N) ";
        char c;
        is >> c;
        if (c == 'N') {
            return;
        }
        cout << "enter " << i + 1 << " el: ";
        T item;
        is >> item;
        T tmp = item;
        push_tail(tmp);
    }
}

