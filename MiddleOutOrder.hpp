// roynaor10@gmail.com

#ifndef EX4_MIDDLEOUTORDER_HPP
#define EX4_MIDDLEOUTORDER_HPP

#include <vector>
#include <stdexcept>

namespace genericContainer {

    // Template class for iterating from the middle outwards in zigzag
    template<typename T>
    class MiddleOutOrder {
    private:
        std::vector<T> dataCopy;  // Copy of the original container

    public:
        // Iterator nested class
        class Iterator {
        private:
            const std::vector<T>* data;  // Pointer to the data
            size_t total;                // Total elements in the data
            size_t count;                // Elements visited so far
            size_t middle;              // Middle index
            int left;                   // Left side iterator
            size_t right;               // Right side iterator
            bool leftTurn;              // Indicates which side to visit next

        public:
            // Constructor
            Iterator(const std::vector<T>* data, bool atEnd = false)
                    : data(data),
                      total(data ? data->size() : 0),
                      count(0),
                      middle(data ? data->size() / 2 : 0),
                      left(static_cast<int>(middle) - 1),
                      right(middle + 1),
                      leftTurn(true) {
                if (!data || data->empty()) {
                    throw std::invalid_argument("MiddleOutOrder cannot be used on an empty container.");
                }
                if (atEnd) {
                    count = total;  // Mark as finished
                }
            }

            // Dereference – get current element
            const T& operator*() const {
                if (count >= total) {
                    throw std::out_of_range("Iterator out of bounds in MiddleOutOrder.");
                }
                if (count == 0) {
                    return data->at(middle);  // First visit is middle
                }
                if (leftTurn && left >= 0) {
                    return data->at(left);
                }
                if (!leftTurn && right < data->size()) {
                    return data->at(right);
                }
                throw std::out_of_range("Invalid access in MiddleOutOrder iterator.");
            }

            // Prefix increment (++it)
            Iterator& operator++() {
                ++count;
                if (count == 1) return *this;  // Skip toggle on first middle step

                if (leftTurn && left >= 0) {
                    --left;
                } else if (!leftTurn && right < data->size()) {
                    ++right;
                }

                leftTurn = !leftTurn;
                return *this;
            }

            // Postfix increment (it++)
            Iterator operator++(int) {
                Iterator temp = *this;
                ++(*this);
                return temp;
            }

            // Comparison for inequality
            bool operator!=(const Iterator& other) const {
                return count != other.count || data != other.data;
            }

            // Comparison for equality
            bool operator==(const Iterator& other) const {
                return count == other.count && data == other.data;
            }
        };

        // Constructor – copy original data
        MiddleOutOrder(const std::vector<T>& original)
                : dataCopy(original) {
            if (dataCopy.empty()) {
                throw std::invalid_argument("Cannot create MiddleOutOrder on an empty container.");
            }
        }

        // Begin iterator
        Iterator begin() const {
            return Iterator(&dataCopy);
        }

        // End iterator
        Iterator end() const {
            return Iterator(&dataCopy, true);
        }
    };

} // namespace genericContainer

#endif // EX4_MIDDLEOUTORDER_HPP
