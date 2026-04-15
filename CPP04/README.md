# CPP Module 04 - Subtype Polymorphism & Abstract Classes

## Overview

Module 04 covers runtime polymorphism through virtual functions, abstract classes, and interfaces. The exercises build an animal hierarchy that demonstrates dynamic dispatch and pure virtual functions.

## Learning objectives

- Virtual functions and dynamic binding
- Virtual destructors
- Abstract classes and pure virtual functions (`= 0`)
- Deep copy with dynamically allocated members
- Interfaces (classes with only pure virtual functions)

## Exercises

| Exercise | Name | Key concepts |
|----------|------|-------------|
| ex00 | Polymorphism | Animal, Dog, Cat hierarchy; virtual `makeSound`, virtual destructor |
| ex01 | I don't want to set the world on fire | Brain class, deep copy of pointer members in Dog/Cat |
| ex02 | Abstract class | Animal becomes abstract (pure virtual `makeSound`) |
| ex03 | Interface & recap | AMateria, ICharacter, IMateriaSource — interface-based design |

## Compilation

```bash
cd ex00  # or ex01, ex02, ex03
make
```

Compiles with `-Wall -Wextra -Werror -std=c++98`.
