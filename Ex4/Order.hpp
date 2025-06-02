// roynaor10@gmail.com

#ifndef EX4_ORDER_HPP
#define EX4_ORDER_HPP

#include <vector>
#include <stdexcept>

namespace genericContainer {

    // Template class for iterating in the original order
    template<typename T>
    class Order {
    private:
        std::vector<T> dataCopy;  // Copy of original data for safe iteration

    public:
        // Nested iterator class
        class Iterator {
        private:
            const std::vector<T>* data;  // Pointer to data
            size_t index;                // Current index

        public:
            // Constructor
            Iterator(const std::vector<T>* data, size_t index)
                    : data(data), index(index) {
                if (!data) {
                    throw std::invalid_argument("Null data pointer passed to Order iterator.");
                }
            }

            // Dereference
            const T& operator*() const {
                if (index >= data->size()) {
                    throw std::out_of_range("Dereferencing out of bounds in Order.");
                }
                return data->at(index);
            }

            // Increment
            Iterator& operator++() {
                if (index >= data->size()) {
                    throw std::out_of_range("Cannot increment past the end in Order.");
                }
                ++index;
                return *this;
            }

            // Comparison
            bool operator!=(const Iterator& other) const {
                return index != other.index || data != other.data;
            }
        };

        // Constructor – makes a copy of original vector
        Order(const std::vector<T>& original)
                : dataCopy(original) {
            if (dataCopy.empty()) {
                throw std::invalid_argument("Cannot create Order on an empty container.");
            }
        }

        // Begin – iterator starting at index 0
        Iterator begin() const {
            return Iterator(&dataCopy, 0);
        }

        // End – iterator pointing past the last index
        Iterator end() const {
            return Iterator(&dataCopy, dataCopy.size());
        }
    };

} // namespace genericContainer

#endif // EX4_ORDER_HPP
