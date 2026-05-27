# CPP04 — Subtype Polymorphism, Abstract Classes & Interfaces
### A Deep Reference Document

---

## Table of Contents
1. [What is Polymorphism? The Four Kinds](#1-what-is-polymorphism-the-four-kinds)
2. [Subtype Polymorphism — The Runtime Kind](#2-subtype-polymorphism--the-runtime-kind)
3. [virtual Functions — The Mechanism](#3-virtual-functions--the-mechanism)
4. [The vtable — How Virtual Dispatch Works Under the Hood](#4-the-vtable--how-virtual-dispatch-works-under-the-hood)
5. [The Virtual Destructor — The Most Common OOP Bug](#5-the-virtual-destructor--the-most-common-oop-bug)
6. [Shallow Copy vs Deep Copy](#6-shallow-copy-vs-deep-copy)
7. [Abstract Classes and Pure Virtual Functions](#7-abstract-classes-and-pure-virtual-functions)
8. [Interfaces — Pure Abstract Classes](#8-interfaces--pure-abstract-classes)
9. [The Prototype Pattern — clone()](#9-the-prototype-pattern--clone)
10. [Memory Ownership with Polymorphic Objects](#10-memory-ownership-with-polymorphic-objects)
11. [WrongAnimal — The Demonstration of What NOT to Do](#11-wronganimal--the-demonstration-of-what-not-to-do)
12. [Mental Model Summary](#12-mental-model-summary)

---

## 1. What is Polymorphism? The Four Kinds

The word "polymorphism" comes from Greek: *poly* (many) + *morphe* (form). In programming, it means **one interface, multiple implementations** — the ability to call the same function on different objects and get different behavior.

C++ has four distinct kinds:

**1. Ad-hoc polymorphism (function overloading)**
Same function name, different parameter types. Resolved at compile time.
```cpp
void print(int x)    { std::cout << x; }
void print(double x) { std::cout << x; }
void print(char x)   { std::cout << x; }
```

**2. Parametric polymorphism (templates)**
One function/class definition, many types via generic programming. Resolved at compile time.
```cpp
template <typename T>
T max(T a, T b) { return (a > b) ? a : b; }
```

**3. Coercion polymorphism (implicit conversion)**
Automatic type conversion by the compiler. You pass an `int` where a `double` is expected.

**4. Subtype polymorphism (inheritance + virtual functions)**
A derived class object used through a base class pointer/reference, where virtual function calls dispatch to the derived class version. Resolved at **runtime**.

CPP04 is entirely about this fourth kind. It is the heart of classical Object-Oriented Programming.

---

## 2. Subtype Polymorphism — The Runtime Kind

The **Liskov Substitution Principle** (LSP) states: if `S` is a subtype of `T`, then anywhere a `T` is used, an `S` can be substituted without breaking the program. This is the theoretical foundation of subtype polymorphism.

In practice: if `Dog` inherits from `Animal`, then anywhere an `Animal*` is expected, you can pass a `Dog*`.

```cpp
class Animal {
public:
    void makeSound() { std::cout << "..."; }  // NOT virtual
};

class Dog : public Animal {
public:
    void makeSound() { std::cout << "Woof!"; }  // hides Animal's makeSound
};

Animal* a = new Dog();
a->makeSound();  // Prints "..."  ← WRONG behavior — Animal's version is called
```

Without `virtual`, this is **static dispatch** — the compiler looks at the declared type of the pointer (`Animal*`) and calls `Animal::makeSound`. The fact that it actually points to a `Dog` is ignored.

```cpp
class Animal {
public:
    virtual void makeSound() { std::cout << "..."; }  // NOW virtual
};

class Dog : public Animal {
public:
    virtual void makeSound() { std::cout << "Woof!"; }  // overrides
};

Animal* a = new Dog();
a->makeSound();  // Prints "Woof!" ← CORRECT — Dog's version is called
```

With `virtual`, this is **dynamic dispatch** — the runtime checks the actual type of the object (Dog) and calls the right function. The declared type of the pointer no longer dictates which function runs.

**This is the entire point of CPP04.** The `virtual` keyword changes dispatch from compile-time to runtime, enabling a single piece of code to work correctly with any present or future subclass.

---

## 3. virtual Functions — The Mechanism

### Declaring a virtual function

```cpp
class Base {
public:
    virtual void doSomething();     // declared virtual in base
    virtual void doElse() const;    // const qualifiers are preserved in override
};
```

### Overriding in a derived class

```cpp
class Derived : public Base {
public:
    virtual void doSomething();  // 'virtual' is optional here but good practice
    // In C++11+, you'd write: void doSomething() override;
    // In C++98, the virtual keyword in derived is optional but conventional
};
```

The override is valid only when:
1. The function name is identical.
2. The parameter types are identical.
3. The `const` qualifier matches.
4. The return type is the same (or covariant — a derived type, for pointers/references).

**If any of these don't match, you get a NEW function, not an override.** This is a silent, common mistake.

### Covariant return types

An override can return a pointer or reference to a type derived from the base's return type:

```cpp
class Base {
public:
    virtual Base* clone() const;
};

class Derived : public Base {
public:
    virtual Derived* clone() const;  // Valid: Derived* is covariant with Base*
};
```

This is used in the **prototype pattern** (see section 9).

### What virtual does NOT change

- `virtual` only affects calls made through a pointer or reference to a base class.
- Calling through an object directly always uses the static type:

```cpp
Dog d;
d.makeSound();        // Static dispatch — always calls Dog::makeSound, regardless of virtual

Animal& ref = d;
ref.makeSound();      // Dynamic dispatch — calls Dog::makeSound because virtual

Animal a = d;         // OBJECT SLICING — d's Dog parts are copied into an Animal
a.makeSound();        // Static dispatch on the Animal object — calls Animal::makeSound
```

---

## 4. The vtable — How Virtual Dispatch Works Under the Hood

This is what the compiler generates behind the scenes when you use `virtual`. Understanding this makes everything about polymorphism click.

### Setup

When a class has at least one virtual function, the compiler creates a **vtable** (virtual function table) for that class. A vtable is an array of function pointers — one entry per virtual function.

```
Animal's vtable:
  [0] → Animal::makeSound
  [1] → Animal::~Animal  (virtual destructor)

Dog's vtable:
  [0] → Dog::makeSound    (overridden)
  [1] → Dog::~Dog         (overridden)

Cat's vtable:
  [0] → Cat::makeSound    (overridden)
  [1] → Cat::~Cat         (overridden)
```

### The vptr

Every object of a class with virtual functions has a hidden pointer called the **vptr** (virtual pointer). This pointer is automatically set by the constructor to point to the class's vtable.

```
Memory layout of a Dog object:
  [ vptr ] → points to Dog's vtable
  [ type ] → "Dog"
  [  ... ] → other Dog-specific data

Memory layout of an Animal object:
  [ vptr ] → points to Animal's vtable
  [ type ] → ""
```

### What happens during a virtual call

```cpp
Animal* ptr = new Dog();
ptr->makeSound();
```

1. The CPU looks at `ptr` (an `Animal*` — but that's just the type used for access).
2. It reads the `vptr` from the object `ptr` points to. The `vptr` points to Dog's vtable.
3. It looks up entry [0] in Dog's vtable — this is `Dog::makeSound`.
4. It calls `Dog::makeSound`.

**Non-virtual call (no vtable lookup):**
```cpp
ptr->Animal::makeSound();  // explicitly calling Animal's version
// Or:
Animal a;
a.makeSound();  // object on stack, type known at compile time, direct call
```

### Cost of virtual dispatch

A virtual call is slightly slower than a direct call because of the extra indirection (read vptr → index into vtable → call). In practice, this cost is negligible for most applications. It becomes relevant only in extremely tight inner loops called millions of times.

The size cost: every polymorphic object carries one extra pointer (8 bytes on 64-bit). Every polymorphic class has one vtable (shared among all instances, so this is a fixed cost).

---

## 5. The Virtual Destructor — The Most Common OOP Bug

This is one of the most important rules in C++: **if a class has any virtual function, it must have a virtual destructor.**

### The bug without a virtual destructor

```cpp
class Animal {
public:
    ~Animal() {              // NOT virtual — MISTAKE
        std::cout << "Animal destroyed" << std::endl;
    }
};

class Dog : public Animal {
private:
    Brain* _brain;  // heap-allocated resource
public:
    Dog()  { _brain = new Brain(); }
    ~Dog() {
        delete _brain;       // must be called to avoid leak
        std::cout << "Dog destroyed" << std::endl;
    }
};

Animal* a = new Dog();
delete a;  // calls Animal::~Animal ONLY — Dog::~Dog is NEVER called
           // _brain is LEAKED. Memory corruption possible.
```

**Why?** `delete a` calls the destructor through an `Animal*` pointer. Without `virtual`, the destructor is statically dispatched to `Animal::~Animal`. The Dog part of the object is never properly destroyed.

### The fix: virtual destructor

```cpp
class Animal {
public:
    virtual ~Animal() {        // virtual destructor — problem solved
        std::cout << "Animal destroyed" << std::endl;
    }
};

Animal* a = new Dog();
delete a;
// Output:
//   Dog destroyed    ← Dog::~Dog is called first (due to vtable lookup)
//   Animal destroyed ← Then Animal::~Animal is called (base class destructor always runs)
```

With a virtual destructor, `delete a` does the vtable lookup, finds `Dog::~Dog`, calls it. After `Dog::~Dog` runs, the base class destructor `Animal::~Animal` runs automatically (destructors always chain upward through the hierarchy).

**Rule: if you have any virtual function, make your destructor virtual. Period.**

A practical corollary: **interfaces** (classes with only pure virtual functions) must also have a virtual destructor:

```cpp
class ICharacter {
public:
    virtual ~ICharacter() {}  // virtual, with empty body — essential
    virtual void use(int idx, ICharacter& target) = 0;
    // ...
};
```

---

## 6. Shallow Copy vs Deep Copy

This is a critical concept that CPP04 specifically tests.

### Shallow copy — copying the pointer

A **shallow copy** copies the value of pointer members, not what they point to. The copy and the original end up sharing the same heap-allocated data.

```
Original Dog:
  [ vptr   ]
  [ _brain ] → [0x1234: Brain object with 100 strings]

Shallow copy of Dog:
  [ vptr   ]
  [ _brain ] → [0x1234: SAME Brain object]  ← sharing!
```

Problems with shallow copy:
1. If the original is modified (ideas changed), the copy sees the changes too. They're the same Brain.
2. When either object is destroyed, it calls `delete _brain`. Now the other object has a dangling pointer to deleted memory. Double-delete → undefined behavior (crash or corruption).

```cpp
class Dog : public Animal {
private:
    Brain* _brain;
public:
    // Default copy constructor — SHALLOW COPY (just copies the pointer)
    // Dog(const Dog& other) : _brain(other._brain) {}  ← WRONG
    
    // Correct copy constructor — DEEP COPY
    Dog(const Dog& other) : Animal(other) {
        _brain = new Brain(*other._brain);  // allocate NEW Brain, copy contents
    }
    
    // Correct assignment operator — DEEP COPY
    Dog& operator=(const Dog& other) {
        if (this != &other) {
            Animal::operator=(other);
            delete _brain;                      // free old brain
            _brain = new Brain(*other._brain);  // allocate new brain, copy contents
        }
        return *this;
    }
    
    ~Dog() {
        delete _brain;  // each Dog owns and deletes its own brain
    }
};
```

### After deep copy:

```
Original Dog:
  [ vptr   ]
  [ _brain ] → [0x1234: Brain A with 100 strings]

Deep copy of Dog:
  [ vptr   ]
  [ _brain ] → [0x5678: Brain B — DIFFERENT object, same content]
```

Now they're fully independent. Modifying one doesn't affect the other. Destroying one doesn't affect the other.

### The Brain class itself also needs deep copy

If Brain contains a `std::string[100]`, strings manage their own memory internally. The default compiler-generated copy for Brain will do element-wise copying of the strings, which is correct (since `std::string` has its own proper copy constructor). So Brain's default copy is fine in this case.

But if Brain stored `char*` arrays instead of `std::string`, Brain itself would need a custom deep copy.

---

## 7. Abstract Classes and Pure Virtual Functions

### The problem that abstract classes solve

With the Animal/Dog/Cat hierarchy, `Animal` has a `makeSound()` function. But what sound does a generic "Animal" make? It's undefined. Yet if we write:

```cpp
Animal a;
a.makeSound();  // what does this print? "..." ? That's meaningless.
```

...we can construct an `Animal` object that makes no meaningful sound. This shouldn't be allowed. An `Animal` in this context is a conceptual category, not a concrete thing that can be instantiated.

**Pure virtual functions** enforce this:

```cpp
class Animal {
public:
    virtual ~Animal() {}
    virtual void makeSound() const = 0;  // pure virtual — "= 0" makes it abstract
};
```

The `= 0` syntax declares the function as **pure virtual**. A class with at least one pure virtual function is called an **abstract class**.

**Properties of abstract classes:**
1. Cannot be instantiated — `Animal a;` is a **compile error**.
2. Can still have constructors (used when constructing derived objects).
3. Can still have non-virtual and non-pure-virtual member functions.
4. Can still have data members.
5. Derived classes MUST implement all pure virtual functions, or they are also abstract.

```cpp
Animal a;      // ERROR: cannot instantiate abstract class
Animal* a;     // Fine — pointer to abstract class is OK
Animal& a = *dogPtr;  // Fine — reference to abstract class is OK

class Concrete : public Animal {
public:
    virtual void makeSound() const {
        std::cout << "Woof!" << std::endl;
    }
    // makeSound is implemented — Concrete is NOT abstract, CAN be instantiated
};

Concrete c;  // Fine — all pure virtual functions are implemented
```

### Can a pure virtual function have a body?

Yes, this is a little-known feature. A pure virtual function can have an implementation:

```cpp
class Animal {
public:
    virtual void makeSound() const = 0;  // pure virtual...
};

void Animal::makeSound() const {         // ...but with a body
    std::cout << "(silent)" << std::endl;
}
```

Derived classes must still implement it (they can't inherit the class as-is), but they can call the base version with `Animal::makeSound()` if needed. This pattern is rare but valid.

---

## 8. Interfaces — Pure Abstract Classes

In many languages (Java, C#), there is an `interface` keyword that defines a contract: a list of methods a class promises to implement, without any data or implementation.

**C++ has no `interface` keyword.** However, you can simulate interfaces perfectly using a **pure abstract class** — a class where ALL methods are pure virtual, there are no data members, and there is a virtual destructor.

```cpp
// This IS a C++ interface
class ICharacter {
public:
    virtual ~ICharacter() {}                                  // virtual destructor
    virtual std::string const& getName() const = 0;           // pure virtual
    virtual void equip(AMateria* m) = 0;                      // pure virtual
    virtual void unequip(int idx) = 0;                        // pure virtual
    virtual void use(int idx, ICharacter& target) = 0;        // pure virtual
    // NO data members
    // NO non-virtual member functions (except maybe static helpers)
};
```

### Why interfaces are powerful

1. **Decoupling:** Code that uses `ICharacter*` doesn't need to know about `Character`, `Robot`, `NPC`, or any other implementing class. It only knows the interface contract.

2. **Multiple interface "inheritance":** While C++ doesn't support multiple inheritance of implementation well (the diamond problem), inheriting from multiple pure abstract classes (interfaces) is clean and widely done:
```cpp
class Character : public ICharacter, public ISerializable, public IDrawable {
    // implements all three interfaces
};
```

3. **Substitutability:** Any class that implements `ICharacter` can be used wherever an `ICharacter*` is expected. New implementations can be added without changing existing code.

### Interface vs Abstract Class — the distinction

| | Abstract Class | Interface (Pure Abstract) |
|---|---|---|
| Data members | Yes | No |
| Non-pure virtual methods | Yes | No |
| Pure virtual methods | At least one | All methods |
| Purpose | Partial implementation + contract | Contract only |
| Example | `AMateria` (has `type` member, `getType()`) | `ICharacter` (pure contract) |

In CPP04, `AMateria` is an **abstract class** (has a protected `type` member, has a `getType()` implementation), while `ICharacter` and `IMateriaSource` are **interfaces** (pure abstract — no data, no implementations).

### The convention for naming

The `I` prefix (`ICharacter`, `IMateriaSource`) signals "this is an interface." The `A` prefix (`AMateria`, `AAnimal`) signals "this is an abstract class." These are conventions, not C++ rules.

---

## 9. The Prototype Pattern — clone()

### The problem

You have an `AMateria*` pointer. You don't know if it's an `Ice` or a `Cure`. You want to make a copy of whatever it points to, correctly typed.

```cpp
AMateria* m = /* could be Ice* or Cure* */;

// This DOESN'T work — it copies to AMateria, slicing the derived type
// AMateria copy = *m;

// You need:
AMateria* copy = m->clone();  // calls Ice::clone() or Cure::clone() via vtable
```

### The Prototype pattern

Each concrete class implements a `clone()` method that returns a `new` instance of its own type:

```cpp
class AMateria {
public:
    virtual AMateria* clone() const = 0;  // pure virtual — every subclass must implement
};

class Ice : public AMateria {
public:
    virtual Ice* clone() const {       // covariant return type — Ice* is valid
        return new Ice(*this);         // copy-constructs a new Ice
    }
};

class Cure : public AMateria {
public:
    virtual Cure* clone() const {
        return new Cure(*this);
    }
};

// Usage — the caller doesn't know the actual type:
AMateria* original = /* some AMateria */;
AMateria* copy = original->clone();   // vtable dispatch → correct type created
```

**Why `new` and not a stack object?** Because the caller holds an `AMateria*`, the returned object must have a lifetime that outlasts the function call. Returning a stack-allocated object through a pointer would be a dangling pointer.

**The caller owns the returned object** and is responsible for `delete`-ing it. This is an important memory ownership rule to track.

---

## 10. Memory Ownership with Polymorphic Objects

CPP04 ex03 introduces a subtle memory management challenge: `unequip()` removes a Materia from the character's inventory but does NOT delete it. This means there are "floating" Materia objects on the "floor" that must still be deleted eventually.

This teaches the concept of **memory ownership** — who is responsible for deleting an object.

### The ownership rules in ex03

1. `MateriaSource::learnMateria(AMateria*)` — MateriaSource takes ownership. It copies the materia and owns the copy.
2. `MateriaSource::createMateria()` — returns a new object. The CALLER takes ownership.
3. `Character::equip(AMateria*)` — the Character takes ownership of the Materia.
4. `Character::unequip(int)` — releases ownership WITHOUT deleting. Caller must save the pointer first.
5. `Character` destructor — deletes all equipped Materias.

```cpp
// CORRECT pattern for unequip:
AMateria* dropped = nullptr;

// Save the pointer BEFORE unequipping
for (int i = 0; i < 4; i++) {
    if (me->getMateria(i) != nullptr)
        dropped = me->getMateria(i);  // save address
}
me->unequip(someIdx);   // removes from inventory, does NOT delete
// ...later...
delete dropped;          // you are responsible for this

// WRONG pattern:
me->unequip(someIdx);   // removed from inventory
// Pointer lost! Memory leaked.
```

The challenge is that in C++98, there are no smart pointers (those came in C++11). You must manually track all these raw pointers. This is why the subject warns: "Save the addresses before calling unequip(), or anything else, but don't forget that you have to avoid memory leaks."

---

## 11. WrongAnimal — The Demonstration of What NOT to Do

Ex00 asks you to implement `WrongAnimal` and `WrongCat` alongside the correct `Animal`/`Dog`/`Cat`. This is a pedagogical exercise to make you feel the difference between virtual and non-virtual dispatch.

```cpp
// WrongAnimal — makeSound is NOT virtual
class WrongAnimal {
public:
    std::string type;
    void makeSound() const {  // NOT virtual
        std::cout << "..." << std::endl;
    }
};

class WrongCat : public WrongAnimal {
public:
    WrongCat() { type = "WrongCat"; }
    void makeSound() const {  // NOT an override — it HIDES WrongAnimal::makeSound
        std::cout << "Meow (wrong)!" << std::endl;
    }
};

// Behavior:
const WrongAnimal* wc = new WrongCat();
wc->makeSound();     // Prints "..." — WrongAnimal's version!
                     // Because makeSound is not virtual, dispatch is static.
                     // The compiler sees WrongAnimal* and calls WrongAnimal::makeSound.

// vs. the correct version:
const Animal* c = new Cat();
c->makeSound();      // Prints "Meow!" — Cat's version, because makeSound IS virtual
```

**Why does hiding differ from overriding?**

When you define a function in a derived class with the same name as a non-virtual function in the base class, you are **hiding** it, not overriding it. The function exists in the derived class, but only when accessed through a Derived pointer/reference — not through a Base pointer/reference.

```cpp
WrongCat wcat;
wcat.makeSound();           // "Meow (wrong)!" — accessed through WrongCat directly

WrongAnimal* wa = &wcat;
wa->makeSound();            // "..." — accessed through WrongAnimal*, hiding kicks in

// In contrast, with virtual:
Cat cat;
Animal* a = &cat;
a->makeSound();             // "Meow!" — override kicks in
```

The WrongAnimal exercise burns this distinction into muscle memory. You FEEL the behavior difference, not just read about it.

---

## 12. Mental Model Summary

Think of subtype polymorphism as a **dispatch table that the object carries with it.**

Every polymorphic object has a hidden pointer to its class's "function directory" (vtable). When you call a virtual function through a base pointer, the program looks up "what's in slot #3 of this object's directory?" rather than "what's in slot #3 of Animal's directory?" This one-level indirection is what makes runtime polymorphism work.

The whole system rests on three pillars:

**1. Virtual functions** — opt-in mechanism for runtime dispatch. Without `virtual`, all dispatch is compile-time based on the declared type.

**2. Virtual destructor** — makes the dispatch system work correctly for cleanup. Without it, deleting a derived object through a base pointer leaks the derived part.

**3. Pure virtual functions** — express "this method must be implemented by subclasses." A class with at least one pure virtual method is abstract and cannot be instantiated. A class with ALL pure virtual methods and no data is an interface.

The critical mental shift from CPP00-CPP03 to CPP04 is moving from thinking about objects as "things that exist" to thinking about objects as "things that respond to messages according to their actual type, not their declared type."

```
Animal* zoo[3] = { new Dog(), new Cat(), new Animal() };  // (Animal is abstract in ex02 — this fails)
// With virtual, calling zoo[i]->makeSound() calls the RIGHT version for each
// With non-virtual, it always calls Animal::makeSound regardless of actual type
```

**The four rules to always remember:**
1. If a class is designed to be used polymorphically through a base pointer — make its destructor **virtual**.
2. If a method should behave differently in derived classes — make it **virtual**.
3. If a class represents a concept that makes no sense to instantiate directly — make at least one method **pure virtual** (= 0).
4. If a class has pointer members that it owns — implement **deep copy** (copy constructor + assignment operator).

---

*End of CPP04 Reference — Subtype Polymorphism, Abstract Classes & Interfaces*
