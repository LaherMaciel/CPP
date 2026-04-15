# CPP Module 06 - C++ Casts

## Overview

Module 06 covers the four C++ cast operators and when to use each one.

## Learning objectives

- `static_cast` — compile-time cast between compatible types
- `dynamic_cast` — safe downcast with runtime type checking (requires polymorphism)
- `reinterpret_cast` — low-level bit reinterpretation
- `const_cast` — add or remove const qualifier

## Exercises

| Exercise | Name | Key concepts |
|----------|------|-------------|
| ex00 | Conversion | Scalar type converter: int, char, float, double with edge cases |
| ex01 | Serialization | `reinterpret_cast` to serialize/deserialize a pointer as `uintptr_t` |
| ex02 | Identify real type | `dynamic_cast` to identify the concrete type of a polymorphic object |

## Compilation

```bash
cd ex00  # or ex01, ex02
make
```

Compiles with `-Wall -Wextra -Werror -std=c++98`.
