# CPP05 — Exceptions & Error Handling
### A Deep Reference Document

---

## Table of Contents
1. [Why Exceptions Exist](#1-why-exceptions-exist)
2. [The Core Mechanism: throw, try, catch](#2-the-core-mechanism-throw-try-catch)
3. [Stack Unwinding — What Actually Happens](#3-stack-unwinding--what-actually-happens)
4. [std::exception — The Standard Base Class](#4-stdexception--the-standard-base-class)
5. [Writing Custom Exception Classes](#5-writing-custom-exception-classes)
6. [Nested Exception Classes](#6-nested-exception-classes)
7. [Exception Specifications & noexcept](#7-exception-specifications--noexcept)
8. [Exception Safety Guarantees](#8-exception-safety-guarantees)
9. [The Orthodox Canonical Form & Exceptions](#9-the-orthodox-canonical-form--exceptions)
10. [Common Pitfalls](#10-common-pitfalls)
11. [Mental Model Summary](#11-mental-model-summary)

---

## 1. Why Exceptions Exist

Before exceptions, C programs (and early C++) handled errors through **return codes**:

```cpp
int openFile(const char* path) {
    // returns -1 on error, 0 on success
}

int readData(int fd, char* buf) {
    // returns -1 on error, bytes read on success
}

int main() {
    int fd = openFile("data.txt");
    if (fd == -1) { /* handle error */ return 1; }

    char buf[1024];
    int n = readData(fd, buf);
    if (n == -1) { /* handle error */ return 1; }

    // ... every single call needs an if check
}
```

This approach has serious problems:

**Problem 1: Error handling pollutes the happy path.**
The actual logic is buried under a mountain of `if (err)` checks. Reading the code, it is hard to see what the program actually does vs. what it does when things go wrong.

**Problem 2: Return codes can be silently ignored.**
Nothing forces you to check the return value. The compiler won't warn you (usually). The bug silently propagates, corrupting state far from the original failure point.

**Problem 3: Constructors cannot return a value.**
This is the critical one for C++. A constructor has no return type. If constructing an object fails (e.g., invalid arguments passed), you have no way to signal the failure through a return code. You'd need some `isValid()` flag, which is fragile and ugly.

**Exceptions solve all three:**
- You write the happy path cleanly; error handling is separated into `catch` blocks.
- Ignored exceptions crash the program (via `std::terminate`), which is safer than silent propagation.
- Constructors can `throw`, making object construction atomic — either you get a fully valid object, or you get an exception. There is no "half-constructed" object in your hands.

---

## 2. The Core Mechanism: throw, try, catch

The three keywords form the entire exception system.

### `throw`

`throw` launches an exception. You can throw anything — an int, a string, an object. In practice, always throw objects that derive from `std::exception`.

```cpp
throw 42;                          // legal, but terrible practice
throw "something went wrong";      // legal, but terrible practice
throw std::runtime_error("oops");  // correct use of standard library
throw MyCustomException("oops");   // best practice in your own code
```

When `throw` executes:
1. The thrown object is **copy-constructed** onto a special managed storage area (not the regular stack).
2. The runtime begins searching for a matching `catch` block, going up the call stack.
3. Stack frames are destroyed (destructors called) as the search progresses upward.

### `try`

A `try` block defines a region of code that is "protected". If any exception is thrown inside it — or inside any function called from it, at any depth of the call stack — the `catch` handlers attached to that `try` get a chance to handle it.

```cpp
try {
    riskyFunction();
    anotherRiskyFunction(); // if this throws, riskyFunction's locals are cleaned up
}
catch (/* ... */) {
    // handle it here
}
```

### `catch`

`catch` blocks follow a `try` block. Each `catch` specifies what type it can handle.

```cpp
try {
    // ...
}
catch (const std::out_of_range& e) {
    // handles std::out_of_range and any class derived from it
    std::cerr << "Range error: " << e.what() << std::endl;
}
catch (const std::exception& e) {
    // handles any std::exception not already caught above
    std::cerr << "Standard exception: " << e.what() << std::endl;
}
catch (...) {
    // catches EVERYTHING — the last resort
    std::cerr << "Unknown exception!" << std::endl;
}
```

**Order matters.** `catch` blocks are checked top to bottom. Since derived classes match their base class handler, always put more specific (derived) handlers BEFORE less specific (base) ones. If you put `catch (std::exception&)` first, a `catch (std::out_of_range&)` below it will never execute.

### Catching by reference vs by value

**Always catch by `const` reference.** Here is why:

```cpp
// BAD — catching by value
catch (MyException e) {
    // e is a COPY of the thrown object.
    // If the actual thrown object is of a class derived from MyException,
    // the copy is sliced down to MyException. You lose the derived type.
    // virtual functions dispatch to MyException's version, not the actual type.
}

// GOOD — catching by const reference
catch (const MyException& e) {
    // No copy. No slicing. The original thrown object is referenced.
    // virtual functions (like what()) dispatch correctly to the actual type.
}
```

**Object slicing** is the silent bug where copying a derived object into a base-type variable loses the derived parts. References bypass this entirely.

---

## 3. Stack Unwinding — What Actually Happens

This is the most important section to understand deeply, because it explains why exceptions interact with RAII and destructors so powerfully.

Consider this call stack at the moment of a throw:

```
main()
  └─ processFile()
       └─ parseData()
            └─ validateEntry()  <── throw GradeTooHighException() happens here
```

When `validateEntry()` throws:

1. The runtime checks: does `validateEntry()` have a matching `catch`? **No.**
2. **`validateEntry()`'s stack frame is destroyed.** All local variables in it have their destructors called. This is **stack unwinding**.
3. The runtime checks: does `parseData()` have a matching `catch`? **No.**
4. **`parseData()`'s stack frame is destroyed.** All its local variables' destructors run.
5. The runtime checks: does `processFile()` have a matching `catch`? **No.**
6. **`processFile()`'s stack frame is destroyed.**
7. The runtime checks: does `main()` have a matching `catch`? **Yes!**
8. Execution jumps into `main()`'s `catch` block.

**This is why RAII is so powerful in the presence of exceptions.** Any resource wrapped in an object (file handle, allocated memory, mutex lock) will be automatically released during stack unwinding because the destructor always runs.

```cpp
// DANGEROUS — raw resource, no RAII
void riskyFunction() {
    FILE* f = fopen("data.txt", "r");   // raw pointer, no destructor
    
    doSomethingThatMightThrow();        // if this throws...
    
    fclose(f);  // THIS LINE IS NEVER REACHED. File handle is LEAKED.
}

// SAFE — RAII wrapper
void safeFunction() {
    std::ifstream f("data.txt");        // RAII: destructor calls close()
    
    doSomethingThatMightThrow();        // if this throws...
    
    // f's destructor runs automatically during unwinding. File closed. No leak.
}
```

**What if a destructor throws during unwinding?**
This is catastrophic. If an exception is already propagating and a destructor throws a second exception, `std::terminate()` is called and the program crashes immediately.

**Destructors must NEVER throw.** This is one of the most important rules in C++. If a destructor needs to do something that might fail, the failure must be caught and swallowed inside the destructor, or the class must be redesigned.

---

## 4. std::exception — The Standard Base Class

`std::exception` (from `<stdexcept>` or `<exception>`) is the root of the standard exception hierarchy. It defines one key virtual method:

```cpp
// Simplified — from <exception>
class exception {
public:
    virtual ~exception() throw();
    virtual const char* what() const throw();
};
```

`what()` returns a C-string describing the error. The `throw()` annotation is C++98's way of saying "this function doesn't throw."

### The Standard Exception Hierarchy

```
std::exception
├── std::logic_error         (errors that could be detected before runtime — programmer mistakes)
│   ├── std::invalid_argument    — wrong argument passed
│   ├── std::domain_error        — result not defined (e.g., sqrt of negative)
│   ├── std::length_error        — too large to represent
│   └── std::out_of_range        — value out of valid range
│
├── std::runtime_error       (errors only detectable at runtime — environment issues)
│   ├── std::overflow_error      — arithmetic overflow
│   ├── std::underflow_error     — arithmetic underflow
│   └── std::range_error         — result outside representable range
│
├── std::bad_alloc           — thrown by new when heap allocation fails
├── std::bad_cast            — thrown by dynamic_cast on references
└── std::bad_typeid          — thrown by typeid on null pointer
```

**`std::logic_error`** — For invariant violations. "A grade of -5 is invalid" is a logic error — it means the calling code has a bug.

**`std::runtime_error`** — For things that depend on the environment. "The CSV file is empty" is a runtime error — the code might be correct, but the environment is wrong.

---

## 5. Writing Custom Exception Classes

The correct pattern for a minimal custom exception:

```cpp
#include <stdexcept>

class GradeTooHighException : public std::exception {
public:
    // what() must be const, must return const char*, must not throw
    virtual const char* what() const throw() {
        return "Grade is too high (minimum grade is 1)";
    }
};
```

Note: the subject explicitly states that **exception classes do NOT need to be in Orthodox Canonical Form**. You do not need a copy constructor, assignment operator, etc. for simple exception classes.

### A richer exception (with a dynamic message):

```cpp
#include <stdexcept>
#include <string>

class GradeTooLowException : public std::exception {
private:
    std::string _message;

public:
    // Construct with a custom message
    explicit GradeTooLowException(const std::string& msg) : _message(msg) {}
    
    // Virtual destructor is important when inheriting
    virtual ~GradeTooLowException() throw() {}
    
    virtual const char* what() const throw() {
        return _message.c_str();
    }
};

// Usage:
throw GradeTooLowException("Grade 200 exceeds the maximum of 150");
```

### Why inherit from std::exception?

Because code that uses your class can write:

```cpp
catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
}
```

...and this will catch your custom exception automatically. If your exception doesn't inherit from `std::exception`, users must know your specific type. Inheriting from the standard hierarchy makes your exceptions composable with any existing code.

---

## 6. Nested Exception Classes

C++ lets you define classes inside other classes. Exception classes are commonly nested inside the class that throws them. This creates a clear namespace and expresses ownership.

```cpp
class Bureaucrat {
public:
    // Exception types nested inside Bureaucrat
    class GradeTooHighException : public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Bureaucrat: grade too high (minimum is 1)";
        }
    };
    
    class GradeTooLowException : public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Bureaucrat: grade too low (maximum is 150)";
        }
    };

    Bureaucrat(const std::string& name, int grade) : _name(name), _grade(grade) {
        if (_grade < 1)
            throw GradeTooHighException();
        if (_grade > 150)
            throw GradeTooLowException();
        // If we reach here, the object is guaranteed to be in a valid state
    }

    void incrementGrade() {
        if (_grade - 1 < 1)
            throw GradeTooHighException();
        --_grade;
    }

    void decrementGrade() {
        if (_grade + 1 > 150)
            throw GradeTooLowException();
        ++_grade;
    }

private:
    const std::string _name;
    int _grade;
};

// Throwing — the nested name is used from outside
throw Bureaucrat::GradeTooHighException();

// Catching — same syntax
try {
    Bureaucrat b("Alice", 0);  // throws
}
catch (const Bureaucrat::GradeTooHighException& e) {
    std::cerr << e.what() << std::endl;
}
catch (const std::exception& e) {
    std::cerr << "Unexpected: " << e.what() << std::endl;
}
```

**Why nest them?**
- `Bureaucrat::GradeTooHighException` tells you at the call site exactly which class and which condition caused the error. Much more informative than a generic exception.
- It prevents name collisions. Two unrelated classes can both have a `GradeTooHighException` nested inside them.
- It groups related types together logically.

---

## 7. Exception Specifications (C++98 style)

In C++98, you can annotate functions with `throw(...)`:

```cpp
void safeFunction() throw();           // promises not to throw
void mightThrow() throw(MyException);  // promises only to throw MyException
void anythingGoes();                   // no specification — may throw anything
```

These are **dynamic exception specifications**. They were largely deprecated in C++11 and removed in C++17. The only one you'll encounter in CPP modules is `throw()` (empty), meaning "does not throw." You'll see it on `what()` overrides.

In modern C++ (C++11+), `noexcept` replaces `throw()`:

```cpp
virtual const char* what() const noexcept { return "error"; }  // modern
virtual const char* what() const throw()  { return "error"; }  // C++98 style
```

For the CPP modules (C++98 standard), use `throw()` when overriding `what()`.

---

## 8. Exception Safety Guarantees

When writing a function that might throw, your code implicitly provides one of four guarantees:

### No-throw guarantee (strongest)
The function will **never** throw. Destructors, swap functions, and move operations must provide this.

```cpp
void safeSwap(int& a, int& b) throw() {
    int tmp = a;
    a = b;
    b = tmp;
    // No heap allocations, no virtual calls — impossible to throw
}
```

### Strong guarantee ("commit or rollback")
If the function throws, the program state is **completely unchanged** — as if the function was never called. "All or nothing." This is the ideal for most operations.

Achieved via the **copy-and-swap idiom**:
```cpp
void updateObject(MyClass& obj, int newValue) {
    MyClass tmp = obj;        // 1. Make a copy (might throw — obj is untouched)
    tmp.setValue(newValue);   // 2. Modify the copy (might throw — obj is untouched)
    swap(obj, tmp);           // 3. swap is no-throw — only commit once both steps succeeded
}
// If steps 1 or 2 throw, obj was never modified. Strong guarantee.
```

### Basic guarantee (minimum acceptable)
If the function throws, no resources are leaked and all objects are in a **valid but possibly changed** state. This is what RAII gives you automatically.

### No guarantee (broken code)
Resources may be leaked. Objects may be in an invalid or corrupted state. This is what you get if you write `new` without RAII and the constructor throws. Never acceptable.

---

## 9. The Orthodox Canonical Form & Exceptions

The OCF (Orthodox Canonical Form) requires four special member functions:
1. Default constructor
2. Copy constructor  
3. Copy assignment operator
4. Destructor

With exceptions, the golden rule is: **enforce class invariants in the constructor by throwing if they are violated.**

```cpp
class Bureaucrat {
public:
    // Parameterized constructor — enforces invariants with exceptions
    Bureaucrat(const std::string& name, int grade) : _name(name), _grade(grade) {
        if (_grade < 1)
            throw GradeTooHighException();
        if (_grade > 150)
            throw GradeTooLowException();
        // After this line, the object is GUARANTEED valid. No isValid() needed.
    }
    
    // Copy constructor — source was already validated, no re-check needed
    Bureaucrat(const Bureaucrat& other) : _name(other._name), _grade(other._grade) {}

    // Assignment operator
    Bureaucrat& operator=(const Bureaucrat& other) {
        if (this != &other)
            _grade = other._grade;  // _name is const — cannot be re-assigned
        return *this;
    }
    
    // Destructor — must NEVER throw
    ~Bureaucrat() {}

private:
    const std::string _name;  // const member — set once, never changed
    int _grade;
};
```

**Critical rule: if a constructor throws, the object's destructor is NOT called** (because the object was never fully constructed). However, the destructors of all fully-constructed member variables AND base class subobjects ARE called. So RAII members (like `std::string _name`) are always cleaned up safely even if the constructor body throws.

---

## 10. Common Pitfalls

### Pitfall 1: Throwing in a destructor
```cpp
~MyClass() {
    if (somethingWrong)
        throw MyException();  // NEVER DO THIS
    // If an exception is already propagating during stack unwinding,
    // throwing a second exception calls std::terminate() — instant crash.
}
// Rule: destructors must be noexcept. If you must do something that can fail,
// catch and swallow the failure inside the destructor, or log and continue.
```

### Pitfall 2: Catching by value — object slicing
```cpp
catch (std::exception e) {           // BAD — copies and SLICES the thrown object
    e.what();                        // calls std::exception::what(), not the override
}
catch (const std::exception& e) {   // GOOD — reference, no copy, no slicing
    e.what();                        // correctly calls the overridden what()
}
```

### Pitfall 3: Wrong catch order — most specific must come first
```cpp
// WRONG — base class catch swallows everything
catch (const std::exception& e)    { /* always runs */ }
catch (const std::out_of_range& e) { /* DEAD CODE — never reached */ }

// CORRECT — derived first, base second
catch (const std::out_of_range& e) { /* runs for out_of_range */ }
catch (const std::exception& e)    { /* runs for everything else */ }
```

### Pitfall 4: Forgetting virtual destructors in exception hierarchies
If a base exception class doesn't have a virtual destructor, catching a derived exception by base reference and then the object being destroyed will not call the derived destructor.

```cpp
class Base : public std::exception {
    virtual ~Base() throw() {}  // MUST be virtual if you're going to derive from this
};

class Derived : public Base {
    std::string* msg;  // heap allocation
    ~Derived() throw() { delete msg; }  // won't run if Base's destructor isn't virtual
};
```

### Pitfall 5: Exceptions escaping main()
```cpp
int main() {
    Bureaucrat b("Alice", 0);  // throws, nothing catches it
    // std::terminate() is called. The program crashes.
    // Always wrap main() logic in try/catch.
}
```

---

## 11. Mental Model Summary

Think of exceptions as an **emergency ejection system**.

Normal code flows **downward** through function calls. When something goes catastrophically wrong deep in the call stack, throwing an exception is like pulling an ejector handle — you shoot **upward** through all the stack frames until someone catches you.

As you shoot upward, every stack frame you pass through gets cleaned up (destructors run in reverse order of construction). This is **stack unwinding**.

The practical insight: **exceptions are for exceptional situations** — conditions where the current code cannot meaningfully handle the error and needs to report it upward. If a function can deal with an error condition through normal control flow, use a return value. If the error is truly unrecoverable at that level, throw.

**The three rules to always remember:**
1. **Throw by value** — throw `MyException()`, not a pointer, not a reference.
2. **Catch by `const` reference** — `catch (const MyException& e)` — prevents slicing.
3. **Destructors must never throw** — or you risk `std::terminate()`.

---

*End of CPP05 Reference — Exceptions & Error Handling*
