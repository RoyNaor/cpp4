#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "MyContainer.hpp"

using namespace genericContainer;

TEST_CASE("Add and size") {
    MyContainer<int> c;
    CHECK(c.size() == 0);
    c.add(5);
    c.add(10);
    CHECK(c.size() == 2);
}

TEST_CASE("Remove existing and non-existing elements") {
    MyContainer<int> c;
    c.add(1);
    c.add(2);
    c.add(2);
    c.add(3);
    c.remove(2);
    CHECK(c.size() == 2);

    CHECK_THROWS_AS(c.remove(2), std::invalid_argument);
    CHECK_THROWS_WITH(c.remove(99), "Item not found in container.");
}

TEST_CASE("Stream output formatting") {
    MyContainer<int> c;
    c.add(3);
    c.add(1);
    std::ostringstream oss;
    oss << c;
    CHECK(oss.str() == "[ 3 1 ]");
}

TEST_CASE("AscendingOrder iteration") {
    MyContainer<int> c;
    c.add(4);
    c.add(1);
    c.add(3);
    auto asc = c.ascendingOrder();

    std::vector<int> result;
    for (auto it = asc.begin(); it != asc.end(); ++it) {
        result.push_back(*it);
    }
    CHECK(result == std::vector<int>{1, 3, 4});
}

TEST_CASE("AscendingOrder empty container dereference throws") {
    MyContainer<int> empty;
    auto asc = empty.ascendingOrder();
    auto it = asc.begin();
    CHECK_THROWS_AS(*it, std::out_of_range); 
}


TEST_CASE("DescendingOrder iteration") {
    MyContainer<int> c;
    c.add(2);
    c.add(1);
    c.add(3);
    auto desc = c.descendingOrder();

    std::vector<int> result;
    for (auto it = desc.begin(); it != desc.end(); ++it) {
        result.push_back(*it);
    }
    CHECK(result == std::vector<int>{3, 2, 1});
}

TEST_CASE("SideCrossOrder iteration") {
    MyContainer<int> c;
    c.add(10);
    c.add(20);
    c.add(30);
    c.add(40);

    auto sc = c.sideCrossOrder();
    std::vector<int> result;
    for (auto it = sc.begin(); it != sc.end(); ++it) {
        result.push_back(*it);
    }
    CHECK(result == std::vector<int>{10, 40, 20, 30});
}

TEST_CASE("ReverseOrder iteration") {
    MyContainer<int> c;
    c.add(1);
    c.add(2);
    c.add(3);

    auto rev = c.reverseOrder();
    std::vector<int> result;
    for (auto it = rev.begin(); it != rev.end(); ++it) {
        result.push_back(*it);
    }
    CHECK(result == std::vector<int>{3, 2, 1});

    MyContainer<int> empty;
    CHECK_THROWS_AS(empty.reverseOrder(), std::invalid_argument);
}

TEST_CASE("Order iteration") {
    MyContainer<int> c;
    c.add(9);
    c.add(8);
    c.add(7);

    auto o = c.order();
    std::vector<int> result;
    for (auto it = o.begin(); it != o.end(); ++it) {
        result.push_back(*it);
    }
    CHECK(result == std::vector<int>{9, 8, 7});

    MyContainer<int> empty;
    CHECK_THROWS_AS(empty.order(), std::invalid_argument);
}

TEST_CASE("MiddleOutOrder iteration") {
    MyContainer<int> c;
    c.add(0);
    c.add(1);
    c.add(2);
    c.add(3);
    c.add(4);

    auto m = c.middleOutOrder();
    std::vector<int> result;
    for (auto it = m.begin(); it != m.end(); ++it) {
        result.push_back(*it);
    }
    CHECK(result == std::vector<int>{2, 1, 3, 0, 4});

    MyContainer<int> empty;
    CHECK_THROWS_AS(empty.middleOutOrder(), std::invalid_argument);
}

TEST_CASE("MyContainer<double> basic operations") {
    MyContainer<double> c;
    c.add(1.1);
    c.add(2.2);
    c.add(3.3);
    CHECK(c.size() == 3);

    std::ostringstream oss;
    oss << c;
    CHECK(oss.str() == "[ 1.1 2.2 3.3 ]");

    auto asc = c.ascendingOrder();
    std::vector<double> expected = {1.1, 2.2, 3.3};
    size_t i = 0;
    for (auto it = asc.begin(); it != asc.end(); ++it) {
        CHECK(doctest::Approx(*it) == expected[i++]); // floating-point comparison
    }
}

TEST_CASE("MyContainer<char> basic operations and order") {
    MyContainer<char> c;
    c.add('z');
    c.add('a');
    c.add('m');
    CHECK(c.size() == 3);

    std::ostringstream oss;
    oss << c;
    CHECK(oss.str() == "[ z a m ]");

    auto desc = c.descendingOrder();
    std::vector<char> expected = {'z', 'm', 'a'};
    size_t i = 0;
    for (auto it = desc.begin(); it != desc.end(); ++it) {
        CHECK(*it == expected[i++]);
    }

    auto sc = c.sideCrossOrder();
    std::vector<char> expectedCross = {'a', 'z', 'm'}; // sorted: a, m, z
    i = 0;
    for (auto it = sc.begin(); it != sc.end(); ++it) {
        CHECK(*it == expectedCross[i++]);
    }
}

