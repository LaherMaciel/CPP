# CPP Module 01 - Memory Allocation & References

## Overview

Module 01 covers memory management, references, pointers to member functions, and the switch statement. Builds on the OOP fundamentals from Module 00.

## Learning Objectives

- Dynamic memory allocation with `new` and `delete`
- Array allocation with `new[]` and `delete[]`
- References and their differences from pointers
- Pointers to member functions
- Switch statement usage

## Exercise Structure

```
CPP01/
├── ex00/    # BraiiiiiiinnnzzzZ (stack vs heap)
├── ex01/    # Moar brainz! (zombie horde, new[])
├── ex02/    # HI THIS IS BRAIN (references vs pointers)
├── ex03/    # Unnecessary violence (references in classes)
├── ex04/    # Sed is for losers (file string replacement)
├── ex05/    # Harl 2.0 (pointers to member functions)
├── ex06/    # Harl filter (switch statement)
└── README.md
```

## Exercises

### Exercise 00: BraiiiiiiinnnzzzZ
- **Focus**: Stack vs heap allocation, `new`/`delete`
- **Concepts**: Object lifetime, standalone functions, memory management

### Exercise 01: Moar brainz!
- **Focus**: Allocating arrays of objects on the heap
- **Concepts**: `new[]`, `delete[]`, zombie horde

### Exercise 02: HI THIS IS BRAIN
- **Focus**: References vs pointers
- **Concepts**: `&` reference syntax, address comparison

### Exercise 03: Unnecessary violence
- **Focus**: Using references in class design
- **Concepts**: When to use references vs pointers as members

### Exercise 04: Sed is for losers
- **Focus**: File I/O and string manipulation
- **Concepts**: `std::ifstream`, `std::ofstream`, string replacement without `std::string::replace`

### Exercise 05: Harl 2.0
- **Focus**: Pointers to member functions
- **Concepts**: Function pointer syntax, avoiding if/else chains

### Exercise 06: Harl filter
- **Focus**: Switch statement
- **Concepts**: `switch`/`case`, fall-through behavior

## Compilation

```bash
cd ex00  # or ex01, ex02, etc.
make
```

Compiles with `-Wall -Wextra -Werror -std=c++98`.

## Progress

- [x] Exercise 00: BraiiiiiiinnnzzzZ
- [ ] Exercise 01: Moar brainz!
- [ ] Exercise 02: HI THIS IS BRAIN
- [ ] Exercise 03: Unnecessary violence
- [ ] Exercise 04: Sed is for losers
- [ ] Exercise 05: Harl 2.0
- [ ] Exercise 06: Harl filter

## Next Module

After completing Module 01, move on to [CPP Module 02](../CPP02/README.md) which covers ad-hoc polymorphism, operator overloading, and Orthodox Canonical Form.

---

**Status**: In Progress
