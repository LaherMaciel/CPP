# CPP Module 09 - STL

## Overview

Module 09 applies everything learned about the STL to solve concrete algorithmic problems. Each exercise mandates a different container type.

## Learning objectives

- Choosing the right STL container for the task
- `std::stack` for expression evaluation
- `std::map` for key-value lookups
- `std::deque`/`std::list` for the Ford-Johnson merge-insert sort

## Exercises

| Exercise | Name | Key concepts |
|----------|------|-------------|
| ex00 | Bitcoin Exchange | `std::map` — parse a CSV database, look up closest past date |
| ex01 | Reverse Polish Notation | `std::stack` — evaluate an RPN expression |
| ex02 | PmergeMe | Ford-Johnson merge-insert sort with two different containers, compare performance |

## Compilation

```bash
cd ex00  # or ex01, ex02
make
```

Compiles with `-Wall -Wextra -Werror -std=c++98`.
