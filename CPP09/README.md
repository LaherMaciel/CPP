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

## Understanding Ford-Johnson (ex02)

The merge-insert sort is the hardest part of this module, and the part most
explanations skip is the *insertion order* of the smaller elements — not the
pairing, which is the easy half.

**[FORD_JOHNSON.md](FORD_JOHNSON.md)** — the algorithm worked through step by
step on nine numbers, with the Jacobsthal insertion order explained by counting
comparisons both ways.

Three things it clears up:

- The recursion runs on the **larger** element of each pair only. The smaller
  ones are set aside and inserted at the end — this is what makes it *not*
  merge sort.
- Each smaller element must stay **linked to its partner** through the
  recursion. Losing that link is the most common implementation bug.
- The b's go back in **Jacobsthal order** (1, 3, 2, 5, 4, 11, 10, 9, 8, 7, 6 …),
  which makes every binary search land on a `2^k - 1` range. Inserting them in
  plain order still sorts correctly — it just costs more comparisons, and that
  is the only thing distinguishing Ford-Johnson from "pair up and binary insert".
