# CPP Module 00 - C++ Fundamentals

## 📋 Overview

Module 00 introduces the fundamental concepts of C++ programming. This module focuses on understanding the basics of object-oriented programming in C++ and getting familiar with the C++98 standard.

## 🎯 Learning Objectives

By the end of this module, you will understand:
- C++ namespaces and their usage
- Class definition and member functions
- Standard input/output streams
- Initialization lists
- Static member variables and functions
- Const correctness
- Basic object-oriented principles

## 📚 Key Concepts

### 1. Namespaces
- **Purpose**: Prevent naming conflicts and organize code
- **Usage**: `std::`, custom namespaces
- **Syntax**: `namespace name { }`

### 2. Classes and Objects
- **Class Definition**: Data members and member functions
- **Access Specifiers**: `public`, `private`, `protected`
- **Object Creation**: Constructor and destructor

### 3. Member Functions
- **Declaration**: Inside class definition
- **Definition**: Outside class (using scope resolution)
- **Inline Functions**: Defined inside class

### 4. Input/Output Streams
- **Standard Streams**: `std::cout`, `std::cin`, `std::cerr`
- **Stream Manipulators**: `std::endl`, `std::setw`
- **Formatting**: Basic output formatting

### 5. Initialization Lists
- **Purpose**: Initialize member variables efficiently
- **Syntax**: `Constructor() : member1(value1), member2(value2)`
- **Benefits**: Direct initialization vs assignment

### 6. Static Members
- **Static Variables**: Shared among all instances
- **Static Functions**: Can be called without object instance
- **Memory**: Stored in static memory area

### 7. Const Correctness
- **Const Objects**: Cannot be modified
- **Const Functions**: Cannot modify object state
- **Const Parameters**: Parameters cannot be modified

## 📁 Exercise Structure

```
CPP_Module_00/
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

### All Exercises
```bash
# From module root directory
for dir in ex*/; do
    echo "Compiling $dir"
    cd "$dir"
    g++ -Wall -Wextra -Werror -std=c++98 *.cpp -o main
    cd ..
done
```

## 📝 Exercise Details

### Exercise 00: Namespaces and Basic I/O
- **Focus**: Understanding namespaces and basic input/output
- **Key Files**: `main.cpp`, header files
- **Concepts**: `std::cout`, `std::endl`, namespace usage

### Exercise 01: Classes and Member Functions
- **Focus**: Basic class definition and member functions
- **Key Files**: Class definition and implementation
- **Concepts**: Class syntax, member functions, access specifiers

### Exercise 02: Constructors and Destructors
- **Focus**: Object lifecycle management
- **Key Files**: Constructor/destructor implementation
- **Concepts**: Default constructor, destructor, object creation

### Exercise 03: Initialization Lists
- **Focus**: Efficient member initialization
- **Key Files**: Constructor with initialization lists
- **Concepts**: Initialization vs assignment, const members

### Exercise 04: Static Members
- **Focus**: Static variables and functions
- **Key Files**: Static member implementation
- **Concepts**: Static variables, static functions, shared state

### Exercise 05: Const Correctness
- **Focus**: Immutable objects and functions
- **Key Files**: Const member functions
- **Concepts**: Const objects, const functions, const parameters

### Exercise 06: Advanced Classes
- **Focus**: Combining all concepts
- **Key Files**: Complex class implementation
- **Concepts**: All previous concepts combined

### Exercise 07: Final Project
- **Focus**: Comprehensive application
- **Key Files**: Multiple classes working together
- **Concepts**: Complete module integration

## 🔍 Common Pitfalls

1. **Forgetting `std::`**: Always use `std::` prefix for standard library
2. **Missing Semicolons**: C++ requires semicolons after class definitions
3. **Initialization Order**: Member initialization order follows declaration order
4. **Const Functions**: Cannot modify member variables in const functions
5. **Static Initialization**: Static members must be defined outside class

## 📖 Resources

- [C++ Reference - Classes](https://en.cppreference.com/w/cpp/language/classes)
- [C++ Reference - Namespaces](https://en.cppreference.com/w/cpp/language/namespace)
- [C++ Reference - Static Members](https://en.cppreference.com/w/cpp/language/static)
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/)

## ✅ Progress Checklist

- [ ] Exercise 00: Namespaces and Basic I/O
- [ ] Exercise 01: Classes and Member Functions
- [ ] Exercise 02: Constructors and Destructors
- [ ] Exercise 03: Initialization Lists
- [ ] Exercise 04: Static Members
- [ ] Exercise 05: Const Correctness
- [ ] Exercise 06: Advanced Classes
- [ ] Exercise 07: Final Project
- [ ] Code review and optimization
- [ ] Documentation completion

## 🚀 Next Module

After completing Module 00, you'll move on to [CPP Module 01](../CPP_Module_01/README.md) which covers memory allocation, pointers to members, references, and the switch statement.

---

**Status**: 🔄 In Progress  
**Last Updated**: [Current Date]  
**Completion**: 0/8 exercises
