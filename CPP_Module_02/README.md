# CPP Module 02 - Operator Overloading & Canonical Classes

## 📋 Overview

Module 02 introduces ad-hoc polymorphism through operator overloading and the canonical form of classes. This module focuses on making your classes behave like built-in types.

## 🎯 Learning Objectives

By the end of this module, you will understand:
- Operator overloading concepts and syntax
- Canonical form of classes (Orthodox Canonical Class)
- Copy constructor and assignment operator
- Destructor implementation
- Default constructor usage
- Deep vs shallow copying
- Operator overloading best practices

## 📚 Key Concepts

### 1. Operator Overloading
- **Arithmetic Operators**: `+`, `-`, `*`, `/`, `%`
- **Comparison Operators**: `==`, `!=`, `<`, `>`, `<=`, `>=`
- **Assignment Operators**: `=`, `+=`, `-=`, etc.
- **Stream Operators**: `<<`, `>>`
- **Increment/Decrement**: `++`, `--`

### 2. Canonical Form
- **Default Constructor**: `ClassName()`
- **Copy Constructor**: `ClassName(const ClassName& other)`
- **Assignment Operator**: `ClassName& operator=(const ClassName& other)`
- **Destructor**: `~ClassName()`

### 3. Deep vs Shallow Copy
- **Shallow Copy**: Copies pointers, not data
- **Deep Copy**: Copies actual data
- **Memory Management**: Proper resource handling

### 4. Orthodox Canonical Class
- **Four Essential Functions**: Default constructor, copy constructor, assignment operator, destructor
- **Rule of Three**: If you need one, you need all three
- **Resource Management**: Proper cleanup and copying

## 📁 Exercise Structure

```
CPP_Module_02/
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

1. **Self-Assignment**: Check for `this == &other` in assignment operator
2. **Memory Leaks**: Proper cleanup in destructor and assignment
3. **Shallow Copy Issues**: Implement deep copy when needed
4. **Operator Return Types**: Correct return types for operators
5. **Const Correctness**: Proper const usage in operators

## 📖 Resources

- [C++ Reference - Operator Overloading](https://en.cppreference.com/w/cpp/language/operators)
- [C++ Reference - Copy Constructor](https://en.cppreference.com/w/cpp/language/copy_constructor)
- [Rule of Three](https://en.wikipedia.org/wiki/Rule_of_three_(C%2B%2B_programming))

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

After completing Module 02, you'll move on to [CPP Module 03](../CPP_Module_03/README.md) which covers inheritance and polymorphism.

---

**Status**: ⏳ Planned  
**Last Updated**: [Current Date]  
**Completion**: 0/8 exercises
