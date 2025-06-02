CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Target executable names
TARGET = main
TEST_EXEC = tests

# Source files
SRCS = main.cpp MyContainer.tpp
HEADERS = MyContainer.hpp \
          AscendingOrder.hpp DescendingOrder.hpp \
          SideCrossOrder.hpp ReverseOrder.hpp \
          Order.hpp MiddleOutOrder.hpp

TEST_SRC = test.cpp
OBJS = $(SRCS:.cpp=.o)
TEST_OBJ = $(TEST_SRC:.cpp=.o)

# Default target builds main app and tests
all: $(TARGET) $(TEST_EXEC)

# Build main executable (optional if you have a main.cpp)
$(TARGET): main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp

# Build test binary
$(TEST_EXEC): $(TEST_SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TEST_EXEC) $(TEST_SRC)

# Run valgrind memory check on tests
valgrind: $(TEST_EXEC)
	valgrind --leak-check=full --track-origins=yes ./$(TEST_EXEC)

# Run the test suite
test: $(TEST_EXEC)
	./$(TEST_EXEC)

# Clean object and binary files
clean:
	rm -f $(TARGET) $(TEST_EXEC) *.o

.PHONY: all test valgrind clean
