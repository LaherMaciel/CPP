# CPP Module 03 - Inheritance & Polymorphism

## 📋 Overview

Module 03 introduces inheritance, virtual functions, and polymorphism. This module focuses on creating class hierarchies and understanding runtime polymorphism.

## 🎯 Learning Objectives

By the end of this module, you will understand:
- Inheritance concepts and syntax
- Virtual functions and virtual destructors
- Polymorphism and dynamic binding
- Base class and derived class relationships
- Virtual function tables (vtables)
- Pure virtual functions and abstract classes

## 📚 Key Concepts

### 1. Inheritance
- **Base Class**: Parent class being inherited from
- **Derived Class**: Child class that inherits
- **Access Specifiers**: `public`, `protected`, `private` inheritance
- **Multiple Inheritance**: Inheriting from multiple base classes

### 2. Virtual Functions
- **Virtual Keyword**: `virtual` function declaration
- **Virtual Destructors**: `virtual ~ClassName()`
- **Override**: `override` keyword (C++11+)
- **Virtual Function Tables**: Runtime dispatch mechanism

### 3. Polymorphism
- **Runtime Polymorphism**: Function calls resolved at runtime
- **Dynamic Binding**: Virtual function calls
- **Base Class Pointers**: Pointing to derived objects
- **Function Overriding**: Redefining base class functions

### 4. Abstract Classes
- **Pure Virtual Functions**: `= 0` syntax
- **Cannot Instantiate**: Abstract classes cannot create objects
- **Interface Definition**: Defining contracts for derived classes

## 📁 Exercise Structure

```
CPP_Module_03/
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

1. **Missing Virtual Destructors**: Always use virtual destructors in base classes
2. **Slicing**: Object slicing when copying derived objects to base objects
3. **Virtual Function Override**: Proper virtual function overriding
4. **Memory Management**: Proper cleanup in inheritance hierarchies
5. **Access Specifiers**: Understanding inheritance access levels

## 📖 Resources

- [C++ Reference - Inheritance](https://en.cppreference.com/w/cpp/language/derived_class)
- [C++ Reference - Virtual Functions](https://en.cppreference.com/w/cpp/language/virtual)
- [C++ Reference - Abstract Classes](https://en.cppreference.com/w/cpp/language/abstract_class)

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

After completing Module 03, you'll move on to [CPP Module 04](../CPP_Module_04/README.md) which covers subtype polymorphism and interfaces.

---

**Status**: ⏳ Planned  
**Last Updated**: [Current Date]  
**Completion**: 0/8 exercises
