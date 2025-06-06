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
            const std::vector<T>* data;
            size_t left;
            size_t right;
            bool leftTurn;
            size_t count;

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
                    count = data->size();  // mark as finished
                }
            }

            // Dereference operator
            const T& operator*() const {
                if (count >= data->size()) {
                    throw std::out_of_range("Dereferencing out of range in SideCrossOrder.");
                }
                return leftTurn ? data->at(left) : data->at(right);
            }

            // Prefix increment (++it)
            Iterator& operator++() {
                if (count >= data->size()) {
                    throw std::out_of_range("Increment past end in SideCrossOrder.");
                }
                if (leftTurn) {
                    ++left;
                } else {
                    if (right == 0) right = -1; // avoid unsigned underflow
                    else --right;
                }
                leftTurn = !leftTurn;
                ++count;
                return *this;
            }

            // Postfix increment (it++)
            Iterator operator++(int) {
                Iterator temp = *this;
                ++(*this);
                return temp;
            }

            // Prefix decrement (--it)
            Iterator& operator--() {
                if (count == 0) {
                    throw std::out_of_range("Cannot decrement before beginning.");
                }

                --count;
                leftTurn = !leftTurn;
                if (!leftTurn) {
                    --left;
                } else {
                    ++right;
                }
                return *this;
            }

            // Postfix decrement (it--)
            Iterator operator--(int) {
                Iterator temp = *this;
                --(*this);
                return temp;
            }

            // Random access (it[n])
            const T& operator[](size_t offset) const {
                if (count + offset >= data->size()) {
                    throw std::out_of_range("Random access out of range.");
                }

                // Simulate the zigzag pattern for index + offset
                size_t virtualCount = count + offset;
                bool even = (virtualCount % 2 == 0);
                size_t pos = virtualCount / 2;
                return even ? data->at(pos) : data->at(data->size() - 1 - pos);
            }

            // Jump forward
            Iterator operator+(int n) const {
                Iterator result = *this;
                result += n;
                return result;
            }

            // Jump backward
            Iterator operator-(int n) const {
                Iterator result = *this;
                result -= n;
                return result;
            }

            // Add and assign
            Iterator& operator+=(int n) {
                for (int i = 0; i < n; ++i) ++(*this);
                return *this;
            }

            // Subtract and assign
            Iterator& operator-=(int n) {
                for (int i = 0; i < n; ++i) --(*this);
                return *this;
            }

            // Inequality comparison
            bool operator!=(const Iterator& other) const {
                return count != other.count || data != other.data;
            }

            // Equality comparison
            bool operator==(const Iterator& other) const {
                return count == other.count && data == other.data;
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
