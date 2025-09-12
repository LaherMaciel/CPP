# CPP Module 06 - C++ Casts

## 📋 Overview

Module 06 introduces the four types of C++ casts: static_cast, dynamic_cast, const_cast, and reinterpret_cast. This module focuses on safe and appropriate type conversions.

## 🎯 Learning Objectives

By the end of this module, you will understand:
- The four C++ cast operators
- When and how to use each cast type
- Type safety and conversion rules
- Runtime type checking with dynamic_cast
- Const correctness with const_cast
- Low-level memory reinterpretation

## 📚 Key Concepts

### 1. Static Cast
- **Purpose**: Compile-time type conversions
- **Syntax**: `static_cast<Type>(expression)`
- **Use Cases**: Numeric conversions, upcasting, void* conversions
- **Safety**: Compile-time checked, no runtime overhead

### 2. Dynamic Cast
- **Purpose**: Runtime type checking and safe downcasting
- **Syntax**: `dynamic_cast<Type*>(pointer)` or `dynamic_cast<Type&>(reference)`
- **Use Cases**: Polymorphic type conversions, safe downcasting
- **Safety**: Runtime checked, returns nullptr on failure

### 3. Const Cast
- **Purpose**: Adding or removing const/volatile qualifiers
- **Syntax**: `const_cast<Type>(expression)`
- **Use Cases**: Working with const-incorrect APIs, mutable members
- **Safety**: Can break const correctness, use with caution

### 4. Reinterpret Cast
- **Purpose**: Low-level bit pattern reinterpretation
- **Syntax**: `reinterpret_cast<Type>(expression)`
- **Use Cases**: Converting between unrelated types, bit manipulation
- **Safety**: Most dangerous cast, implementation-dependent

## 📁 Exercise Structure

```
CPP_Module_06/
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

1. **C-Style Casts**: Avoid `(Type)expression`, use C++ casts
2. **Dynamic Cast Performance**: Runtime overhead for type checking
3. **Const Cast Abuse**: Don't use to break const correctness
4. **Reinterpret Cast**: Implementation-dependent behavior
5. **Cast Chain**: Avoid chaining multiple casts

## 📖 Resources

- [C++ Reference - Casts](https://en.cppreference.com/w/cpp/language/cast)
- [C++ Reference - Static Cast](https://en.cppreference.com/w/cpp/language/static_cast)
- [C++ Reference - Dynamic Cast](https://en.cppreference.com/w/cpp/language/dynamic_cast)

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

After completing Module 06, you'll move on to [CPP Module 07](../CPP_Module_07/README.md) which covers C++ templates.

---

**Status**: ⏳ Planned  
**Last Updated**: [Current Date]  
**Completion**: 0/8 exercises
