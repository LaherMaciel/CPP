# CPP08 — STL: Containers, Iterators & Algorithms
### A Deep Reference Document

---

## Table of Contents
1. [What is the STL?](#1-what-is-the-stl)
2. [Containers — The Big Picture](#2-containers--the-big-picture)
3. [Sequence Containers](#3-sequence-containers)
4. [Associative Containers](#4-associative-containers)
5. [Container Adapters](#5-container-adapters)
6. [Iterators — The Glue](#6-iterators--the-glue)
7. [Algorithms — The <algorithm> Header](#7-algorithms--the-algorithm-header)
8. [Iterator Invalidation — The Most Dangerous STL Pitfall](#8-iterator-invalidation--the-most-dangerous-stl-pitfall)
9. [Choosing the Right Container](#9-choosing-the-right-container)
10. [Extending STL Containers — Inheritance](#10-extending-stl-containers--inheritance)
11. [Mental Model Summary](#11-mental-model-summary)

---

## 1. What is the STL?

The **Standard Template Library** is a set of template classes and functions that form a large part of the C++ standard library. It was designed by Alexander Stepanov around a single powerful idea:

> **Algorithms and containers should be decoupled from each other, connected by iterators.**

Without this design, you'd need `sortVector`, `sortList`, `sortDeque` as separate functions. With it, you have one `std::sort` that works on any data structure that provides the right kind of iterators.

The STL has three main components:
1. **Containers** — data structures that store elements.
2. **Iterators** — objects that traverse containers (the connector between the other two).
3. **Algorithms** — functions that operate on ranges of elements via iterators.

---

## 2. Containers — The Big Picture

All STL containers share a common design:
- They are **class templates** — you specify the element type: `std::vector<int>`, `std::list<std::string>`.
- They manage their own memory — no manual `new`/`delete`.
- They own their elements — when the container is destroyed, so are all its elements.
- They have a **common interface**: `size()`, `empty()`, `begin()`, `end()`, `clear()`.

### Container categories

**Sequence containers** — maintain insertion order (or explicit order you set):
- `std::vector` — dynamic array
- `std::list` — doubly linked list
- `std::deque` — double-ended queue

**Associative containers** — maintain sorted order, fast lookup by key:
- `std::set` — sorted unique elements
- `std::multiset` — sorted elements, duplicates allowed
- `std::map` — sorted key-value pairs, unique keys
- `std::multimap` — sorted key-value pairs, duplicate keys allowed

**Container adapters** — interfaces built on top of other containers:
- `std::stack` — LIFO stack
- `std::queue` — FIFO queue
- `std::priority_queue` — heap-based priority queue

---

## 3. Sequence Containers

### std::vector — the workhorse

`std::vector` is a dynamically sized array. Elements are stored **contiguously in memory**, just like a C array, which makes random access (`v[i]`) extremely fast.

```cpp
#include <vector>

std::vector<int> v;           // empty vector
std::vector<int> v(5);        // 5 elements, default-initialized to 0
std::vector<int> v(5, 42);    // 5 elements, all equal to 42

v.push_back(10);              // add to the end — O(amortized 1)
v.push_back(20);
v.push_back(30);

v[1]         // = 20 — no bounds check — O(1)
v.at(1)      // = 20 — bounds check (throws std::out_of_range) — O(1)
v.front()    // = 10 — first element
v.back()     // = 30 — last element
v.size()     // = 3 — number of elements
v.capacity() // >= 3 — allocated space (may be more than size)

v.pop_back()              // remove last element — O(1)
v.insert(v.begin(), 5);   // insert 5 at front — O(n) — expensive!
v.erase(v.begin());       // erase first element — O(n) — expensive!
```

**How vector grows:** When `push_back` exceeds capacity, vector allocates a larger buffer (typically 2x the old size), copies all elements, and deallocates the old buffer. The amortized cost of `push_back` is O(1), but individual calls can be O(n) when reallocation occurs.

```
Initial:   [10|20|30]  size=3, capacity=4
push_back(40): [10|20|30|40]  size=4, capacity=4
push_back(50): reallocation!
    1. Allocate new buffer of size 8
    2. Copy all 4 elements to new buffer
    3. Add 50
    4. Delete old buffer
    Result: [10|20|30|40|50|__|__|__]  size=5, capacity=8
```

**Use vector when:**
- You need random access by index.
- You mostly add/remove at the END.
- Cache performance matters (contiguous memory).
- This is the default container — when in doubt, start with vector.

### std::list — the doubly linked list

`std::list` stores elements as nodes linked by pointers. Elements are **NOT contiguous** in memory.

```cpp
#include <list>

std::list<int> lst;

lst.push_back(10);   // add to end — O(1)
lst.push_front(5);   // add to front — O(1)  ← vector can't do this cheaply
lst.pop_back();      // remove from end — O(1)
lst.pop_front();     // remove from front — O(1)

// No operator[]! Random access is O(n) — must iterate
// lst[2]  ← DOES NOT COMPILE

// Insert/erase anywhere in O(1) IF you have an iterator to that position
std::list<int>::iterator it = lst.begin();
++it;  // advance to second element
lst.insert(it, 99);  // insert 99 before second element — O(1)
lst.erase(it);       // erase the element it points to — O(1)
```

**Memory layout:**
```
5 → 10 → 20 → 30 → nullptr
↑           ↑
These nodes are scattered throughout the heap, connected by pointers.
Poor cache behavior — each node access may be a cache miss.
```

**Use list when:**
- You need frequent insertions/deletions at ARBITRARY positions.
- You have iterators to the insertion/deletion points.
- You never need random access by index.

### std::deque — double-ended queue

`std::deque` (pronounced "deck") supports fast insertion/deletion at BOTH ends AND random access. It's a sequence of fixed-size chunks.

```cpp
#include <deque>

std::deque<int> dq;

dq.push_back(10);   // add to end — O(1)
dq.push_front(5);   // add to front — O(1)  ← unlike vector
dq.pop_back();      // remove from end — O(1)
dq.pop_front();     // remove from front — O(1)

dq[0]   // random access — O(1), like vector
dq.at(0) // with bounds check
```

**Use deque when:**
- You need random access AND fast insertion/deletion at both ends.
- `std::queue` uses deque as its underlying container by default.

---

## 4. Associative Containers

### std::map — sorted key-value store

`std::map<Key, Value>` stores key-value pairs, sorted by key. Internally implemented as a **balanced binary search tree** (usually red-black tree). This means:
- All keys are unique.
- Keys are sorted in ascending order.
- Lookup, insertion, deletion: all **O(log n)**.

```cpp
#include <map>

std::map<std::string, int> ages;

// Insert:
ages["Alice"] = 30;
ages["Bob"] = 25;
ages.insert(std::make_pair("Charlie", 35));

// Lookup:
int aliceAge = ages["Alice"];    // = 30 — inserts default value if key not found!
int bobAge = ages.at("Bob");     // = 25 — throws if key not found (safer)

// Check existence:
if (ages.find("Alice") != ages.end()) {
    // Alice exists
}
if (ages.count("Alice") > 0) {  // count is 0 or 1 for std::map
    // Alice exists
}

// Iterate — always in sorted key order:
for (std::map<std::string, int>::iterator it = ages.begin(); it != ages.end(); ++it) {
    std::cout << it->first << ": " << it->second << std::endl;
}
// Output: Alice: 30, Bob: 25, Charlie: 35 (alphabetical order)

// Erase:
ages.erase("Bob");
```

**The `operator[]` trap:** `ages["NewKey"]` inserts a default-constructed value if "NewKey" doesn't exist. This is convenient but can create unintended entries. Prefer `ages.at("NewKey")` when you expect the key to exist.

### std::set — sorted unique elements

Like `std::map` but only stores keys, no values. Same O(log n) complexity.

```cpp
#include <set>

std::set<int> s;
s.insert(5);
s.insert(3);
s.insert(8);
s.insert(3);  // duplicate — silently ignored

// s contains: {3, 5, 8} — sorted, no duplicates
```

---

## 5. Container Adapters

Container adapters are not new data structures — they are **interfaces** that restrict or adapt an underlying container.

### std::stack — LIFO (Last In, First Out)

```cpp
#include <stack>

std::stack<int> s;  // uses std::deque internally by default
// std::stack<int, std::vector<int>> s;  // use vector as underlying container

s.push(10);    // add to top
s.push(20);
s.push(30);

s.top()   // = 30 — view top without removing
s.pop()   // remove top — returns void (not the value!)
s.size()  // = 2 (after pop)
s.empty() // false

// No iterators! You can't iterate a stack by design.
// The only operations are push, pop, top.
```

**LIFO behavior:** Last element pushed is first to be popped. Essential for:
- Function call tracking (the actual call stack in your CPU is LIFO)
- Expression evaluation (Reverse Polish Notation)
- Undo/redo systems
- Depth-first search

### std::queue — FIFO (First In, First Out)

```cpp
#include <queue>

std::queue<int> q;

q.push(10);    // add to back
q.push(20);
q.push(30);

q.front()  // = 10 — view front
q.back()   // = 30 — view back
q.pop()    // remove front — first in, first out
```

---

## 6. Iterators — The Glue

An iterator is an object that acts like a pointer to an element in a container. It provides a uniform way to traverse any container, regardless of its internal structure.

### The iterator concept

All iterators support:
```cpp
*it      // dereference — get the element
++it     // advance to next element (prefix)
it++     // advance to next element (postfix — prefer prefix for performance)
it != it2  // compare two iterators
it == it2  // compare for equality
```

`begin()` returns an iterator to the first element.
`end()` returns an iterator to **one past the last element** (a sentinel — never dereference it!).

```cpp
std::vector<int> v = {10, 20, 30, 40, 50};

// Manual iteration:
std::vector<int>::iterator it = v.begin();
while (it != v.end()) {
    std::cout << *it << std::endl;
    ++it;
}

// For loop style:
for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
    std::cout << *it << " ";
}
```

### Iterator categories

Not all iterators support the same operations. There are five categories, from least to most capable:

**1. Input Iterator** — read once, forward only.
- Supports: `*it` (read), `++it`, `it != end`
- Cannot go backward. Cannot reread.
- Example: reading from a file stream, reading from `std::cin`

**2. Output Iterator** — write once, forward only.
- Supports: `*it = value` (write), `++it`
- Cannot read, cannot go backward.
- Example: writing to `std::cout` via `ostream_iterator`

**3. Forward Iterator** — read/write, forward only, multipass.
- Supports: read AND write, `++it`, can iterate multiple times
- Example: `std::forward_list`, `std::unordered_map`

**4. Bidirectional Iterator** — forward AND backward.
- Supports everything in Forward, plus `--it`
- Example: `std::list`, `std::map`, `std::set`

**5. Random Access Iterator** — can jump to any position in O(1).
- Supports everything in Bidirectional, plus:
  - `it + n`, `it - n` — move by n steps
  - `it[n]` — access element n steps away
  - `it1 - it2` — compute distance between iterators
  - `it1 < it2` — compare positions
- Example: `std::vector`, `std::deque`, raw arrays

Algorithms require specific iterator categories. `std::sort` requires Random Access Iterators (so it works on vector, deque, raw arrays — but NOT on list or map). `std::find` only requires Input Iterators (works on everything).

### const_iterator

For read-only access, use `const_iterator`:

```cpp
const std::vector<int> v = {1, 2, 3};

// iterator would allow modification — won't compile for const container
// std::vector<int>::iterator it = v.begin();  // ERROR

// const_iterator for read-only traversal:
std::vector<int>::const_iterator it = v.begin();
// *it = 99;  // ERROR — cannot modify through const_iterator
std::cout << *it << std::endl;  // OK — reading is fine
```

---

## 7. Algorithms — The `<algorithm>` Header

Algorithms operate on iterator ranges, not on containers directly. A range is defined by `[first, last)` — the first iterator points to the first element, `last` is one past the end.

```cpp
#include <algorithm>
#include <vector>

std::vector<int> v = {5, 3, 8, 1, 9, 2, 7, 4, 6};

// Sort in ascending order — requires random access iterator
std::sort(v.begin(), v.end());
// v = {1, 2, 3, 4, 5, 6, 7, 8, 9}

// Sort in descending order — using a comparator
std::sort(v.begin(), v.end(), std::greater<int>());
// v = {9, 8, 7, 6, 5, 4, 3, 2, 1}

// Find an element — returns iterator to first match, or end() if not found
std::vector<int>::iterator it = std::find(v.begin(), v.end(), 5);
if (it != v.end()) {
    std::cout << "Found: " << *it << std::endl;
}

// Count occurrences
int count = std::count(v.begin(), v.end(), 5);  // = 1

// Check if any element satisfies a condition
// (using a function pointer or functor — no lambdas in C++98)
bool greaterThan8(int n) { return n > 8; }
bool hasLarge = std::find_if(v.begin(), v.end(), greaterThan8) != v.end();

// Min and max elements
std::vector<int>::iterator minIt = std::min_element(v.begin(), v.end());
std::vector<int>::iterator maxIt = std::max_element(v.begin(), v.end());
std::cout << "Min: " << *minIt << ", Max: " << *maxIt << std::endl;

// Reverse the range
std::reverse(v.begin(), v.end());

// Fill with a value
std::fill(v.begin(), v.end(), 0);  // all elements = 0

// Accumulate (sum) — in <numeric>
#include <numeric>
int sum = std::accumulate(v.begin(), v.end(), 0);  // 0 is the starting value
```

### Key insight about algorithms

`std::sort(v.begin(), v.end())` doesn't know it's sorting a `std::vector`. It only knows:
- `v.begin()` gives it a random-access iterator
- `v.end()` gives it the sentinel
- Elements support `<` for comparison

This means `std::sort` works equally well on `std::deque`, on raw arrays (`std::sort(arr, arr + n)`), and on any range that provides random access iterators. The **same algorithm, any container** principle.

---

## 8. Iterator Invalidation — The Most Dangerous STL Pitfall

**Iterator invalidation** occurs when an operation on a container makes previously obtained iterators invalid (pointing to garbage or out-of-range memory). Using an invalidated iterator is undefined behavior.

### Vector invalidation rules

```cpp
std::vector<int> v = {1, 2, 3, 4, 5};
std::vector<int>::iterator it = v.begin() + 2;  // points to element 3

// DANGER: push_back may cause reallocation
v.push_back(6);
// If reallocation happened, it is NOW INVALID (dangling pointer to old buffer)
// *it  — undefined behavior!

// Safe: reserve space first to prevent reallocation
v.reserve(10);
std::vector<int>::iterator it2 = v.begin() + 2;
v.push_back(7);   // no reallocation — it2 is still valid

// ALWAYS invalidates when reallocation happens
// Invalidates iterators at and after insertion point
v.insert(v.begin(), 0);  // it2 is now invalid (element shifted)

// Erase invalidates at and after the erased position
v.erase(v.begin());  // all iterators after begin() are now invalid
```

### List invalidation rules (much safer)

```cpp
std::list<int> lst = {1, 2, 3, 4, 5};
std::list<int>::iterator it = lst.begin();
++it; ++it;  // points to element 3

lst.push_back(6);   // no invalidation — list doesn't reallocate
lst.push_front(0);  // no invalidation

// Only insertion is NEVER invalidating for list
// Erasure invalidates ONLY the iterator to the erased element
lst.erase(it);      // it is now invalid
// All OTHER iterators are still valid
```

### Map/set invalidation

Same as list — insert doesn't invalidate, erase only invalidates the iterator to the erased element.

**The golden rule:** After any modification to a container, treat all iterators as potentially invalid unless you know the specific rules for that container.

---

## 9. Choosing the Right Container

```
Do you need to store key-value pairs?
├─ Yes, with unique keys → std::map (sorted) or std::unordered_map (C++11, O(1) average)
└─ No, just values →

    Do you need sorted order with fast lookup?
    ├─ Yes → std::set
    └─ No →
    
        Do you need random access by index?
        ├─ Yes →
        │   Do you add/remove at both ends?
        │   ├─ Yes → std::deque
        │   └─ No → std::vector  ← DEFAULT CHOICE
        └─ No →
            Do you need O(1) insert/erase anywhere?
            ├─ Yes → std::list (bidirectional)
            └─ No, just at one end →
                LIFO? → std::stack
                FIFO? → std::queue
```

**Rule of thumb:** Start with `std::vector`. Switch to something else only when profiling shows vector is a bottleneck, or when the semantics require it (you need sorted key-value pairs → use map).

---

## 10. Extending STL Containers — Inheritance

CPP08 includes making `std::stack` iterable. `std::stack` doesn't expose iterators by design. The solution is to **inherit from it** and expose the underlying container's iterators.

`std::stack` (and other adapters) have a `protected` member named `c` which IS the underlying container:

```cpp
template <typename T>
class MutantStack : public std::stack<T> {
public:
    // std::stack's underlying container is protected member 'c'
    // It is of type std::stack's Container template parameter (deque by default)
    
    typedef typename std::stack<T>::container_type::iterator iterator;
    typedef typename std::stack<T>::container_type::const_iterator const_iterator;
    
    iterator begin() { return this->c.begin(); }
    iterator end()   { return this->c.end(); }
    
    const_iterator begin() const { return this->c.begin(); }
    const_iterator end()   const { return this->c.end(); }
};
```

The `typename` before `std::stack<T>::container_type::iterator` is necessary in C++98 templates to tell the compiler that `container_type::iterator` is a type (not a static member or something else). This is the **dependent name** problem in templates.

**Why inherit from std::stack rather than wrapping it?**
Inheriting means `MutantStack` already has all the `push`, `pop`, `top`, `size`, `empty` operations — we only add `begin()` and `end()`. Composition (has-a) would require forwarding all those functions manually.

**Note:** Inheriting from STL containers is generally discouraged in production code (they have no virtual destructors, so polymorphic deletion would be UB). Here it's acceptable because we're adding functionality, not overriding behavior, and we're not using it polymorphically through a base pointer.

---

## 11. Mental Model Summary

Think of the STL as a **city infrastructure**:

**Containers are warehouses** — they store things in different configurations optimized for different access patterns:
- Vector: warehouse with numbered shelf locations (random access by index)
- List: treasure hunt where each item has a note pointing to the next item
- Map: alphabetically sorted filing cabinet (find by key)
- Stack: a stack of trays — you can only add or remove from the top

**Iterators are forklifts** — they navigate the warehouses. Different warehouses need different types of forklifts:
- Some forklifts can only go forward (input iterator)
- Some can go backward too (bidirectional)
- Some can jump directly to any shelf (random access)

**Algorithms are procedures** — they tell the forklifts what to do:
- "Sort all items in this range"
- "Find the item with this label"
- "Count how many items satisfy this condition"

The crucial design: **procedures don't need to know which warehouse they're in**. They just need the right type of forklift (iterator). This is the elegance and power of the STL.

**Performance cheat sheet:**

| Operation | vector | list | deque | map/set |
|---|---|---|---|---|
| Random access [i] | O(1) | O(n) | O(1) | N/A |
| Push back | O(1)* | O(1) | O(1) | N/A |
| Push front | O(n) | O(1) | O(1) | N/A |
| Insert middle | O(n) | O(1)† | O(n) | N/A |
| Find by value | O(n) | O(n) | O(n) | O(n) |
| Find by key | N/A | N/A | N/A | O(log n) |
| Sort | O(n log n) | O(n log n)‡ | O(n log n) | always sorted |

\* amortized  
† requires iterator to position  
‡ list has its own sort member function

---

*End of CPP08 Reference — STL Containers, Iterators & Algorithms*
