# CPP Module 00 - C++ Fundamentals

## Overview

Module 00 introduces the fundamental concepts of C++ programming, focusing on object-oriented programming basics and the C++98 standard.

## Learning objectives

- C++ namespaces and standard I/O streams
- Class definition, member functions, and access specifiers
- Constructors and destructors
- Static member variables and functions
- Const correctness
- Encapsulation and basic OOP principles

## Exercises

| Exercise | Name | Key concepts |
|----------|------|-------------|
| ex00 | Megaphone | `std::cout`, `std::toupper`, command-line arguments |
| ex01 | My Awesome PhoneBook | Classes, encapsulation, `std::getline`, `std::setw`, circular buffer |
| ex02 | The Job Of Your Dreams | Static members, const member functions, `localtime()`, matching a spec |

## Compilation

```bash
cd ex00  # or ex01, ex02
make
```

Compiles with `-Wall -Wextra -Werror -std=c++98`.
