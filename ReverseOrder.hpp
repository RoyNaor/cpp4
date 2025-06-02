// roynaor10@gmail.com

#ifndef EX4_REVERSEORDER_HPP
#define EX4_REVERSEORDER_HPP

#include <vector>
#include <algorithm>
#include <stdexcept>

namespace genericContainer {

    // Template class for iterating through a container in reverse order
    template<typename T>
    class ReverseOrder {
    private:
        std::vector<T> dataCopy;  // Stores a copy of the original data

    public:
        // Nested iterator class
        class Iterator {
        private:
            const std::vector<T>* data;  // Pointer to the data
            size_t index;                // Current index (starting from the back)

        public:
            // Constructor
            Iterator(const std::vector<T>* data, size_t index)
                    : data(data), index(index) {
                if (!data) {
                    throw std::invalid_argument("Null data pointer passed to ReverseOrder iterator.");
                }
            }

            // Dereference operator
            const T& operator*() const {
                if (index >= data->size()) {
                    throw std::out_of_range("Dereferencing out of range in ReverseOrder.");
                }
                return data->at(data->size() - 1 - index);
            }

            // Pre-increment
            Iterator& operator++() {
                if (index >= data->size()) {
                    throw std::out_of_range("Cannot increment past the end in ReverseOrder.");
                }
                ++index;
                return *this;
            }

            // Inequality comparison
            bool operator!=(const Iterator& other) const {
                return index != other.index || data != other.data;
            }
        };

        // Constructor – makes a copy of the input vector
        ReverseOrder(const std::vector<T>& original)
                : dataCopy(original) {
            if (dataCopy.empty()) {
                throw std::invalid_argument("ReverseOrder cannot be created on an empty container.");
            }
        }

        // Begin iterator – starts from last element
        Iterator begin() const {
            return Iterator(&dataCopy, 0);
        }

        // End iterator – one past the first element
        Iterator end() const {
            return Iterator(&dataCopy, dataCopy.size());
        }
    };

} // namespace genericContainer

#endif // EX4_REVERSEORDER_HPP
