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

            // Dereference operator
            const T& operator*() const {
                if (index >= data->size()) {
                    throw std::out_of_range("Dereferencing out of bounds in Order.");
                }
                return data->at(index);
            }

            // Prefix increment (++it)
            Iterator& operator++() {
                if (index >= data->size()) {
                    throw std::out_of_range("Cannot increment beyond end in Order.");
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
                    throw std::out_of_range("Cannot decrement before beginning in Order.");
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

            // Random access: it[n]
            const T& operator[](size_t offset) const {
                if (index + offset >= data->size()) {
                    throw std::out_of_range("Random access out of bounds in Order.");
                }
                return data->at(index + offset);
            }

            // it + n
            Iterator operator+(int n) const {
                if (index + n > data->size()) {
                    throw std::out_of_range("Iterator + offset out of range.");
                }
                return Iterator(data, index + n);
            }

            // it - n
            Iterator operator-(int n) const {
                if (n > index) {
                    throw std::out_of_range("Iterator - offset out of range.");
                }
                return Iterator(data, index - n);
            }

            // it += n
            Iterator& operator+=(int n) {
                if (index + n > data->size()) {
                    throw std::out_of_range("Iterator += out of range.");
                }
                index += n;
                return *this;
            }

            // it -= n
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

            // Equality comparison
            bool operator==(const Iterator& other) const {
                return index == other.index && data == other.data;
            }
        };

        // Constructor – makes a copy of the original vector
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

        // End – iterator pointing one past the last index
        Iterator end() const {
            return Iterator(&dataCopy, dataCopy.size());
        }
    };

} // namespace genericContainer

#endif // EX4_ORDER_HPP
