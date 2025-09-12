# CPP Module 05 - Exceptions & Error Handling

## 📋 Overview

Module 05 introduces exception handling, repetition constructs, and error management strategies. This module focuses on robust error handling and program flow control.

## 🎯 Learning Objectives

By the end of this module, you will understand:
- Exception handling with try-catch blocks
- Custom exception classes
- Exception safety and RAII
- Repetition constructs (loops)
- Error propagation and handling
- Resource management during exceptions

## 📚 Key Concepts

### 1. Exception Handling
- **Try-Catch Blocks**: `try { } catch (Exception& e) { }`
- **Throw Statement**: `throw Exception("message");`
- **Exception Types**: Standard and custom exceptions
- **Exception Propagation**: How exceptions bubble up

### 2. Custom Exceptions
- **Exception Classes**: Inheriting from `std::exception`
- **Exception Messages**: Providing meaningful error information
- **Exception Hierarchy**: Creating exception class hierarchies
- **Exception Safety**: Guaranteeing program state during exceptions

### 3. Repetition Constructs
- **For Loops**: `for (init; condition; increment)`
- **While Loops**: `while (condition)`
- **Do-While Loops**: `do { } while (condition);`
- **Range-based Loops**: `for (auto& item : container)`

### 4. Exception Safety
- **No-throw Guarantee**: Functions that never throw
- **Basic Exception Safety**: No resource leaks
- **Strong Exception Safety**: Commit or rollback semantics
- **RAII**: Resource Acquisition Is Initialization

## 📁 Exercise Structure

```
CPP_Module_05/
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

1. **Exception Specification**: Avoid dynamic exception specifications
2. **Resource Leaks**: Ensure proper cleanup in exception handlers
3. **Exception Swallowing**: Don't catch exceptions without handling them
4. **Exception Safety**: Maintain program invariants during exceptions
5. **Performance**: Exception handling has overhead

## 📖 Resources

- [C++ Reference - Exceptions](https://en.cppreference.com/w/cpp/language/exceptions)
- [C++ Reference - Exception Safety](https://en.cppreference.com/w/cpp/language/exceptions)
- [Exception Safety](https://en.wikipedia.org/wiki/Exception_safety)

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

After completing Module 05, you'll move on to [CPP Module 06](../CPP_Module_06/README.md) which covers C++ casts.

---

**Status**: ⏳ Planned  
**Last Updated**: [Current Date]  
**Completion**: 0/8 exercises
