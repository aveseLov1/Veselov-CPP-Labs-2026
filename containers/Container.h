#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>
#include <stdexcept>
#include <cstring>

template <typename T>
class Container {
protected:
    size_t max_size;
    size_t size;
    T* pdata;

    void resize() {
        T* new_pdata = new T[max_size];
        for (size_t i = 0; i < size; ++i) {
            new_pdata[i] = pdata[i];
        }
        delete[] pdata;
        pdata = new_pdata;
    }

public:
    Container(size_t initial_size = 0)
        : max_size(initial_size > 0 ? initial_size : 1), size(0) {
        pdata = new T[max_size];
    }

    Container(const T& element)
        : max_size(1), size(0) {
        pdata = new T[max_size];
        push(element);
    }

    Container(const Container& other)
        : max_size(other.max_size), size(other.size) {
        pdata = new T[max_size];
        for (size_t i = 0; i < size; ++i) {
            pdata[i] = other.pdata[i];
        }
    }

    Container(Container&& other) noexcept
        : max_size(other.max_size), size(other.size), pdata(other.pdata) {
        other.pdata = nullptr;
        other.size = 0;
        other.max_size = 1;
    }

    virtual ~Container() {
        delete[] pdata;
    }

    virtual void push(const T& element) {
        if (size >= max_size) {
            max_size *= 2;
            resize();
        }
        pdata[size++] = element;
    }

    virtual void pop(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }

        for (size_t i = index; i < size - 1; ++i) {
            pdata[i] = pdata[i + 1];
        }
        size--;

        if (size < max_size / 4 && max_size > 1) {
            max_size /= 2;
            resize();
        }
    }

    virtual int find(const T& element) const {
        for (size_t i = 0; i < size; ++i) {
            if (pdata[i] == element) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return pdata[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return pdata[index];
    }

    Container& operator=(const Container& other) {
        if (this != &other) {
            delete[] pdata;
            max_size = other.max_size;
            size = other.size;
            pdata = new T[max_size];
            for (size_t i = 0; i < size; ++i) {
                pdata[i] = other.pdata[i];
            }
        }
        return *this;
    }

    Container& operator=(Container&& other) noexcept {
        if (this != &other) {
            delete[] pdata;
            max_size = other.max_size;
            size = other.size;
            pdata = other.pdata;
            other.pdata = nullptr;
            other.size = 0;
            other.max_size = 1;
        }
        return *this;
    }

    size_t getSize() const { return size; }
    size_t getMaxSize() const { return max_size; }
    bool isEmpty() const { return size == 0; }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Container<U>& container);
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Container<T>& container) {
    os << "[";
    for (size_t i = 0; i < container.size; ++i) {
        os << container.pdata[i];
        if (i < container.size - 1) os << ", ";
    }
    os << "]";
    return os;
}

#endif // CONTAINER_H
