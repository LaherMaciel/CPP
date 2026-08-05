# CPP Module 06 - C++ Casts

## Overview

Module 06 covers the four C++ cast operators and when to use each one.

## Learning objectives

- `static_cast` — compile-time cast between compatible types
- `dynamic_cast` — safe downcast with runtime type checking (requires polymorphism)
- `reinterpret_cast` — low-level bit reinterpretation
- `const_cast` — add or remove const qualifier

## Exercises

| Exercise | Name | Key concepts |
|----------|------|-------------|
| ex00 | Conversion | Scalar type converter: int, char, float, double with edge cases |
| ex01 | Serialization | `reinterpret_cast` to serialize/deserialize a pointer as `uintptr_t` |
| ex02 | Identify real type | `dynamic_cast` to identify the concrete type of a polymorphic object |

## Compilation

```bash
cd ex00  # or ex01, ex02
make
```

Compiles with `-Wall -Wextra -Werror -std=c++98`.

## Notes

### The four casts — which one, and why

| Cast | What it does | When |
|------|--------------|------|
| `static_cast` | Real conversion the compiler can prove is meaningful (`int`→`double`, upcast). **Refuses pointer↔integer.** | Default choice |
| `dynamic_cast` | Runtime-checked downcast. Needs a polymorphic type (≥1 virtual function). Fails → `NULL` for pointers, **throws** for references | ex02 |
| `reinterpret_cast` | **No conversion at all** — relabels the same bits as another type | ex01 |
| `const_cast` | Adds/removes `const` only | — |

A C-style cast `(T)x` compiles but silently picks whichever of these fits. The named casts say *which* conversion you meant, and they're greppable. That's the whole reason the module exists.

**The relabel idea:** `static_cast` takes an apple and *turns it into* a banana. `reinterpret_cast` takes an apple and *starts calling it* a banana — same object, new label. That's why a round-trip through `reinterpret_cast` is lossless: nothing was transformed, so nothing can be lost.

### `uintptr_t` vs `unsigned int` vs `size_t`

All the `_t` names are **typedefs** (`_t` = "type") — aliases that resolve to whatever real type is correct **on this machine**. That's the point: the right size isn't the same everywhere, so the standard gives you a name meaning "whatever fits here."

Measured on a 64-bit Linux build:

```
unsigned int : 4 bytes      size_t    : 8 bytes
Data*        : 8 bytes      uintptr_t : 8 bytes
```

- **`unsigned int` is 4 bytes but a pointer is 8** — store an address in one and you throw away half of it. The round-trip returns garbage.
- **`uintptr_t`** — unsigned integer guaranteed wide enough to hold **a pointer**. Answers *"where"*.
- **`size_t`** — wide enough for the **size of the largest object** the platform allows (not "the biggest integer available"). What `sizeof`, `.size()` and `.length()` return. Answers *"how big / how many"*.

They happen to be the same width here; that isn't guaranteed. Pick by meaning.

**Why unsigned, and why not a float:** addresses are never negative, and `unsigned` doesn't apply to floating types anyway. More importantly floats *approximate* — a `double` has 53 mantissa bits, so it can't represent every 64-bit value exactly. For an address, "close" is a crash. Integers count exactly; that's what you need.

### Making a class non-instantiable (C++98)

Declare all four — default ctor, copy ctor, `operator=`, destructor — **`private` and never define them.**

Not writing them is *not* enough: **C++ silently generates public versions for you.** You aren't preventing something that was never there, you're taking away something the language hands out for free.

Two layers of defence:
- `private` → outside code fails the **access check** at compile time
- **no body** → a member or `friend` that gets past `private` fails at **link time** ("undefined reference")

C++11 replaced this with `= delete`, written right on the declaration, giving a clearer *"use of deleted function"* error and no linker trickery. Can be `public` or `private` — `private` still hides it from autocomplete.

### `dynamic_cast` — the only cast that checks (ex02)

`reinterpret_cast` **never fails**: `reinterpret_cast<A*>(p)` on a `B` object "succeeds" and hands back a bogus `A*`. You'd print the wrong type, confidently. `dynamic_cast` inspects what the object **actually is** at runtime.

It only works on **polymorphic** types — the class needs at least one virtual function. That's why the subject demands `Base` have a public virtual destructor: without it `dynamic_cast` doesn't even compile. The virtual destructor isn't decoration, it's the enabling requirement.

**Two forms, two failure modes — this is the point of the exercise:**

| Form | On failure |
|------|-----------|
| `dynamic_cast<A*>(ptr)` | returns `NULL` → test with `if` |
| `dynamic_cast<A&>(ref)` | **throws `std::bad_cast`** → `try`/`catch` |

A reference cannot be null, so there's no failure value to return — the language throws instead. That's why the reference version of `identify` needs exceptions even though it looks like it should mirror the pointer version.

**Catch `std::exception&`, not `std::bad_cast`** — `std::bad_cast` is declared in `<typeinfo>`, which this exercise forbids. `bad_cast` inherits from `std::exception`, so catching the base class works and only needs `<exception>`.

Assign to a **reference**, not a value: `A& a = dynamic_cast<A&>(p);`. Writing `A a = ...` copy-constructs a whole new object instead of referring to the existing one.

**You cannot avoid three attempts.** `dynamic_cast<T>` needs `T` at compile time — types aren't values, you can't loop over them or hold one in a variable. Three types, three casts. Any structure you build is just rearranging where those three live.

### `rand()` and the one-second trap

`srand()` / `rand()` from `<cstdlib>`, seeded with `time(NULL)` from `<ctime>`. Seed **once** in `main`.

`time(NULL)` has **one-second resolution**, so every run inside the same second gets the same seed and therefore the same first value. Run the program four times quickly and you'll see the identical result each time and think randomness is broken. The fix is to generate several objects **within one run** — the sequence advances normally there. (It also satisfies the subject's "write a program to test that everything works".)

`srand(static_cast<unsigned int>(time(NULL)))` — the cast silences `-Wconversion` on `time_t` → `unsigned int`.

### Identity vs equality

`&d == back` proves the pointers are **the same** — one object, two names. Comparing `name` and `value` would only prove two objects are **identical** — different memory that happens to match. The subject asks for the pointer comparison because it's the stronger claim.

Useful precision generally: *same* = same address, *identical* = equal contents.

### `const` and function parameters

You **cannot** pass a `const Data*` to a function taking `Data*` — the function could modify the object through it, breaking the promise `const` made. `const_cast` is the caller explicitly taking responsibility for stripping that promise.

### Small things

- `<cstdint>` is C++11. Under `-std=c++98` use **`<stdint.h>`** for `uintptr_t`.
- `std::hex` switches stream output to hexadecimal and is **sticky** — everything after it stays hex until `std::dec`. No manual conversion function needed, unlike C.
- `(void)param;` exists only to silence `-Wextra -Werror` on an unused parameter. Delete it once the parameter is genuinely used.
- A cast is an **expression producing a value** — it does not modify its operand. `reinterpret_cast<T>(x);` on its own line does nothing (`warning: statement has no effect`); you must return or assign the result.
- `static` has three unrelated meanings: on a free function = internal linkage; on a local variable = persists between calls; on a class member = callable with no object.
