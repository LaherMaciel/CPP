# CPP Module 04 - Subtype Polymorphism & Interfaces

## 📋 Overview

Module 04 focuses on subtype polymorphism, abstract classes, and interfaces. This module builds upon inheritance concepts to create flexible and extensible class hierarchies.

## 🎯 Learning Objectives

By the end of this module, you will understand:
- Subtype polymorphism principles
- Pure virtual functions and abstract classes
- Interface design patterns
- Virtual function implementation
- Abstract base class usage
- Polymorphic object handling

## 📚 Key Concepts

### 1. Subtype Polymorphism
- **Liskov Substitution Principle**: Derived objects can replace base objects
- **Interface Segregation**: Small, focused interfaces
- **Dependency Inversion**: Depend on abstractions, not concretions
- **Polymorphic Collections**: Collections of base class pointers

### 2. Abstract Classes
- **Pure Virtual Functions**: `virtual ReturnType function() = 0;`
- **Cannot Instantiate**: Abstract classes cannot create objects
- **Interface Definition**: Defining contracts for derived classes
- **Implementation Requirements**: Derived classes must implement pure virtuals

### 3. Interfaces
- **Pure Virtual Interface**: All functions are pure virtual
- **Multiple Interfaces**: Classes can implement multiple interfaces
- **Interface Segregation**: Small, cohesive interfaces
- **Implementation Flexibility**: Different implementations of same interface

### 4. Virtual Function Tables
- **VTable Structure**: Runtime function dispatch mechanism
- **Virtual Function Override**: Proper overriding in derived classes
- **Dynamic Binding**: Runtime function resolution
- **Performance Considerations**: Virtual function call overhead

## 📁 Exercise Structure

```
CPP_Module_04/
├── ex00/                   # Exercise 00
├── ex01/                   # Exercise 01
├── ex02/                   # Exercise 02
├── ex03/                   # Exercise 03
├── ex04/                   # Exercise 04
├── ex05/                   # Exercise 05
├── ex06/                   # Exercise 06
├── ex07/                   # Exercise 07
└── README.md              # This file
```

## 🛠️ Compilation Instructions

### Individual Exercise
```bash
cd ex00
g++ -Wall -Wextra -Werror -std=c++98 *.cpp -o program_name
./program_name
```

## 📝 Exercise Details

*Exercise details will be added as you progress through each exercise.*

## 🔍 Common Pitfalls

1. **Missing Pure Virtual Implementation**: All pure virtuals must be implemented
2. **Abstract Class Instantiation**: Cannot create objects of abstract classes
3. **Interface Violation**: Breaking interface contracts
4. **Virtual Destructor**: Always use virtual destructors in base classes
5. **Memory Management**: Proper cleanup in polymorphic hierarchies

## 📖 Resources

- [C++ Reference - Abstract Classes](https://en.cppreference.com/w/cpp/language/abstract_class)
- [C++ Reference - Virtual Functions](https://en.cppreference.com/w/cpp/language/virtual)
- [SOLID Principles](https://en.wikipedia.org/wiki/SOLID)

## ✅ Progress Checklist

- [ ] Exercise 00: [Exercise Name]
- [ ] Exercise 01: [Exercise Name]
- [ ] Exercise 02: [Exercise Name]
- [ ] Exercise 03: [Exercise Name]
- [ ] Exercise 04: [Exercise Name]
- [ ] Exercise 05: [Exercise Name]
- [ ] Exercise 06: [Exercise Name]
- [ ] Exercise 07: [Exercise Name]
- [ ] Code review and optimization
- [ ] Documentation completion

## 🚀 Next Module

After completing Module 04, you'll move on to [CPP Module 05](../CPP_Module_05/README.md) which covers repetition and exceptions.

---

**Status**: ⏳ Planned  
**Last Updated**: [Current Date]  
**Completion**: 0/8 exercises
