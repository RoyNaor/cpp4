// roynaor10@gmail.com

#ifndef MYCONTAINER_HPP
#define MYCONTAINER_HPP

#include <iostream>
#include <vector>
#include <stdexcept>
#include "AscendingOrder.hpp"
#include "DescendingOrder.hpp"
#include "SideCrossOrder.hpp"
#include "ReverseOrder.hpp"
#include "Order.hpp"
#include "MiddleOutOrder.hpp"

namespace genericContainer {

    template<typename T = int>
    class MyContainer {
    private:
        std::vector<T> data;

    public:
        void add(const T& item);
        void remove(const T& item);
        size_t size() const;

        template<typename U>
        friend std::ostream& operator<<(std::ostream& os, const MyContainer<U>& container);

        AscendingOrder<T> ascendingOrder() const {
            return AscendingOrder<T>(data);
        }

        DescendingOrder<T> descendingOrder() const {
            return DescendingOrder<T>(data);
        }

        SideCrossOrder<T> sideCrossOrder() const {
            return SideCrossOrder<T>(data);
        }

        ReverseOrder<T> reverseOrder() const {
            return ReverseOrder<T>(data);
        }

        Order<T> order() const {
            return Order<T>(data);
        }


        MiddleOutOrder<T> middleOutOrder() const {
            return MiddleOutOrder<T>(data);
        }
    };

} // namespace genericContainer

#include "MyContainer.tpp"

#endif // MYCONTAINER_HPP
