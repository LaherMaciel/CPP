# CPP06 — C++ Casts & Type Conversion
### A Deep Reference Document

---

## Table of Contents
1. [What is a Cast?](#1-what-is-a-cast)
2. [Why C-style Casts are Dangerous](#2-why-c-style-casts-are-dangerous)
3. [static_cast — Compile-time Safe Conversions](#3-static_cast--compile-time-safe-conversions)
4. [dynamic_cast — Runtime Polymorphic Downcasting](#4-dynamic_cast--runtime-polymorphic-downcasting)
5. [reinterpret_cast — Raw Bitwise Reinterpretation](#5-reinterpret_cast--raw-bitwise-reinterpretation)
6. [const_cast — Removing or Adding const](#6-const_cast--removing-or-adding-const)
7. [RTTI — Run-Time Type Information](#7-rtti--run-time-type-information)
8. [uintptr_t and Pointer Serialization](#8-uintptr_t-and-pointer-serialization)
9. [Type Detection Without typeinfo](#9-type-detection-without-typeinfo)
10. [Choosing the Right Cast — Decision Guide](#10-choosing-the-right-cast--decision-guide)
11. [Mental Model Summary](#11-mental-model-summary)

---

## 1. What is a Cast?

A cast is an explicit instruction to the compiler to treat a value as a different type.

Types in C++ are not just labels — they determine:
- How many bytes a value occupies in memory
- How the bits in those bytes are interpreted
- What operations are valid on that value
- What implicit conversions happen

Converting between types is sometimes necessary and sometimes dangerous. Casts let you do it explicitly, which forces you to think about what you're doing.

There are four kinds of conversion:
1. **Widening / promotion** — converting a smaller type to a larger one (int → long). Usually safe.
2. **Narrowing** — converting a larger type to a smaller one (double → int). Data loss possible.
3. **Related-type conversion** — converting between types in the same hierarchy (Base* → Derived*).
4. **Unrelated-type conversion** — reinterpreting raw bytes as a completely different type.

C++ provides four cast operators that correspond roughly to these categories, with different levels of safety.

---

## 2. Why C-style Casts are Dangerous

In C (and early C++), you cast like this:

```cpp
double pi = 3.14159;
int n = (int)pi;  // C-style cast

// Or the function-style cast (same thing):
int m = int(pi);
```

The problem is that the C-style cast is **too powerful and too permissive**. The compiler will attempt to apply, in order, any of the following:
1. `const_cast`
2. `static_cast`
3. `static_cast` then `const_cast`
4. `reinterpret_cast`
5. `reinterpret_cast` then `const_cast`

It tries them in sequence until one compiles. This means you can accidentally do something far more dangerous than you intended, and the code looks identical to a safe cast.

```cpp
// These look identical in syntax:
const int x = 10;
int* p1 = (int*)&x;             // silently removes const — undefined behavior
double* p2 = (double*)&someInt; // silently reinterprets bytes — potentially UB

// The programmer wanted a simple numeric conversion, got undefined behavior
```

Furthermore, C-style casts are **hard to grep for** in a codebase. How do you search for "all places where we remove constness" if that looks the same as "all places where we convert int to double"?

C++ casts solve this:
- Each cast operator has a single, specific, well-defined meaning.
- Misuse is a compile error, not silent undefined behavior.
- They're easily searchable with tools.
- They document **intent** — a reader can immediately tell what kind of conversion is happening.

---

## 3. static_cast — Compile-time Safe Conversions

`static_cast` performs conversions that are checked at **compile time** using only the type system. If the conversion doesn't make sense from a type perspective, it won't compile.

### Numeric conversions (narrowing and widening)

```cpp
double pi = 3.14159;
int n = static_cast<int>(pi);      // truncates to 3 — compiler knows this is valid
// n == 3, the fractional part is discarded

int i = 65;
char c = static_cast<char>(i);     // valid — int can represent char values
// c == 'A'

float f = static_cast<float>(n);   // widening — always safe
```

### Upcasting (Derived* → Base*) — always safe

```cpp
class Animal {};
class Dog : public Animal {};

Dog* dog = new Dog();
Animal* animal = static_cast<Animal*>(dog);  // safe upcast
// animal now points to the Dog object, but you can only use the Animal interface
```

Upcasting is actually done implicitly in C++, but `static_cast` makes the intent explicit.

### Downcasting (Base* → Derived*) — UNSAFE

```cpp
Animal* animal = new Animal();  // NOT a Dog
Dog* dog = static_cast<Dog*>(animal);  // compiles! But is undefined behavior at runtime
// static_cast trusts YOU. It does NOT check if animal actually points to a Dog.
```

`static_cast` for downcasting says: "I, the programmer, know this is a Dog. Just convert it." If you're wrong, the behavior is undefined. For safe downcasting with a runtime check, use `dynamic_cast`.

### void* conversions

```cpp
void* raw = malloc(sizeof(int));
int* p = static_cast<int*>(raw);  // correct way to cast from void*
```

### Enum to int

```cpp
enum Color { RED = 0, GREEN = 1, BLUE = 2 };
int val = static_cast<int>(GREEN);  // val == 1
Color c = static_cast<Color>(2);    // c == BLUE
```

**When to use `static_cast`:**
- Numeric type conversions (int/float/double/char)
- Upcasting in class hierarchies
- Downcasting when you are absolutely certain of the actual type
- void* to typed pointer conversions
- Enum ↔ int conversions

---

## 4. dynamic_cast — Runtime Polymorphic Downcasting

`dynamic_cast` performs downcasts at **runtime**, checking whether the actual type of the pointed-to object is compatible with the target type. It requires RTTI (Run-Time Type Information) to be enabled (it is by default in most compilers).

**Key requirement:** `dynamic_cast` only works with **polymorphic types** — types that have at least one virtual function (usually a virtual destructor). If the base class has no virtual functions, `dynamic_cast` won't compile.

### With pointers — returns nullptr on failure

```cpp
class Animal { public: virtual ~Animal() {} };  // virtual destructor = polymorphic
class Dog : public Animal {};
class Cat : public Animal {};

Animal* animal = new Dog();  // actually a Dog

// Safe downcast:
Dog* dog = dynamic_cast<Dog*>(animal);
if (dog != nullptr) {
    // It IS a Dog — safe to use
    dog->bark();
} else {
    // It is NOT a Dog
}

// Wrong downcast:
Cat* cat = dynamic_cast<Cat*>(animal);
// cat == nullptr (animal is a Dog, not a Cat)
// No undefined behavior — just a null pointer to check
```

### With references — throws std::bad_cast on failure

```cpp
Animal& animalRef = *animal;  // reference to the same Dog

try {
    Dog& dogRef = dynamic_cast<Dog&>(animalRef);  // succeeds — it IS a Dog
    dogRef.bark();
}
catch (const std::bad_cast& e) {
    // Would be caught if animalRef was not actually a Dog
    std::cerr << "Not a Dog!" << std::endl;
}
```

References can't be null, so `dynamic_cast` on a reference throws instead of returning null.

### dynamic_cast vs static_cast for downcasting

```cpp
Animal* base = new Dog();

// static_cast — no runtime check, undefined behavior if wrong
Dog* d1 = static_cast<Dog*>(base);  // "I KNOW it's a Dog. Trust me."

// dynamic_cast — runtime check, safe
Dog* d2 = dynamic_cast<Dog*>(base); // "Check if it's a Dog at runtime."
if (d2) { /* it is a Dog */ }
```

Use `dynamic_cast` when you're not certain of the actual type. Use `static_cast` only when you are absolutely certain AND the runtime cost of `dynamic_cast` is a problem (it's rarely a real concern).

### How dynamic_cast works under the hood

`dynamic_cast` uses **RTTI** — each polymorphic object has a hidden pointer to a type descriptor (usually accessed via the vtable). When you call `dynamic_cast<Derived*>(basePtr)`, the runtime:
1. Checks the RTTI of the actual object `basePtr` points to.
2. Checks whether that type is `Derived` or a class derived from `Derived`.
3. If yes: returns the correctly adjusted pointer to the `Derived` subobject.
4. If no: returns nullptr (or throws std::bad_cast for references).

This means `dynamic_cast` has a small runtime cost, proportional to the depth of the inheritance hierarchy. In performance-critical code, this matters; in general application code, it's negligible.

---

## 5. reinterpret_cast — Raw Bitwise Reinterpretation

`reinterpret_cast` is the most powerful and the most dangerous cast. It tells the compiler: "Forget everything about the type. Just look at these bits and call them a different type."

It does **no conversion**. It does **no runtime check**. It simply takes the bit pattern and reinterprets it as the target type. The result is **implementation-defined** (it works consistently on a given platform, but behavior may differ between platforms).

```cpp
int n = 42;
// Reinterpret the address of n as a pointer to float — NOT a conversion
float* fp = reinterpret_cast<float*>(&n);
// *fp does NOT equal 42.0f — it's the same bits interpreted as a float

long long addr = reinterpret_cast<long long>(&n);
// addr holds the numeric value of the memory address of n
```

### The main legitimate uses of reinterpret_cast

**1. Pointer ↔ integer (for serialization):**
```cpp
#include <stdint.h>  // for uintptr_t

int value = 42;
int* ptr = &value;

// Store the pointer as an integer (for logging, serialization, etc.)
uintptr_t address = reinterpret_cast<uintptr_t>(ptr);

// Recover the pointer from the integer
int* recovered = reinterpret_cast<int*>(address);
// recovered == ptr (same address)
```

**2. Type-punning in low-level code (hardware, binary protocols):**
```cpp
// Read the bit representation of a float
float f = 1.0f;
unsigned int bits = *reinterpret_cast<unsigned int*>(&f);
// bits now contains the IEEE 754 representation of 1.0f
```

**3. Treating a block of memory as a different type (embedded/systems programming):**
```cpp
unsigned char buffer[4];
// ... fill buffer from network ...
int value = *reinterpret_cast<int*>(buffer);  // interpret 4 bytes as an int
```

### Why is reinterpret_cast dangerous?

```cpp
double d = 3.14;
int* p = reinterpret_cast<int*>(&d);  // legally compiles
*p = 0;  // You just corrupted the double. Undefined behavior territory.

// Also: alignment issues
// On some platforms, accessing an int through an unaligned pointer crashes
char buf[5];
int* misaligned = reinterpret_cast<int*>(buf + 1);  // misaligned — potential crash
```

**Rule:** Only use `reinterpret_cast` when you know exactly what the bits look like and what platform you're on. Never use it when another cast will do.

---

## 6. const_cast — Removing or Adding const

`const_cast` is the only cast that can change the `const` or `volatile` qualifiers of a type. It **cannot** change the actual type.

### Adding const (safe, always legal)

```cpp
int x = 10;
const int* cp = const_cast<const int*>(&x);  // add const — always fine
// But this is silly — implicit conversion does this for you
const int* cp2 = &x;  // same thing without the cast
```

### Removing const — CAREFUL

```cpp
const int x = 10;
int* p = const_cast<int*>(&x);  // remove const — compiles
*p = 42;  // UNDEFINED BEHAVIOR if x was truly const
          // On many compilers, x is still 10 (stored in read-only memory)
          // but *p shows 42 (through the pointer). Chaos.
```

**Removing const from something that was originally declared const is undefined behavior.** The only safe use is:

```cpp
// SAFE: the original variable was NOT const
int mutableInt = 10;
const int* constPtr = &mutableInt;  // const pointer to a non-const int
int* p = const_cast<int*>(constPtr);  // remove const — safe because mutableInt IS mutable
*p = 42;  // OK — mutableInt was never actually const
```

### The legitimate use case: fixing legacy API design

```cpp
// Old C API with a terrible signature — takes char* but never actually modifies it
void legacy_print(char* str);

// Your string is const
const char* myStr = "hello";

// You KNOW legacy_print won't modify the string, but you need to call it:
legacy_print(const_cast<char*>(myStr));  // valid IF you're certain it won't modify
```

This is the most common real-world use: calling old APIs that forgot to mark parameters `const`.

---

## 7. RTTI — Run-Time Type Information

RTTI is the mechanism that makes `dynamic_cast` and `typeid` work. Every polymorphic type has a hidden entry in its vtable that points to type information.

### typeid

`typeid` returns a `std::type_info` object that describes the type of an expression:

```cpp
#include <typeinfo>

class Animal { public: virtual ~Animal() {} };
class Dog : public Animal {};

Animal* ptr = new Dog();

// On the pointer itself — gives Animal* type info (static, not polymorphic)
std::cout << typeid(ptr).name() << std::endl;  // "P6Animal" (mangled)

// Dereferencing — gives the actual dynamic type
std::cout << typeid(*ptr).name() << std::endl;  // "3Dog" (mangled)
```

The `name()` function returns implementation-defined mangled names. You can compare `type_info` objects with `==`:

```cpp
if (typeid(*ptr) == typeid(Dog)) {
    std::cout << "It's a Dog!" << std::endl;
}
```

**Important:** The subject of CPP06 ex02 explicitly **forbids using `typeinfo`**. This forces you to use `dynamic_cast` for type identification instead. This is actually the more idiomatic C++ approach — prefer `dynamic_cast` over `typeid` comparisons.

---

## 8. uintptr_t and Pointer Serialization

`uintptr_t` is an **unsigned integer type** that is guaranteed to be large enough to hold a pointer value on the current platform. It's defined in `<stdint.h>` (C++98) or `<cstdint>` (C++11).

On a 32-bit system: `uintptr_t` is 32 bits (same as a pointer).
On a 64-bit system: `uintptr_t` is 64 bits (same as a pointer).

This is important because `int` is only guaranteed to be at least 16 bits wide and is often 32 bits even on 64-bit systems — not large enough to hold a pointer on all platforms.

### Serialization concept

"Serializing" a pointer means converting it to an integer for storage or transmission, and being able to recover the original pointer:

```cpp
#include <stdint.h>  // C++98

struct Data {
    int value;
    std::string name;
};

Data obj = { 42, "hello" };
Data* ptr = &obj;

// Serialize: pointer → integer
uintptr_t serialized = reinterpret_cast<uintptr_t>(ptr);

// ... store serialized, pass it around ...

// Deserialize: integer → pointer
Data* recovered = reinterpret_cast<Data*>(serialized);

// recovered == ptr (points to the same object)
// *recovered == obj (same data)
```

This works because `reinterpret_cast` between a pointer and `uintptr_t` is explicitly well-defined: the round-trip `pointer → uintptr_t → pointer` gives back the original pointer.

**Why would you ever do this in real code?**
- Storing pointers in heterogeneous containers (though `void*` is cleaner).
- Passing pointers through C callback APIs that only accept integers.
- Low-level memory management, garbage collectors.
- Debugging: logging memory addresses as integers.

In CPP06, this teaches you that `reinterpret_cast` has a well-defined use case for pointer ↔ integer conversions, and that `uintptr_t` is the correct integer type for this purpose.

---

## 9. Type Detection Without typeinfo

Since CPP06 ex02 forbids `<typeinfo>`, you must use `dynamic_cast` to identify types:

```cpp
class Base { public: virtual ~Base() {} };
class A : public Base {};
class B : public Base {};
class C : public Base {};

void identify(Base* ptr) {
    // Try to cast to each derived type
    if (dynamic_cast<A*>(ptr) != nullptr) {
        std::cout << "A" << std::endl;
    } else if (dynamic_cast<B*>(ptr) != nullptr) {
        std::cout << "B" << std::endl;
    } else if (dynamic_cast<C*>(ptr) != nullptr) {
        std::cout << "C" << std::endl;
    } else {
        std::cout << "Unknown" << std::endl;
    }
}
```

### Without pointers (reference version)

The trick: `dynamic_cast` on a reference throws `std::bad_cast` on failure. You can use try/catch as the "check":

```cpp
void identify(Base& ref) {
    // Try A
    try {
        A& a = dynamic_cast<A&>(ref);
        std::cout << "A" << std::endl;
        return;
    } catch (std::bad_cast&) {}
    
    // Try B
    try {
        B& b = dynamic_cast<B&>(ref);
        std::cout << "B" << std::endl;
        return;
    } catch (std::bad_cast&) {}
    
    // Try C
    try {
        C& c = dynamic_cast<C&>(ref);
        std::cout << "C" << std::endl;
        return;
    } catch (std::bad_cast&) {}

    // Note: using a pointer inside this function is FORBIDDEN by the subject
    // So we can't convert &ref to a pointer and use the pointer version
}
```

This is clunky but demonstrates that `dynamic_cast` with references uses exceptions for failure signaling, which is the natural C++ behavior (references can't be null).

---

## 10. Choosing the Right Cast — Decision Guide

```
What are you trying to do?
│
├─ Convert between numeric types (int, float, double, char, enum)?
│   └─ Use: static_cast<TargetType>(value)
│
├─ Convert between pointer/reference types in a known hierarchy?
│   ├─ Upcast (Derived* → Base*)? Use: static_cast or just implicit conversion
│   ├─ Downcast and you are 100% CERTAIN of the type? Use: static_cast
│   └─ Downcast and you need a runtime safety check? Use: dynamic_cast
│       ├─ Using pointer? Check result != nullptr
│       └─ Using reference? Wrap in try/catch std::bad_cast
│
├─ Need to remove/add const?
│   └─ Use: const_cast (only if you know the original was not truly const)
│
├─ Need to convert pointer to/from integer (uintptr_t)?
│   └─ Use: reinterpret_cast
│
└─ Need to reinterpret raw bits as a completely different type?
    └─ Use: reinterpret_cast (with extreme caution, know your platform)

If you're tempted to use a C-style cast: STOP.
Figure out which of the above you actually need and use the correct cast.
```

---

## 11. Mental Model Summary

Think of the four casts as having different "levels of trust" and different safety profiles:

**`static_cast`** — "I'm logically converting this value. The type system says it makes sense. Compile-time check only."
→ Safe for numeric conversions and upcasts. Trust but verify for downcasts.

**`dynamic_cast`** — "I'm navigating an inheritance hierarchy and need the runtime to verify the actual type."
→ Safe but has a cost. Returns null/throws on failure. Requires virtual functions.

**`reinterpret_cast`** — "I'm abandoning type safety entirely and reading raw bits."
→ Only for pointer↔integer and truly low-level operations. Almost never needed in application code.

**`const_cast`** — "I'm changing whether the type system lets me modify this value."
→ Use only to call legacy APIs or when you know the original is mutable. Never to actually modify a truly const object.

**The hierarchy of preference:**
1. No cast (implicit conversion) — always prefer
2. `static_cast` — most common, compile-time checked
3. `dynamic_cast` — when you need runtime type checking
4. `const_cast` — only for const-correctness fixes
5. `reinterpret_cast` — last resort, very specific use cases
6. C-style cast — never

---

*End of CPP06 Reference — C++ Casts & Type Conversion*
