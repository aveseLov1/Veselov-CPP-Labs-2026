#ifndef SET_H
#define SET_H

#include "Container.h"
#include <algorithm>
#include <cstring>

template <typename T>
class Set : public Container<T> {
public:
    Set() : Container<T>() {}
    Set(const T& element) : Container<T>(element) {}
    Set(const Set& other) : Container<T>(other) {}
    Set(Set&& other) noexcept : Container<T>(std::move(other)) {}

    bool is_element(const T& element) const {
        return q_find(element) != -1;
    }

    int q_find(const T& element) const {
        if (this->size == 0) return -1;

        int left = 0;
        int right = this->size - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (this->pdata[mid] == element) {
                return mid;
            } else if (this->pdata[mid] < element) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1;
    }

    void push(const T& element) {
        if (!is_element(element)) {
            Container<T>::push(element);
            sort();
        }
    }

    void pop(const T& element) {
        int index = q_find(element);
        if (index != -1) {
            Container<T>::pop(static_cast<size_t>(index));
        }
    }

    Set& operator+=(const Set& other) {
        for (size_t i = 0; i < other.size; ++i) {
            this->push(other.pdata[i]);
        }
        return *this;
    }

    Set& operator-=(const Set& other) {
        for (size_t i = 0; i < other.size; ++i) {
            this->pop(other.pdata[i]);
        }
        return *this;
    }

    Set& operator*=(const Set& other) {
        Set<T> result;
        for (size_t i = 0; i < this->size; ++i) {
            if (other.is_element(this->pdata[i])) {
                result.push(this->pdata[i]);
            }
        }
        *this = result;
        return *this;
    }

    Set operator+(const Set& other) const {
        Set result = *this;
        result += other;
        return result;
    }

    Set operator-(const Set& other) const {
        Set result = *this;
        result -= other;
        return result;
    }

    Set operator*(const Set& other) const {
        Set result = *this;
        result *= other;
        return result;
    }

    bool operator==(const Set& other) const {
        if (this->size != other.size) return false;
        for (size_t i = 0; i < this->size; ++i) {
            if (this->pdata[i] != other.pdata[i]) return false;
        }
        return true;
    }

    bool operator!=(const Set& other) const {
        return !(*this == other);
    }

    Set& operator=(const Set& other) {
        if (this != &other) {
            Container<T>::operator=(other);
        }
        return *this;
    }

    Set& operator=(Set&& other) noexcept {
        if (this != &other) {
            Container<T>::operator=(std::move(other));
        }
        return *this;
    }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Set<U>& set);

private:
    void sort() {
        if (this->size > 1) {
            for (size_t i = 0; i < this->size - 1; ++i) {
                for (size_t j = 0; j < this->size - i - 1; ++j) {
                    if (this->pdata[j] > this->pdata[j + 1]) {
                        std::swap(this->pdata[j], this->pdata[j + 1]);
                    }
                }
            }
        }
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Set<T>& set) {
    os << "{";
    for (size_t i = 0; i < set.size; ++i) {
        os << set.pdata[i];
        if (i < set.size - 1) os << ", ";
    }
    os << "}";
    return os;
}

// Специализация для char*
template <>
class Set<char*> : public Container<char*> {
public:
    Set() : Container<char*>() {}
    Set(const char* element) : Container<char*>() {
        if (element) push(element);
    }
    Set(const Set& other) : Container<char*>() {
        this->max_size = other.max_size;
        this->size = other.size;
        this->pdata = new char*[this->max_size];
        for (size_t i = 0; i < this->size; ++i) {
            char* copy = new char[strlen(other.pdata[i]) + 1];
            strcpy(copy, other.pdata[i]);
            this->pdata[i] = copy;
        }
    }

    Set(Set&& other) noexcept : Container<char*>() {
        this->max_size = other.max_size;
        this->size = other.size;
        this->pdata = other.pdata;
        other.pdata = nullptr;
        other.size = 0;
        other.max_size = 1;
    }

    ~Set() {
        for (size_t i = 0; i < this->size; ++i) {
            delete[] this->pdata[i];
        }
        delete[] this->pdata;
        this->pdata = nullptr;
    }

    bool is_element(const char* element) const {
        return q_find(element) != -1;
    }

    int q_find(const char* element) const {
        if (this->size == 0 || !element) return -1;

        int left = 0;
        int right = static_cast<int>(this->size) - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            int cmp = strcmp(this->pdata[mid], element);

            if (cmp == 0) return mid;
            else if (cmp < 0) left = mid + 1;
            else right = mid - 1;
        }
        return -1;
    }

    void push(const char* element) {
        if (!element) return;
        if (!is_element(element)) {
            char* copy = new char[strlen(element) + 1];
            strcpy(copy, element);
            if (this->size >= this->max_size) {
                this->max_size *= 2;
                char** new_pdata = new char*[this->max_size];
                for (size_t i = 0; i < this->size; ++i) {
                    new_pdata[i] = this->pdata[i];
                }
                delete[] this->pdata;
                this->pdata = new_pdata;
            }
            this->pdata[this->size++] = copy;
            sort();
        }
    }

    void pop(const char* element) {
        int index = q_find(element);
        if (index != -1) {
            delete[] this->pdata[index];
            for (size_t i = index; i < this->size - 1; ++i) {
                this->pdata[i] = this->pdata[i + 1];
            }
            this->size--;

            if (this->size < this->max_size / 4 && this->max_size > 1) {
                this->max_size /= 2;
                char** new_pdata = new char*[this->max_size];
                for (size_t i = 0; i < this->size; ++i) {
                    new_pdata[i] = this->pdata[i];
                }
                delete[] this->pdata;
                this->pdata = new_pdata;
            }
        }
    }

    Set& operator+=(const Set& other) {
        for (size_t i = 0; i < other.size; ++i) {
            this->push(other.pdata[i]);
        }
        return *this;
    }

    Set& operator-=(const Set& other) {
        for (size_t i = 0; i < other.size; ++i) {
            this->pop(other.pdata[i]);
        }
        return *this;
    }

    Set& operator*=(const Set& other) {
        Set<char*> result;
        for (size_t i = 0; i < this->size; ++i) {
            if (other.is_element(this->pdata[i])) {
                result.push(this->pdata[i]);
            }
        }
        *this = std::move(result);
        return *this;
    }

    Set operator+(const Set& other) const {
        Set result = *this;
        result += other;
        return result;
    }

    Set operator-(const Set& other) const {
        Set result = *this;
        result -= other;
        return result;
    }

    Set operator*(const Set& other) const {
        Set result = *this;
        result *= other;
        return result;
    }

    bool operator==(const Set& other) const {
        if (this->size != other.size) return false;
        for (size_t i = 0; i < this->size; ++i) {
            if (strcmp(this->pdata[i], other.pdata[i]) != 0) return false;
        }
        return true;
    }

    bool operator!=(const Set& other) const {
        return !(*this == other);
    }

    Set& operator=(const Set& other) {
        if (this != &other) {
            for (size_t i = 0; i < this->size; ++i) {
                delete[] this->pdata[i];
            }
            delete[] this->pdata;

            this->max_size = other.max_size;
            this->size = other.size;
            this->pdata = new char*[this->max_size];
            for (size_t i = 0; i < this->size; ++i) {
                char* copy = new char[strlen(other.pdata[i]) + 1];
                strcpy(copy, other.pdata[i]);
                this->pdata[i] = copy;
            }
        }
        return *this;
    }

    Set& operator=(Set&& other) noexcept {
        if (this != &other) {
            for (size_t i = 0; i < this->size; ++i) {
                delete[] this->pdata[i];
            }
            delete[] this->pdata;

            this->max_size = other.max_size;
            this->size = other.size;
            this->pdata = other.pdata;

            other.pdata = nullptr;
            other.size = 0;
            other.max_size = 1;
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Set& set) {
        os << "{";
        for (size_t i = 0; i < set.size; ++i) {
            os << set.pdata[i];
            if (i < set.size - 1) os << ", ";
        }
        os << "}";
        return os;
    }

private:
    void sort() {
        if (this->size > 1) {
            for (size_t i = 0; i < this->size - 1; ++i) {
                for (size_t j = 0; j < this->size - i - 1; ++j) {
                    if (strcmp(this->pdata[j], this->pdata[j + 1]) > 0) {
                        std::swap(this->pdata[j], this->pdata[j + 1]);
                    }
                }
            }
        }
    }
};

#endif // SET_H
