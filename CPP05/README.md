# CPP Module 05 - Exceptions

## Overview

Module 05 introduces exception handling in C++. The exercises model a bureaucratic system where operations can fail and must throw typed exceptions.

## Learning objectives

- `try`/`catch`/`throw` mechanics
- Custom exception classes derived from `std::exception`
- Exception safety and resource cleanup
- Nested exception classes

## Exercises

| Exercise | Name | Key concepts |
|----------|------|-------------|
| ex00 | Mommy, when I grow up, I want to be a bureaucrat! | Bureaucrat class, grade validation, `GradeTooHighException`/`GradeTooLowException` |
| ex01 | Form up, maggots! | Form class, signing with grade checks |
| ex02 | No, you need form 28B, not 28C | Concrete form subclasses, execution |
| ex03 | At least this beats coffee-making | Intern class that creates forms by name |

## Compilation

```bash
cd ex00  # or ex01, ex02, ex03
make
```

Compiles with `-Wall -Wextra -Werror -std=c++98`.
