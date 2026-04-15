# CPP Module 07 - C++ Templates

## Overview

Module 07 introduces function and class templates, enabling type-generic code.

## Learning objectives

- Function template syntax and instantiation
- Class templates
- Template specialization
- Using templates with STL containers

## Exercises

| Exercise | Name | Key concepts |
|----------|------|-------------|
| ex00 | Start with a few functions | `swap`, `min`, `max` as function templates |
| ex01 | Iter | `iter` template that applies a function to every element of an array |
| ex02 | Array | `Array<T>` class template with bounds-checked subscript operator |

## Compilation

```bash
cd ex00  # or ex01, ex02
make
```

Compiles with `-Wall -Wextra -Werror -std=c++98`.
