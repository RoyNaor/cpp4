// roynaor10@gmail.com

#ifndef EX4_DESCENDINGORDER_HPP
#define EX4_DESCENDINGORDER_HPP

#include <vector>
#include <algorithm>
#include <stdexcept>

namespace genericContainer {

    // Template class for iterating through a container in descending order
    template<typename T>
    class DescendingOrder {
    private:
        std::vector<T> sortedData;  // Stores the elements sorted in descending order

    public:
        // Nested iterator class
        class Iterator {
        private:
            const std::vector<T>* data;  // Pointer to sorted vector
            size_t index;                // Current index

        public:
            // Constructor
            Iterator(const std::vector<T>* data, size_t index)
                    : data(data), index(index) {
                if (!data) {
                    throw std::invalid_argument("Null data pointer passed to Iterator.");
                }
            }

            // Dereference operator – returns current element
            const T& operator*() const {
                if (index >= data->size()) {
                    throw std::out_of_range("Attempted to dereference out-of-bounds iterator.");
                }
                return data->at(index);
            }

            // Increment operator – moves to next element
            Iterator& operator++() {
                if (index >= data->size()) {
                    throw std::out_of_range("Cannot increment past the end.");
                }
                ++index;
                return *this;
            }

            // Comparison operator – checks if iterators are different
            bool operator!=(const Iterator& other) const {
                return index != other.index || data != other.data;
            }
        };

        // Constructor: copy and sort descending
        DescendingOrder(const std::vector<T>& original) {
            sortedData = original;
            std::sort(sortedData.begin(), sortedData.end(), std::greater<T>());
        }

        // Begin iterator – points to the first (largest) element
        Iterator begin() const {
            return Iterator(&sortedData, 0);
        }

        // End iterator – points one past the last (smallest) element
        Iterator end() const {
            return Iterator(&sortedData, sortedData.size());
        }
    };

} // namespace genericContainer

#endif // EX4_DESCENDINGORDER_HPP
