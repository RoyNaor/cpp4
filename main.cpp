// roynaor10@gmail.com

#include <iostream>
#include "MyContainer.hpp"

using namespace genericContainer;

int main() {
    MyContainer<int> container;

    // Add elements to the container
    container.add(7);
    container.add(15);
    container.add(6);
    container.add(1);
    container.add(2);
    container.add(2);
    container.add(2);
    container.add(2);

    // Remove all instances of 2
    try {
        container.remove(2);
    } catch (const std::exception& e) {
        std::cerr << "Remove error: " << e.what() << std::endl;
    }

    // Print size of container
    std::cout << "Size of container: " << container.size() << std::endl;

    // Print container contents using operator<<
    std::cout << "Container: " << container << std::endl;


    // AscendingOrder iterator
    std::cout << "Ascending order: ";
    auto asc = container.ascendingOrder();
    for (auto it = asc.begin(); it != asc.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;


    // DescendingOrder iterator
    std::cout << "Descending order: ";
    auto desc = container.descendingOrder();
    for (auto it = desc.begin(); it != desc.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;


    // SideCrossOrder iterator
    std::cout << "Side-cross order: ";
    auto sideCross = container.sideCrossOrder();
    for (auto it = sideCross.begin(); it != sideCross.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;


   // ReverseOrder iterator
   auto reverse = container.reverseOrder();
    std::cout << "Reverse order: ";
    for (auto it = reverse.begin(); it != reverse.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;


    // Regular Order iterator
    auto normal = container.order();
    std::cout << "Regular order: ";
    for (auto it = normal.begin(); it != normal.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;


    // MiddleOutOrder iterator
    auto middle = container.middleOutOrder();
    std::cout << "Middle-out order: ";
    for (auto it = middle.begin(); it != middle.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
