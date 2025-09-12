# CPP Module 07 - C++ Templates

## 📋 Overview

Module 07 introduces C++ templates, including function templates, class templates, and template specialization. This module focuses on generic programming and code reuse.

## 🎯 Learning Objectives

By the end of this module, you will understand:
- Function template syntax and usage
- Class template definition and instantiation
- Template specialization (full and partial)
- Template parameter types and constraints
- Template instantiation and compilation
- Generic programming principles

## 📚 Key Concepts

### 1. Function Templates
- **Syntax**: `template<typename T> ReturnType function(T param)`
- **Template Parameters**: `typename` or `class` keywords
- **Template Instantiation**: Compiler generates specific functions
- **Type Deduction**: Automatic type inference from arguments

### 2. Class Templates
- **Syntax**: `template<typename T> class ClassName`
- **Member Functions**: Template member function definitions
- **Static Members**: Template static member variables
- **Template Instantiation**: Creating specific class instances

### 3. Template Specialization
- **Full Specialization**: `template<> class ClassName<SpecificType>`
- **Partial Specialization**: `template<typename T> class ClassName<T*>`
- **Function Specialization**: Specialized function implementations
- **Use Cases**: Optimizing for specific types

### 4. Template Parameters
- **Type Parameters**: `template<typename T>`
- **Non-type Parameters**: `template<int N>`
- **Template Parameters**: `template<template<typename> class Container>`
- **Default Parameters**: `template<typename T = int>`

## 📁 Exercise Structure

```
CPP_Module_07/
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

1. **Template Definition**: Templates must be defined in header files
2. **Template Instantiation**: Explicit instantiation requirements
3. **Template Specialization**: Proper specialization syntax
4. **Type Deduction**: Understanding automatic type inference
5. **Compilation Errors**: Template error messages can be verbose

## 📖 Resources

- [C++ Reference - Templates](https://en.cppreference.com/w/cpp/language/templates)
- [C++ Reference - Function Templates](https://en.cppreference.com/w/cpp/language/function_template)
- [C++ Reference - Class Templates](https://en.cppreference.com/w/cpp/language/class_template)

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

After completing Module 07, you'll move on to [CPP Module 08](../CPP_Module_08/README.md) which covers templated containers, iterators, and algorithms.

---

**Status**: ⏳ Planned  
**Last Updated**: [Current Date]  
**Completion**: 0/8 exercises
