# CPP Module 00 - C++ Fundamentals

## Overview

Module 00 introduces the fundamental concepts of C++ programming, focusing on object-oriented programming basics and the C++98 standard.

## Learning Objectives

- C++ namespaces and standard I/O streams
- Class definition, member functions, and access specifiers
- Constructors and destructors
- Static member variables and functions
- Const correctness
- Encapsulation and basic OOP principles

## Exercise Structure

```
CPP00/
├── ex00/    # Megaphone
├── ex01/    # My Awesome PhoneBook
├── ex02/    # The Job Of Your Dreams
└── README.md
```

## Exercises

### Exercise 00: Megaphone
- **Focus**: Basic string manipulation and standard output
- **Concepts**: `std::cout`, `std::toupper`, command-line arguments

### Exercise 01: My Awesome PhoneBook
- **Focus**: Class design and user interaction
- **Concepts**: Classes (Contact, PhoneBook), encapsulation, getters/setters, `std::getline`, `std::setw`, input validation, circular buffer logic

### Exercise 02: The Job Of Your Dreams
- **Focus**: Recreating a class implementation from a provided header and test file
- **Concepts**: Static members, const member functions, destructors, `localtime()`, file-scope static functions, matching output to specification

## Compilation

```bash
cd ex00  # or ex01, ex02
make
```

Compiles with `-Wall -Wextra -Werror -std=c++98`.

## Progress

- [x] Exercise 00: Megaphone
- [x] Exercise 01: My Awesome PhoneBook
- [x] Exercise 02: The Job Of Your Dreams

## Next Module

After completing Module 00, move on to [CPP Module 01](../CPP01/README.md) which covers memory allocation, references, pointers to members, and the switch statement.

---

**Status**: Complete
