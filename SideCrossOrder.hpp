// roynaor10@gmail.com

#ifndef EX4_SIDECROSSORDER_HPP
#define EX4_SIDECROSSORDER_HPP

#include <vector>
#include <algorithm>
#include <stdexcept>

namespace genericContainer {

    // Template class for iterating through a container in "side-cross" order:
    // leftmost, rightmost, next-left, next-right, etc.
    template<typename T>
    class SideCrossOrder {
    private:
        std::vector<T> sortedData;  // Sorted data to iterate over

    public:
        // Nested iterator class
        class Iterator {
        private:
            const std::vector<T>* data;  // Pointer to the sorted vector
            size_t left;                 // Left index
            size_t right;                // Right index
            bool leftTurn;              // Indicates whether it's left's turn
            size_t count;               // How many elements have been returned

        public:
            // Constructor
            Iterator(const std::vector<T>* data, bool end = false)
                    : data(data),
                      left(0),
                      right(data ? data->size() - 1 : 0),
                      leftTurn(true),
                      count(0) {
                if (!data) {
                    throw std::invalid_argument("Null data pointer passed to SideCrossOrder iterator.");
                }
                if (end) {
                    count = data->size();  // force end condition
                }
            }

            // Dereference operator
            const T& operator*() const {
                if (count >= data->size()) {
                    throw std::out_of_range("Dereferencing out of range in SideCrossOrder.");
                }
                return leftTurn ? data->at(left) : data->at(right);
            }

            // Pre-increment
            Iterator& operator++() {
                if (count >= data->size()) {
                    throw std::out_of_range("Increment past end in SideCrossOrder.");
                }

                if (leftTurn) {
                    ++left;
                } else {
                    if (right == 0) right = -1; // avoid underflow
                    else --right;
                }

                leftTurn = !leftTurn;
                ++count;
                return *this;
            }

            // Inequality comparison
            bool operator!=(const Iterator& other) const {
                return count != other.count || data != other.data;
            }
        };

        // Constructor: sort data
        SideCrossOrder(const std::vector<T>& original) {
            sortedData = original;
            std::sort(sortedData.begin(), sortedData.end());
        }

        // Begin iterator
        Iterator begin() const {
            return Iterator(&sortedData);
        }

        // End iterator
        Iterator end() const {
            return Iterator(&sortedData, true);
        }
    };

} // namespace genericContainer

#endif // EX4_SIDECROSSORDER_HPP
