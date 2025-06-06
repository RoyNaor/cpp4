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

TEST_CASE("Order iterator prefix/postfix increment") {
    MyContainer<int> c;
    c.add(5);
    c.add(10);

    auto order = c.order();
    auto it = order.begin();

    CHECK(*it == 5);
    auto it2 = it++;
    CHECK(*it2 == 5);     // Postfix returns old position
    CHECK(*it == 10);     // Iterator now moved forward

    --it;  // Going back to previous value
    CHECK(*it == 5);
}

TEST_CASE("Order iterator copy and equality") {
    MyContainer<int> c;
    c.add(1);
    c.add(2);
    c.add(3);

    auto order = c.order();
    auto it1 = order.begin();
    auto it2 = it1;

    CHECK(it1 != order.end());
    CHECK(it1 != order.begin() + 1); // should not be equal after advancing
    CHECK(*it1 == *it2);

    ++it1;
    CHECK(*it1 != *it2);
}

TEST_CASE("Order iterator throws when incremented out of bounds") {
    MyContainer<int> c;
    c.add(42);

    auto order = c.order();
    auto it = order.begin();

    CHECK_NOTHROW(*it);
    ++it;
    CHECK_THROWS_AS(*it, std::out_of_range);
    CHECK_THROWS_AS(++it, std::out_of_range);
}

TEST_CASE("Order iterator with char") {
    MyContainer<char> c;
    c.add('x');
    c.add('y');

    auto order = c.order();
    std::vector<char> expected = {'x', 'y'};
    size_t i = 0;
    for (auto it = order.begin(); it != order.end(); ++it) {
        CHECK(*it == expected[i++]);
    }
}

TEST_CASE("Order iterator with double") {
    MyContainer<double> c;
    c.add(3.3);
    c.add(4.4);

    auto order = c.order();
    std::vector<double> expected = {3.3, 4.4};
    size_t i = 0;
    for (auto it = order.begin(); it != order.end(); ++it) {
        CHECK(doctest::Approx(*it) == expected[i++]);
    }
}

TEST_CASE("Order iterator bracket access []") {
    MyContainer<int> c;
    c.add(100);
    c.add(200);
    c.add(300);

    auto order = c.order();
    auto it = order.begin();

    CHECK(it[0] == 100);
    CHECK(it[1] == 200);
    CHECK(it[2] == 300);

    CHECK_THROWS_AS(it[3], std::out_of_range);
}
