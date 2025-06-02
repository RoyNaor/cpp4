# 🧠 MyContainer – Custom C++ Templated Container with Advanced Iterators

Author: [Roy Naor](mailto:roynaor10@gmail.com)  
License: MIT  
Language: C++17  
Build System: Make

---

## 📦 Project Overview

`MyContainer<T>` is a generic C++ container class that supports standard operations like `add`, `remove`, and iteration, while providing a variety of **custom iteration orders**, including:

- 🔼 Ascending Order
- 🔽 Descending Order
- 🔀 Side-Cross Order (zigzag from ends inward)
- 🔁 Reverse Order (from last to first)
- 📏 Regular Order (insertion order)
- 🧲 Middle-Out Order (from center outwards)

This project demonstrates advanced C++ concepts such as:

- Templates
- Custom iterators
- Exception safety
- Separation of interface and implementation (`.hpp` / `.tpp`)
- Unit testing using `doctest`
- Memory leak detection with `valgrind`

---

## 📂 File Structure

```
.
├── Makefile
├── main.cpp
├── test.cpp
├── MyContainer.hpp / MyContainer.tpp
├── [Iterator Files...]
│   ├── AscendingOrder.hpp
│   ├── DescendingOrder.hpp
│   ├── SideCrossOrder.hpp
│   ├── ReverseOrder.hpp
│   ├── Order.hpp
│   └── MiddleOutOrder.hpp
```

---

## 🛠️ Build Instructions

Make sure you have `g++` and `make` installed. Then simply run:

```bash
make
```

This will compile both:
- `main` – a demo file to run and observe all iterator outputs.
- `tests` – unit tests using doctest.

---

## 🚀 Run

### Run the demo:
```bash
./main
```

### Run the tests:
```bash
./tests
```

---

## 🔍 Memory Leak Check

Run the executable with `valgrind` to ensure there are no memory leaks:

```bash
make valgrind
```

Or manually:

```bash
valgrind --leak-check=full --track-origins=yes ./main
```

---

## ✅ Unit Tests

All functionality and iterators are tested using the `doctest` framework. The tests cover:

- Element addition/removal
- Output formatting
- All iterators (including edge cases and exceptions)
- Template usage with `int`, `char`, and `double`

To run the tests:

```bash
./tests
```

---

## ⚠️ Exception Safety

All iterators throw appropriate exceptions when:

- Attempting to dereference past the end
- Constructed on empty containers (if logic requires it)
- Advancing beyond valid bounds

---

## 💡 Example Output

```bash
Size of container: 4
Container: [ 7 15 6 1 ]
Ascending order: 1 6 7 15
Descending order: 15 7 6 1
Side-cross order: 1 15 6 7
Reverse order: 1 6 15 7
Regular order: 7 15 6 1
Middle-out order: 6 15 1 7
```

---

## 🧪 Tested Types

- `MyContainer<int>`
- `MyContainer<char>`
- `MyContainer<double>`

Use it with any comparable type!

---

## 📝 License

MIT License. Free to use, distribute, and modify.

---
