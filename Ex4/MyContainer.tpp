// roynaor10@gmail.com

#pragma once

#include <algorithm>
#include "MyContainer.hpp"

namespace genericContainer {

    // Adds a new item to the end of the container
    template<typename T>
    void MyContainer<T>::add(const T& item) {
        data.push_back(item);
    }

    // Removes all occurrences of the given item from the container
    // Throws an exception if the item is not found
    template<typename T>
    void MyContainer<T>::remove(const T& item) {
        std::vector<T> newData;
        bool found = false;

        for (const T& val : data) {
            if (val != item) {
                newData.push_back(val);
            } else {
                found = true;
            }
        }

        if (!found) {
            throw std::invalid_argument("Item not found in container.");
        }

        data = newData;
    }

    // Returns the current number of items in the container
    template<typename T>
    size_t MyContainer<T>::size() const {
        return data.size();
    }

    // Output stream operator – prints the container in format: [ item1 item2 ... ]
    template<typename U>
    std::ostream& operator<<(std::ostream& os, const MyContainer<U>& container) {
        os << "[ ";
        for (const auto& item : container.data) {
            os << item << " ";
        }
        os << "]";
        return os;
    }

} // namespace genericContainer
