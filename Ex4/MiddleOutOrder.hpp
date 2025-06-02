// roynaor10@gmail.com

#ifndef EX4_MIDDLEOUTORDER_HPP
#define EX4_MIDDLEOUTORDER_HPP

#include <vector>
#include <stdexcept>

namespace genericContainer {

    // Template class for iterating from the middle outwards
    template<typename T>
    class MiddleOutOrder {
    private:
        std::vector<T> dataCopy;

    public:
        // Nested Iterator class
        class Iterator {
        private:
            const std::vector<T>* data;
            size_t total;
            size_t count;
            size_t middle;
            int left;
            size_t right;
            bool leftTurn;

        public:
            // Constructor
            Iterator(const std::vector<T>* data, bool atEnd = false)
                    : data(data), total(data->size()), count(0),
                      middle(data->size() / 2),
                      left(static_cast<int>(middle) - 1),
                      right(middle + 1), leftTurn(true) {
                if (!data || data->empty()) {
                    throw std::invalid_argument("MiddleOutOrder cannot be used on an empty container.");
                }
                if (atEnd) {
                    count = total;
                }
            }

            // Dereference – return current element in zigzag order
            const T& operator*() const {
                if (count >= total) {
                    throw std::out_of_range("Iterator is out of bounds.");
                }
                if (count == 0) {
                    return data->at(middle);
                }
                if (leftTurn && left >= 0) {
                    return data->at(left);
                }
                if (!leftTurn && right < data->size()) {
                    return data->at(right);
                }
                throw std::out_of_range("Iterator is out of bounds (invalid state).");
            }

            // Increment – zigzag traversal from middle outward
            Iterator& operator++() {
                ++count;
                if (count == 1) return *this;

                if (leftTurn && left >= 0) {
                    --left;
                } else if (!leftTurn && right < data->size()) {
                    ++right;
                }

                leftTurn = !leftTurn;
                return *this;
            }

            // Comparison
            bool operator!=(const Iterator& other) const {
                return count != other.count || data != other.data;
            }
        };

        // Constructor – makes a copy of the data for stable iteration
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
