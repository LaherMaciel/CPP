# CPP Module 05 - Exceptions

## Overview

Module 05 introduces exception handling in C++. The exercises model a bureaucratic system — bureaucrats, forms, and an intern — where operations can fail (a grade out of range, an unsigned form, an unknown form name) and must signal failure by **throwing typed exceptions** rather than returning error codes.

## Learning objectives

- `try` / `catch` / `throw` mechanics and how they redirect control flow
- Custom exception classes derived from `std::exception`, overriding `what()`
- Nested exception classes (scoped inside the class that throws them)
- Separating error *detection* (throw) from error *handling* (catch)
- Orthodox Canonical Form with `const` members
- Reusing an abstract base as a polymorphic hierarchy (carried over from CPP04)
- Heap ownership (`new` / `delete`) and virtual destructors

## Exercises

| Exercise | Name | Key concepts |
|----------|------|-------------|
| ex00 | Mommy, when I grow up, I want to be a bureaucrat! | `Bureaucrat` class, grade validation (1–150), `GradeTooHighException` / `GradeTooLowException`, nested exceptions |
| ex01 | Form up, maggots! | `Form` class, signing gated by grade, forward declarations to break the circular dependency |
| ex02 | No, you need form 28B, not 28C | `Form` → abstract `AForm` (pure virtual `execute`), three concrete forms, a shared `checkExecution` guard, `Bureaucrat::executeForm` |
| ex03 | At least this beats coffee-making | `Intern` creating forms by name via a function-pointer table (no if/else forest), heap ownership, virtual destructor |

## Compilation

```bash
cd ex00  # or ex01, ex02, ex03
make
```

Compiles with `-Wall -Wextra -Werror -std=c++98`. In ex02/ex03, `make fclean` also removes any generated `<target>_shrubbery` files.

## Notes

Raw notes and gotchas collected while building the module — the "oh, *that's* how it works" moments. (Polish happens in the final README pass; this is the ore.)

- **`what()` returns `const char*`, so keep the message a string literal.** Don't build it with `std::ostringstream` and `return oss.str().c_str()` — that pointer refers to a temporary `std::string` destroyed when the function returns → dangling pointer. String literals have static storage, so returning them is safe. That's why the grade numbers are hardcoded in the message rather than pulled from the named constants.

- **Randomness (ex02 Robotomy).** `rand() % 2` gives a clean 50/50. Seed **once** with `srand(time(NULL))` at the top of `main` — *not* inside `execute()`. Think of `srand` as "open the book to page N" and `rand()` as "read the next number and advance." Re-seeding every call reopens to the same page (within one second `time()` returns the same value) → identical "random" results.

- **Detection vs. handling.** `execute()` / `checkExecution()` *detect* a problem and `throw`; the caller — `Bureaucrat::executeForm`, mirroring `signForm` — *catches* and decides what to do. Shared check in the base + catch in one caller = no duplication across the three forms.

- **Virtual destructors.** `delete` on a base pointer (`AForm*`) that actually points to a derived form only runs the base destructor **unless the base destructor is `virtual`** — otherwise the derived part is never destroyed. Rule of thumb: *any class with a virtual function (virtual or pure virtual) gets a virtual destructor.* (First met in CPP04.)

- **Heap ownership (ex03).** `Intern::makeForm` returns a `new`'d object because the form must outlive the function — returning the address of a stack local would dangle. The **caller owns** the returned pointer and must `delete` it. This is the module's first use of the heap; ex00–ex02 forms all lived on the stack and were auto-destroyed at scope end.

<details>
<summary><strong>Reading array &amp; function-pointer declarations (ex03 <code>makers</code>)</strong></summary>

The scary line in ex03:

```cpp
AForm* (*makers[3])(const std::string&) = { makeShrubbery, makeRobotomy, makePresidential };
```

Read it in three parts:

```
AForm*      (*makers[3])      (const std::string&)
└─ returns  └─ array of 3     └─ each function
   this        pointers          takes this
```

→ *"an array of 3 pointers, each to a function taking `const std::string&` and returning `AForm*`."*

**The one rule:** `[]` and `()` bind tighter than `*`. Parens only change the meaning when they put `*` with the name **before** `[]` reaches it.

```cpp
int*         arr[3];   // array of 3 pointers-to-int
std::string  arr[3];   // array of 3 strings
std::string* arr[3];   // array of 3 pointers-to-string

std::string (*ptr)[3]; // POINTER to an array of 3 strings   (parens win: [3] is OUTSIDE)
std::string (*ptr[3]); // array of 3 pointers  (parens useless: [3] is INSIDE with ptr)
```

- `(*ptr)[3]` → `*` groups first → **pointer to array**
- `(*ptr[3])` → `[3]` still binds first → **array of pointers** (same as `*ptr[3]`)

So `(*makers[3])(...)` has `[3]` inside with `makers` → **array of pointers** (to functions).

**Readable version** — collapse the type with a `typedef`:

```cpp
typedef AForm* (*FormMaker)(const std::string&);
FormMaker makers[3] = { makeShrubbery, makeRobotomy, makePresidential };
```

**Why `static` on the maker functions?** File-scope `static` = internal linkage (visible only in this `.cpp`) — they're private helpers. (Note: `static` means different things on a class member and on a local variable.)

</details>
