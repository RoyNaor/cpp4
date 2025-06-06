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

            // Prefix increment – move forward (toward smaller elements)
            Iterator& operator++() {
                if (index >= data->size()) {
                    throw std::out_of_range("Cannot increment past the end.");
                }
                ++index;
                return *this;
            }

            // Postfix increment
            Iterator operator++(int) {
                Iterator temp = *this;
                ++(*this);
                return temp;
            }

            // Prefix decrement – move backward
            Iterator& operator--() {
                if (index == 0) {
                    throw std::out_of_range("Cannot decrement below 0.");
                }
                --index;
                return *this;
            }

            // Postfix decrement
            Iterator operator--(int) {
                Iterator temp = *this;
                --(*this);
                return temp;
            }

            // Random access via index offset
            const T& operator[](size_t offset) const {
                if (index + offset >= data->size()) {
                    throw std::out_of_range("Random access out of range.");
                }
                return data->at(index + offset);
            }

            // Iterator + offset
            Iterator operator+(int n) const {
                if (index + n > data->size()) {
                    throw std::out_of_range("Iterator + offset out of range.");
                }
                return Iterator(data, index + n);
            }

            // Iterator - offset
            Iterator operator-(int n) const {
                if (n > index) {
                    throw std::out_of_range("Iterator - offset out of range.");
                }
                return Iterator(data, index - n);
            }

            // Iterator += offset
            Iterator& operator+=(int n) {
                if (index + n > data->size()) {
                    throw std::out_of_range("Iterator += out of range.");
                }
                index += n;
                return *this;
            }

            // Iterator -= offset
            Iterator& operator-=(int n) {
                if (n > index) {
                    throw std::out_of_range("Iterator -= out of range.");
                }
                index -= n;
                return *this;
            }

            // Inequality comparison – used in loops
            bool operator!=(const Iterator& other) const {
                return index != other.index || data != other.data;
            }

            // Equality comparison (optional)
            bool operator==(const Iterator& other) const {
                return index == other.index && data == other.data;
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
