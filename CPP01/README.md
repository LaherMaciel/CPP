# CPP Module 01 - Memory Allocation & References

## 📋 Overview

Module 01 focuses on memory management, pointers to members, references, and the switch statement. This module builds upon the fundamentals learned in Module 00.

## 🎯 Learning Objectives

By the end of this module, you will understand:
- Dynamic memory allocation with `new` and `delete`
- References and their differences from pointers
- Pointers to member functions and variables
- Switch statement usage and best practices
- Memory management best practices
- RAII (Resource Acquisition Is Initialization) principles

## 📚 Key Concepts

### 1. Memory Allocation
- **New Operator**: Dynamic memory allocation
- **Delete Operator**: Memory deallocation
- **Array Allocation**: `new[]` and `delete[]`
- **Memory Leaks**: Prevention and detection

### 2. References
- **Reference Declaration**: `Type& ref = variable`
- **Reference vs Pointer**: Differences and use cases
- **Const References**: `const Type&` for efficiency
- **Reference Parameters**: Passing by reference

### 3. Pointers to Members
- **Member Function Pointers**: `ReturnType (Class::*ptr)(params)`
- **Member Variable Pointers**: `Type Class::*ptr`
- **Usage**: Dynamic function calls and data access

### 4. Switch Statement
- **Syntax**: `switch (expression) { case value: ... }`
- **Break Statement**: Preventing fall-through
- **Default Case**: Handling unexpected values
- **Best Practices**: Complete case coverage

## 📁 Exercise Structure

```
CPP_Module_01/
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

1. **Memory Leaks**: Always pair `new` with `delete`
2. **Array Deletion**: Use `delete[]` for arrays, `delete` for single objects
3. **Dangling References**: References cannot be reassigned
4. **Switch Fall-through**: Always use `break` statements
5. **Null Pointer Dereference**: Check pointers before use

## 📖 Resources

- [C++ Reference - Dynamic Memory](https://en.cppreference.com/w/cpp/language/new)
- [C++ Reference - References](https://en.cppreference.com/w/cpp/language/reference)
- [C++ Reference - Switch](https://en.cppreference.com/w/cpp/language/switch)

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

After completing Module 01, you'll move on to [CPP Module 02](../CPP_Module_02/README.md) which covers ad-hoc polymorphism and operator overloading.

---

**Status**: ⏳ Planned  
**Last Updated**: [Current Date]  
**Completion**: 0/8 exercises
