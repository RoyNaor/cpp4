// test_mycontainer.cpp

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
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
CHECK(c.size() == 2);  // removed all 2's

CHECK_THROWS_AS(c.remove(2), std::runtime_error);
CHECK_THROWS_WITH(c.remove(99), "Element not found in container.");
}

TEST_CASE("Stream output formatting") {
MyContainer<int> c;
c.add(3);
c.add(1);
std::ostringstream oss;
oss << c;
CHECK(oss.str() == "[ 3 1 ]");
}

TEST_CASE("AscendingOrder basic and edge cases") {
MyContainer<int> c;
c.add(4);
c.add(1);
c.add(3);
auto asc = c.ascendingOrder();
CHECK_NOTHROW(*asc.begin());

MyContainer<int> empty;
CHECK_THROWS_AS(empty.ascendingOrder().begin(), std::out_of_range);  // manually deref

// Simulate out-of-bounds manually
auto it = asc.begin();
++it; ++it; ++it;
CHECK_THROWS_AS(*it, std::out_of_range);
}

TEST_CASE("DescendingOrder edge cases") {
MyContainer<int> c;
c.add(2);
c.add(1);
c.add(3);
auto desc = c.descendingOrder();
auto it = desc.begin();
++it; ++it; ++it;
CHECK_THROWS_AS(*it, std::out_of_range);

MyContainer<int> empty;
CHECK_THROWS_AS(empty.descendingOrder(), std::invalid_argument);
}

TEST_CASE("SideCrossOrder correct pattern and bounds") {
MyContainer<int> c;
c.add(10);
c.add(20);
c.add(30);
c.add(40);

auto it = SideCrossOrder<int>::begin(c.getData());
CHECK(*it == 10); ++it;
CHECK(*it == 40); ++it;
CHECK(*it == 20); ++it;
CHECK(*it == 30); ++it;

CHECK_THROWS_AS(*it, std::out_of_range);
CHECK_THROWS_AS(++it, std::out_of_range);

MyContainer<int> empty;
CHECK_THROWS_AS(SideCrossOrder<int>::begin(empty.getData()), std::invalid_argument);
}

TEST_CASE("ReverseOrder basic and exception") {
MyContainer<int> c;
c.add(1);
c.add(2);
auto rev = ReverseOrder<int>::begin(c.getData());
++rev; ++rev;
CHECK_THROWS_AS(*rev, std::out_of_range);

MyContainer<int> empty;
CHECK_THROWS_AS(ReverseOrder<int>::begin(empty.getData()), std::invalid_argument);
}

TEST_CASE("Order iterator normal and out-of-bounds") {
MyContainer<int> c;
c.add(9);
c.add(8);
auto it = Order<int>::begin(c.getData());
++it; ++it;
CHECK_THROWS_AS(*it, std::out_of_range);

MyContainer<int> empty;
CHECK_THROWS_AS(Order<int>::begin(empty.getData()), std::invalid_argument);
}

TEST_CASE("MiddleOutOrder logic and bounds") {
MyContainer<int> c;
c.add(0);
c.add(1);
c.add(2);
c.add(3);
c.add(4);
auto it = MiddleOutOrder<int>::begin(c.getData());
for (size_t i = 0; i < 5; ++i) ++it;
CHECK_THROWS_AS(*it, std::out_of_range);
CHECK_THROWS_AS(++it, std::out_of_range);

MyContainer<int> empty;
CHECK_THROWS_AS(MiddleOutOrder<int>::begin(empty.getData()), std::invalid_argument);
}
