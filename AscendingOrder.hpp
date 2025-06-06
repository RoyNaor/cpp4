// roynaor10@gmail.com

#ifndef EX4_ASCENDINGORDER_HPP
#define EX4_ASCENDINGORDER_HPP

#include <vector>
#include <algorithm>
#include <stdexcept>

namespace genericContainer {

    // Template class for iterating through a container in ascending order
    template<typename T>
    class AscendingOrder {
    private:
        std::vector<T> sortedData; // Holds a sorted copy of the original data

    public:
        // Nested iterator class
        class Iterator {
        private:
            const std::vector<T>* data; // Pointer to the sorted data
            size_t index;               // Current index in the data

        public:
            // Constructor
            Iterator(const std::vector<T>* data, size_t index)
                    : data(data), index(index) {
                if (!data) {
                    throw std::invalid_argument("Null data pointer passed to Iterator.");
                }
            }

            // Dereference operator
            const T& operator*() const {
                if (index >= data->size()) {
                    throw std::out_of_range("Attempted to dereference out-of-bounds iterator.");
                }
                return data->at(index);
            }

            // Prefix increment (++it)
            Iterator& operator++() {
                if (index >= data->size()) {
                    throw std::out_of_range("Cannot increment beyond end of data.");
                }
                ++index;
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
                if (index == 0) {
                    throw std::out_of_range("Cannot decrement below zero.");
                }
                --index;
                return *this;
            }

            // Postfix decrement (it--)
            Iterator operator--(int) {
                Iterator temp = *this;
                --(*this);
                return temp;
            }

            // Indexing (it[n])
            const T& operator[](size_t offset) const {
                if (index + offset >= data->size()) {
                    throw std::out_of_range("Random access out of range.");
                }
                return data->at(index + offset);
            }

            // Add offset (it + n)
            Iterator operator+(int n) const {
                if (index + n > data->size()) {
                    throw std::out_of_range("Iterator + offset out of range.");
                }
                return Iterator(data, index + n);
            }

            // Subtract offset (it - n)
            Iterator operator-(int n) const {
                if (n > index) {
                    throw std::out_of_range("Iterator - offset out of range.");
                }
                return Iterator(data, index - n);
            }

            // Add and assign (it += n)
            Iterator& operator+=(int n) {
                if (index + n > data->size()) {
                    throw std::out_of_range("Iterator += out of range.");
                }
                index += n;
                return *this;
            }

            // Subtract and assign (it -= n)
            Iterator& operator-=(int n) {
                if (n > index) {
                    throw std::out_of_range("Iterator -= out of range.");
                }
                index -= n;
                return *this;
            }

            // Inequality comparison
            bool operator!=(const Iterator& other) const {
                return index != other.index || data != other.data;
            }

            // Equality comparison (optional)
            bool operator==(const Iterator& other) const {
                return index == other.index && data == other.data;
            }
        };

        // Constructor: copies and sorts the original data
        AscendingOrder(const std::vector<T>& original) {
            sortedData = original;
            std::sort(sortedData.begin(), sortedData.end());
        }

        // Returns an iterator to the beginning of the sorted data
        Iterator begin() const {
            return Iterator(&sortedData, 0);
        }

        // Returns an iterator to the end (one past the last element)
        Iterator end() const {
            return Iterator(&sortedData, sortedData.size());
        }
    };

} // namespace genericContainer

#endif // EX4_ASCENDINGORDER_HPP
