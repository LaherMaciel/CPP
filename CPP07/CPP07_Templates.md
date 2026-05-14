# CPP07 — C++ Templates
### A Deep Reference Document

---

## Table of Contents
1. [What are Templates and Why They Exist](#1-what-are-templates-and-why-they-exist)
2. [Function Templates](#2-function-templates)
3. [Template Argument Deduction](#3-template-argument-deduction)
4. [Class Templates](#4-class-templates)
5. [Template Instantiation — What the Compiler Does](#5-template-instantiation--what-the-compiler-does)
6. [Template Specialization](#6-template-specialization)
7. [Non-type Template Parameters](#7-non-type-template-parameters)
8. [Templates in Header Files (.tpp pattern)](#8-templates-in-header-files-tpp-pattern)
9. [Common Template Errors and How to Read Them](#9-common-template-errors-and-how-to-read-them)
10. [Templates vs Polymorphism](#10-templates-vs-polymorphism)
11. [Mental Model Summary](#11-mental-model-summary)

---

## 1. What are Templates and Why They Exist

Consider this problem: you want to write a `swap` function. You need it for `int`, for `float`, for `std::string`, for your custom `Bureaucrat` class. Without templates, you'd write:

```cpp
void swap(int& a, int& b)         { int tmp = a;         a = b;         b = tmp; }
void swap(float& a, float& b)     { float tmp = a;       a = b;         b = tmp; }
void swap(std::string& a, std::string& b) { std::string tmp = a; a = b; b = tmp; }
// ... one per type, forever
```

The logic is IDENTICAL. Only the type changes. This is copy-paste programming, which is fragile (a bug fix requires updating every copy), verbose, and doesn't scale.

**Templates solve this.** A template lets you write the logic ONCE with a **type parameter** that the compiler fills in when you use it:

```cpp
template <typename T>
void swap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

// The compiler generates swap<int>, swap<float>, swap<std::string> etc. automatically
```

Templates are a form of **generic programming** — writing algorithms and data structures that work with any type that meets certain requirements.

**Two kinds of templates:**
1. **Function templates** — template for a function
2. **Class templates** — template for a class (or struct)

---

## 2. Function Templates

### Syntax

```cpp
// 'template' keyword, followed by a template parameter list in < >
// 'typename T' declares T as a type parameter — T is a placeholder
template <typename T>
ReturnType functionName(Parameters) {
    // Body can use T anywhere a type is expected
}
```

### Simple examples

```cpp
// A template that finds the minimum of two values
template <typename T>
T min(T a, T b) {
    return (a < b) ? a : b;
}

// Usage:
int i = min(3, 5);            // T = int
double d = min(3.14, 2.71);   // T = double
std::string s = min(std::string("apple"), std::string("banana"));  // T = std::string
```

### The `typename` vs `class` keyword

```cpp
template <typename T>  // T can be any type
template <class T>     // Exactly the same thing — 'class' here means 'type', not 'class type'
```

Both `typename` and `class` are interchangeable in this context. `typename` is preferred in modern C++ because it's clearer ("any type"), but `class` is valid C++98.

### Multiple type parameters

```cpp
template <typename T, typename U>
void printPair(T first, U second) {
    std::cout << first << ", " << second << std::endl;
}

printPair(42, 3.14);           // T = int, U = double
printPair("hello", 'x');       // T = const char*, U = char
```

### Constraints on T (implicit requirements)

Templates don't specify explicit constraints in C++98. Instead, T must support whatever operations you use on it in the body. If you use `<` for comparison, T must have `operator<`. If you don't, the code won't compile when that instantiation is attempted.

```cpp
template <typename T>
T max(T a, T b) {
    return (a > b) ? a : b;  // T must have operator>
}

max(3, 5);         // int has operator> — compiles
max("a", "b");     // const char* comparison is address comparison — compiles but probably wrong!
```

The requirement for `T` to support certain operations is the **concept** of that template (formalized in C++20, but implicit in C++98/11).

---

## 3. Template Argument Deduction

When you call a function template, you usually don't need to specify the type explicitly — the compiler **deduces** it from the arguments:

```cpp
template <typename T>
void print(T value) {
    std::cout << value << std::endl;
}

print(42);          // compiler deduces T = int
print(3.14);        // compiler deduces T = double
print("hello");     // compiler deduces T = const char*
```

### Explicit instantiation when deduction fails or is wrong

```cpp
template <typename T>
T zero() {
    return T(0);
}

// Deduction fails — there's no argument to deduce from!
// zero();  // ERROR: cannot deduce T

// You must specify explicitly:
int i = zero<int>();        // T = int explicitly
double d = zero<double>();  // T = double explicitly
```

### Deduction with references

```cpp
template <typename T>
void func(T& val) {  // T is deduced WITHOUT the reference
    // ...
}

int x = 10;
func(x);   // T = int (not int&), parameter type is int&
const int y = 20;
func(y);   // T = const int, parameter type is const int&
```

This matters because with `T&`, passing a `const int` makes `T = const int`, not `T = int`. The template preserves constness through deduction.

---

## 4. Class Templates

Class templates let you create generic data structures — containers, wrappers, etc.

### Syntax

```cpp
template <typename T>
class ClassName {
public:
    // Member functions can use T
    void doSomething(T value);
    T getValue() const;
    
private:
    T _data;
};

// Member function definitions outside the class:
template <typename T>
void ClassName<T>::doSomething(T value) {
    _data = value;
}

template <typename T>
T ClassName<T>::getValue() const {
    return _data;
}
```

**Note the syntax:** Every method defined outside the class must be prefixed with `template <typename T>`, and the class name is `ClassName<T>` not just `ClassName`.

### Example: a generic Array class

```cpp
template <typename T>
class Array {
public:
    // Constructor: create array of n elements
    explicit Array(unsigned int n) : _size(n), _data(new T[n]()) {}
    
    // Copy constructor
    Array(const Array& other) : _size(other._size), _data(new T[other._size]) {
        for (unsigned int i = 0; i < _size; i++)
            _data[i] = other._data[i];
    }
    
    // Assignment operator
    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] _data;
            _size = other._size;
            _data = new T[_size];
            for (unsigned int i = 0; i < _size; i++)
                _data[i] = other._data[i];
        }
        return *this;
    }
    
    // Destructor
    ~Array() { delete[] _data; }
    
    // Subscript operator with bounds checking
    T& operator[](unsigned int index) {
        if (index >= _size)
            throw std::out_of_range("Array index out of bounds");
        return _data[index];
    }
    
    // const version for const arrays
    const T& operator[](unsigned int index) const {
        if (index >= _size)
            throw std::out_of_range("Array index out of bounds");
        return _data[index];
    }
    
    unsigned int size() const { return _size; }

private:
    unsigned int _size;
    T* _data;
};

// Usage:
Array<int> intArray(5);      // Array of 5 ints
Array<double> dblArray(3);   // Array of 3 doubles
intArray[0] = 42;
```

### The `new T[n]()` trick

```cpp
T* data = new T[n]();  // Note the () at the end
```

For built-in types (int, float, etc.), the `()` causes **value initialization** — ints become 0, floats become 0.0, etc. For class types, the default constructor is called. Without `()`, built-in types contain garbage. This is the tip in the subject.

---

## 5. Template Instantiation — What the Compiler Does

When you write:

```cpp
template <typename T>
T min(T a, T b) { return (a < b) ? a : b; }

int result = min(3, 5);
```

The compiler generates the following actual function:

```cpp
int min(int a, int b) { return (a < b) ? a : b; }
```

This is called **template instantiation** — the compiler creates a concrete function/class from the template by substituting the type. If you use `min` with `double`, it generates another version:

```cpp
double min(double a, double b) { return (a < b) ? a : b; }
```

**Each unique combination of template arguments gets its own instantiation.** This means:
- Template code can lead to code bloat if used with many types.
- Instantiation happens **at the point of use**, not at the point of definition.
- The compiler needs the full template definition when it instantiates — this is why templates must be in header files.

### Why templates must be in headers

When you write a regular function, you:
- Declare it in `Foo.h`
- Define it in `Foo.cpp`
- The linker connects all the `.o` files together

For templates, the compiler needs the FULL definition to instantiate it for `T = int`. If the definition is in `Foo.cpp`, it gets compiled into `Foo.o`. But `main.cpp` doesn't know the definition — it can only see the declaration from the header. The linker can't help because there's no pre-compiled `min<int>` waiting — instantiation must happen during compilation.

**Solution:** Put template definitions in the header file (either directly, or in a `.tpp` file that is `#include`d at the bottom of the header).

---

## 6. Template Specialization

Sometimes the generic template doesn't work correctly for a specific type, or you want different behavior for it. **Specialization** lets you write a custom implementation for a specific type.

### Full specialization — override for a specific type

```cpp
// Primary template
template <typename T>
bool isNull(T value) {
    return value == T(0);  // 0 for int, 0.0 for double, etc.
}

// Full specialization for const char*
// For char*, "null" means the pointer is nullptr, not the string "0"
template <>  // empty parameter list = full specialization
bool isNull<const char*>(const char* value) {
    return value == nullptr;
}

isNull(0);        // uses primary — returns true (0 == 0)
isNull(nullptr);  // uses primary? No, nullptr is std::nullptr_t...
isNull<const char*>(nullptr);  // uses specialization — returns true
isNull<const char*>("hello");  // uses specialization — returns false
```

### Partial specialization — override for a category of types

Partial specialization only exists for class templates (not function templates in C++98):

```cpp
// Primary template
template <typename T, typename U>
class Pair {
    T first;
    U second;
    // generic implementation
};

// Partial specialization: when both types are the same
template <typename T>
class Pair<T, T> {
    T first;
    T second;
    // can have optimized same-type implementation
};

// Partial specialization: when T is a pointer
template <typename T>
class Pair<T*, T*> {
    T* first;
    T* second;
    // pointer-specific implementation
};
```

For function templates in C++98, use **overloading** instead of partial specialization:

```cpp
template <typename T>
void process(T& value) { /* generic */ }

template <typename T>
void process(T* ptr) { /* pointer-specific overload */ }
```

---

## 7. Non-type Template Parameters

Templates can take values as parameters, not just types:

```cpp
template <typename T, unsigned int N>
class FixedArray {
    T _data[N];  // N is a compile-time constant — can be used in array size
public:
    unsigned int size() const { return N; }
    T& operator[](unsigned int i) { return _data[i]; }
};

FixedArray<int, 5> arr;   // array of 5 ints, size known at compile time
FixedArray<double, 10> d; // array of 10 doubles
```

The CPP07 `Array` class uses `unsigned int n` as a *runtime* constructor parameter (not a template parameter) because the size isn't known until runtime. This is the difference between:

```cpp
Array<int> dynamicArray(n);     // size decided at runtime, uses new[]
FixedArray<int, 5> staticArray; // size is compile-time constant, uses stack/member array
```

---

## 8. Templates in Header Files (.tpp pattern)

Since template definitions must be visible at instantiation time, they need to be in header files. But putting everything in a `.h` or `.hpp` file can get very large. The `.tpp` pattern is a common solution:

**Array.hpp:**
```cpp
#ifndef ARRAY_HPP
#define ARRAY_HPP

template <typename T>
class Array {
public:
    Array(unsigned int n);
    T& operator[](unsigned int i);
    unsigned int size() const;
    // ... declarations
    
private:
    T* _data;
    unsigned int _size;
};

// Include the implementation at the bottom of the header
#include "Array.tpp"

#endif
```

**Array.tpp:**
```cpp
// NOT guarded by #ifdef — included only from Array.hpp

template <typename T>
Array<T>::Array(unsigned int n) : _size(n), _data(new T[n]()) {}

template <typename T>
T& Array<T>::operator[](unsigned int i) {
    if (i >= _size)
        throw std::out_of_range("index out of bounds");
    return _data[i];
}

template <typename T>
unsigned int Array<T>::size() const { return _size; }
```

The `.tpp` file is just a convention — it tells readers "this file contains template implementations" and keeps the class declaration clean. The `#include "Array.tpp"` at the bottom of `Array.hpp` means it all ends up in the header as far as the compiler is concerned.

**Note:** The subject says `.tpp` is optional — you can also put everything directly in the `.hpp`.

---

## 9. Common Template Errors and How to Read Them

Template error messages are notoriously verbose. Here's how to interpret them:

### "No matching function for call to..."
```
error: no matching function for call to 'min(const char*, const char*)'
note: candidate is:
template <typename T> T min(T, T)
note: template argument deduction/substitution failed
```
The compiler tried to deduce `T` from two `const char*` arguments — it would be `T = const char*`. But `const char*` doesn't support `<` in a meaningful way (it compares addresses). The template compiles, but the operation doesn't make sense.

### "Incomplete type" errors
These often mean the class template definition isn't visible when instantiation is attempted. Check your includes.

### "Undefined reference" errors  
Usually means template definitions are in a `.cpp` file, not accessible to other translation units. Move them to the header.

### Reading template error messages
The errors cascade — one bad type substitution causes multiple errors. Focus on:
1. The first error message (the root cause).
2. The line in YOUR code where you used the template.
3. The specific requirement that T failed to meet.

---

## 10. Templates vs Polymorphism

Both templates and virtual function polymorphism achieve "work with multiple types," but they do it in fundamentally different ways.

| Aspect | Templates (static polymorphism) | Virtual functions (runtime polymorphism) |
|---|---|---|
| When resolved | **Compile time** | **Runtime** |
| Mechanism | Code generation per type | vtable + virtual dispatch |
| Performance | Zero runtime overhead | Small overhead per virtual call |
| Flexibility | Types fixed at compile time | Types can be determined at runtime |
| Error detection | At compile time (usually) | At runtime |
| Code size | Can grow (one copy per type) | Shared code |
| Relationship required | None (duck typing) | Must share base class |

### When to use each

**Use templates when:**
- The type is known at compile time.
- You want maximum performance.
- You want to write an algorithm that works on many unrelated types (swap, sort, min/max).
- You're building a container (vector, array, stack).

**Use virtual functions when:**
- The actual type is determined at runtime.
- You have a hierarchy of related classes that share behavior.
- You want to use base class pointers/references to manage heterogeneous collections.
- You need runtime polymorphism (calling the right `execute()` depending on which form type it is).

They complement each other and are often combined:

```cpp
// A generic container that holds polymorphic objects
template <typename T>
class Container {
    T* _elements;  // T is Animal*, Shape*, AForm*, etc.
};
```

---

## 11. Mental Model Summary

Think of a function template as a **recipe for generating functions**. The template itself is not a function — it's instructions the compiler follows to create a function when needed.

```
Template definition:
    template <typename T>
    T swap(T& a, T& b) { ... }
    
    This is NOT compiled into machine code.
    It is stored as a recipe.

When you write:
    swap(3, 5)
    
The compiler says: "I need swap<int>. I have the recipe. Let me generate it."
    
    int swap(int& a, int& b) { ... }  ← actually compiled
```

**The key insight:** Templates are resolved entirely at compile time. By the time your program runs, there are no templates left — there are only the concrete functions and classes that the compiler generated from them. This is called **static dispatch** or **compile-time polymorphism**.

This is fundamentally different from virtual functions, where the dispatch table (vtable) is consulted at runtime to figure out which function to call.

**The three things to remember:**
1. Template definitions must be in header files (or `.tpp` files included from headers).
2. Each unique set of type arguments gets its own compiled copy.
3. T must support whatever operations you perform on it — the constraint is checked at instantiation time, not at template definition time.

---

*End of CPP07 Reference — C++ Templates*
