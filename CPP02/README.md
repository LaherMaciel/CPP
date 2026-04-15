# CPP Module 02 - Ad-hoc Polymorphism & Orthodox Canonical Form

## Overview

Module 02 introduces operator overloading and the Orthodox Canonical Form (OCF). The exercises build a fixed-point number class from scratch, progressively adding operators and conversions.

## Learning objectives

- Orthodox Canonical Form: default constructor, copy constructor, copy assignment operator, destructor
- Operator overloading (arithmetic, comparison, increment/decrement, stream insertion)
- Fixed-point number representation
- Deep vs shallow copy

## Exercises

| Exercise | Name | Key concepts |
|----------|------|-------------|
| ex00 | My First Class in Orthodox Canonical Form | OCF skeleton, fixed-point storage, `getRawBits`/`setRawBits` |
| ex01 | Towards a more useful fixed-point class | Int/float constructors, `toInt`/`toFloat`, `operator<<` |
| ex02 | Now we're talking | Comparison operators, arithmetic operators, increment/decrement, `min`/`max` statics |

## Compilation

```bash
cd ex00  # or ex01, ex02
make
```

Compiles with `-Wall -Wextra -Werror -std=c++98`.
