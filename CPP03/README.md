# CPP Module 03 - Inheritance

## Overview

Module 03 introduces inheritance through a chain of monster classes. Each exercise extends the previous, building up from a base ClapTrap to a multi-level hierarchy.

## Learning objectives

- Single inheritance and class hierarchies
- Member function overriding
- Constructor/destructor call order in inheritance
- Protected members
- Multiple inheritance and diamond problem

## Exercises

| Exercise | Name | Key concepts |
|----------|------|-------------|
| ex00 | ClapTrap | Base class with HP, energy, attack damage, and actions |
| ex01 | Serena, my love! | ScavTrap inherits ClapTrap, overrides `attack`, adds `guardGate` |
| ex02 | Repetitive work | FragTrap inherits ClapTrap, adds `highFivesGuys` |
| ex03 | Now it's weird! | DiamondTrap inherits both ScavTrap and FragTrap (diamond problem) |

## Compilation

```bash
cd ex00  # or ex01, ex02, ex03
make
```

Compiles with `-Wall -Wextra -Werror -std=c++98`.
