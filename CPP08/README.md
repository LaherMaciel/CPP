# CPP Module 08 - Templated Containers, Iterators & Algorithms

## Overview

Module 08 focuses on the C++ Standard Template Library — containers, iterators, and algorithms — and how to write code that works generically with them.

## Learning objectives

- STL containers: `std::vector`, `std::list`, `std::map`, `std::stack`
- Iterators and iterator categories
- STL algorithms (`std::find`, `std::sort`, etc.)
- Writing template functions that work with any conforming container

## Exercises

| Exercise | Name | Key concepts |
|----------|------|-------------|
| ex00 | Easy find | `easyfind` template: find a value in any integer container |
| ex01 | Span | `Span` class storing N integers, `shortestSpan`/`longestSpan` |
| ex02 | Mutated abomination | `MutantStack<T>`: stack with begin/end iterators |

## Compilation

```bash
cd ex00  # or ex01, ex02
make
```

Compiles with `-Wall -Wextra -Werror -std=c++98`.
