# CPP09 — STL Applied: Real Algorithms & Container Strategy
### A Deep Reference Document

---

## Table of Contents
1. [The CPP09 Module-Specific Rule](#1-the-cpp09-module-specific-rule)
2. [std::map for Date-Based Lookups (lower_bound)](#2-stdmap-for-date-based-lookups-lower_bound)
3. [Reverse Polish Notation and std::stack](#3-reverse-polish-notation-and-stdstack)
4. [Sorting Algorithms — Theory Before Ford-Johnson](#4-sorting-algorithms--theory-before-ford-johnson)
5. [The Ford-Johnson Algorithm (Merge-Insert Sort)](#5-the-ford-johnson-algorithm-merge-insert-sort)
6. [Measuring Time in C++](#6-measuring-time-in-c)
7. [Parsing and Input Validation Patterns](#7-parsing-and-input-validation-patterns)
8. [Container Selection for CPP09](#8-container-selection-for-cpp09)
9. [Mental Model Summary](#9-mental-model-summary)

---

## 1. The CPP09 Module-Specific Rule

CPP09 has a unique constraint that doesn't exist in any other module:

> **Once a container is used in one exercise, it cannot be used in any other exercise of this module.**

This means you must plan container use across all three exercises BEFORE you write a line of code. The subject itself warns: "It is advisable to read the subject in its entirety before doing the exercises."

You have three exercises needing at least one container each (ex02 needs two):
- ex00: Bitcoin Exchange
- ex01: Reverse Polish Notation
- ex02: PmergeMe (two different containers)

You have these common containers: `std::map`, `std::stack`, `std::vector`, `std::deque`, `std::list`, `std::queue`, `std::set`.

A common reasonable allocation:
- ex00: `std::map` (perfect for date→price lookup)
- ex01: `std::stack` (perfect for RPN evaluation)
- ex02: `std::vector` + `std::deque` (or `std::list`)

But this is your decision. Read all three exercises, then decide.

---

## 2. std::map for Date-Based Lookups (lower_bound)

The Bitcoin Exchange exercise requires looking up a price by date, where the exact date might not exist in the database — you should use the closest date that doesn't exceed the input date.

This is exactly what `std::map::lower_bound` is for.

### lower_bound explained

```cpp
std::map<K, V>::iterator lower_bound(const K& key);
```

Returns an iterator to the **first element whose key is NOT LESS THAN** `key`. In other words, the first element that is `>= key`.

```cpp
std::map<std::string, double> prices;
prices["2011-01-03"] = 0.30;
prices["2011-01-09"] = 0.32;
prices["2012-01-11"] = 7.10;
prices["2013-06-15"] = 100.0;

// Looking up "2011-01-05" — exact key doesn't exist
auto it = prices.lower_bound("2011-01-05");
// it points to "2011-01-09" (first key >= "2011-01-05")
// But we want the LOWER date — the one BEFORE this

if (it != prices.begin()) {
    --it;  // go back one — now points to "2011-01-03"
}
// it->first  = "2011-01-03"
// it->second = 0.30
```

**The pattern for "find closest key that does not exceed target":**

```cpp
std::map<std::string, double>::iterator findPrice(
    const std::map<std::string, double>& db, const std::string& date) 
{
    // Find first entry >= date
    std::map<std::string, double>::const_iterator it = db.lower_bound(date);
    
    if (it == db.end()) {
        // All dates in DB are < date — use the last entry
        --it;
        return it;
    }
    
    if (it->first == date) {
        // Exact match found
        return it;
    }
    
    if (it == db.begin()) {
        // date is before all entries in DB — no valid entry
        return db.end();  // signal "not found"
    }
    
    // Go to the entry just before — the closest lower date
    --it;
    return it;
}
```

This works because `std::map` always keeps keys in sorted order, and string comparison of "YYYY-MM-DD" format dates is lexicographically identical to chronological order (as long as format is consistent).

### upper_bound for completeness

```cpp
map.upper_bound(key);  // returns first element with key STRICTLY GREATER THAN key
map.lower_bound(key);  // returns first element with key GREATER THAN OR EQUAL TO key
```

These are also available for `std::set`, `std::multimap`, `std::multiset`.

---

## 3. Reverse Polish Notation and std::stack

### What is RPN?

Reverse Polish Notation (RPN), also called **postfix notation**, is a way of writing mathematical expressions where operators come AFTER their operands, not between them.

| Standard (infix) | RPN (postfix) |
|---|---|
| `3 + 4` | `3 4 +` |
| `(3 + 4) * 5` | `3 4 + 5 *` |
| `8 * 9 - 9 - 9 - 9 - 4 + 1` | `8 9 * 9 - 9 - 9 - 4 - 1 +` |

RPN doesn't need parentheses — the order of operations is unambiguous from the token order alone.

### Why std::stack is perfect for RPN

The evaluation algorithm uses a stack of numbers:

```
Algorithm:
  For each token in the expression (left to right):
    If token is a NUMBER: push it onto the stack
    If token is an OPERATOR (+, -, *, /):
      Pop the TOP TWO numbers from the stack
      Apply the operator to them
      Push the RESULT back onto the stack
  At the end: the stack should contain exactly ONE number — the result.

Example: "3 4 + 5 *"
  Token "3" → stack: [3]
  Token "4" → stack: [3, 4]
  Token "+"  → pop 4 and 3, compute 3+4=7, push 7 → stack: [7]
  Token "5" → stack: [7, 5]
  Token "*"  → pop 5 and 7, compute 7*5=35, push 35 → stack: [35]
  End: stack has one element → result is 35
```

**Important: the order of operands with non-commutative operators**

When you pop the two operands for subtraction or division, the second-popped value is the LEFT operand and the first-popped is the RIGHT operand:

```cpp
// For "8 3 -":
// Push 8, push 3
// Encounter "-"
int b = stack.top(); stack.pop();  // b = 3 (right operand)
int a = stack.top(); stack.pop();  // a = 8 (left operand)
int result = a - b;  // 8 - 3 = 5
stack.push(result);

// If you did b - a, you'd get 3 - 8 = -5 (wrong!)
```

### Error conditions for RPN

- **Too few operands**: encountering an operator when the stack has fewer than 2 elements.
- **Too many operands**: reaching the end of the expression with more than 1 element on the stack.
- **Division by zero**: divisor is 0.
- **Invalid token**: not a single-digit number and not an operator.

```cpp
// Subject states: numbers in the input are always < 10 (single digits)
// But intermediate results and the final result can be any value
```

---

## 4. Sorting Algorithms — Theory Before Ford-Johnson

To understand Ford-Johnson, you need to understand sorting theory.

### Comparison-based sorting — the information-theoretic lower bound

Any sorting algorithm that works by **comparing pairs of elements** requires at least **O(n log n)** comparisons in the worst case. This is a mathematical proof:

- There are `n!` possible orderings of `n` elements.
- Each comparison divides the possibilities in half (best case).
- You need enough comparisons to distinguish between all `n!` possibilities.
- `n!` / 2^k ≤ 1 when k ≥ log₂(n!) ≈ n log₂(n) comparisons.

So O(n log n) is the BEST you can do with a comparison-based sort. Common O(n log n) sorts:

### Merge Sort

Divide the array in half, recursively sort each half, merge the two sorted halves:

```
[5, 3, 8, 1, 9, 2, 7, 4]
Split: [5, 3, 8, 1] and [9, 2, 7, 4]
Sort left:  [1, 3, 5, 8]
Sort right: [2, 4, 7, 9]
Merge: [1, 2, 3, 4, 5, 7, 8, 9]
```

Merging two sorted arrays of combined size n takes O(n) comparisons.
Total: T(n) = 2T(n/2) + O(n) → T(n) = O(n log n).

Merge sort is **stable** (equal elements keep their original order) and works well for linked lists.

### Insertion Sort

For a nearly-sorted or small array, insertion sort is fast in practice:

```
For i from 1 to n-1:
    Take element at position i (the "key")
    Shift all elements before i that are > key one position to the right
    Insert key in the correct position
```

- Best case: O(n) — already sorted
- Worst case: O(n²) — reverse sorted
- Small n: faster than merge sort in practice due to low overhead

**Insertion sort with binary search**: since the left portion is already sorted, you can use binary search to find the insertion position in O(log n) instead of O(n). However, the shifting is still O(n), so the overall complexity doesn't change. But the number of **comparisons** decreases!

---

## 5. The Ford-Johnson Algorithm (Merge-Insert Sort)

Ford-Johnson is not famous for being fast in practice — it's famous for using the **minimum possible number of comparisons** to sort `n` elements. It was designed to be **comparison-optimal**, not speed-optimal.

The number of comparisons it uses is within 1 of the theoretical minimum for all n.

### The Algorithm — Conceptual Overview

**Phase 1: Form and sort pairs**

1. Pair up all elements. Compare each pair — O(n/2) comparisons.
2. For each pair, call the larger element a "main element" and the smaller a "pend element."
3. Sort the main elements recursively (using Ford-Johnson itself).
   
   After sorting: you have a sorted main sequence and a set of pending elements, where each pending element is known to be ≤ its paired main element.

**Phase 2: Insert pending elements optimally**

This is the key insight. You don't insert the pending elements one by one — you insert them in a specific order determined by **Jacobsthal numbers** to minimize the number of comparisons.

**Jacobsthal numbers**: 0, 1, 1, 3, 5, 11, 21, 43, 85, 171, ...
Each number is the sum of the previous number and twice the one before that: J(n) = J(n-1) + 2·J(n-2).

The insertion order based on Jacobsthal numbers ensures that when you binary search for the insertion position of each pending element, you minimize the total comparisons.

**Why Jacobsthal numbers?**

When you have a sorted sequence of k elements and insert a new element via binary search, it takes at most ⌈log₂(k+1)⌉ comparisons. Ford-Johnson inserts in an order such that the known upper bounds (each pend ≤ its main) reduce the search space, and the Jacobsthal-based order maximizes the use of this information.

### Concrete small example: sorting 4 elements [a, b, c, d]

Optimal sorting of 4 elements requires exactly 5 comparisons (information-theoretic minimum).

```
Step 1: Compare a vs b → say b > a.  Pair: (a,b)  [1 comparison]
Step 2: Compare c vs d → say d > c.  Pair: (c,d)  [1 comparison]  
Step 3: Compare b vs d → say d > b.  Now we know d > b > a and d > c.  [1 comparison]

Sorted chain so far: [a, b, ?, d]  with c pending (c ≤ d known, c vs b and c vs a unknown)

Step 4: Compare c vs b → say c > b.  Now we know: a < b < c < d  [1 comparison]
  (if c ≤ b: compare c vs a to determine if a < c ≤ b or c ≤ a < b)

Wait — that's only 4 comparisons for the best path, 5 for the worst.
```

### Implementing Ford-Johnson with two containers

The subject requires two different containers. A typical approach:

```
Container 1 (e.g., std::vector):
    - Store and sort pairs
    - Build the main chain
    - Perform the algorithm

Container 2 (e.g., std::deque):
    - Perform the SAME sort independently with the second container
    - Used to benchmark and compare timing
```

The purpose of using two containers is to compare performance. `std::vector` has better cache locality (contiguous memory), while `std::deque` has better front-insertion performance but worse cache behavior. The comparison shows that algorithm performance depends on the container.

### The Jacobsthal insertion sequence generation

```cpp
// Jacobsthal numbers: 0, 1, 1, 3, 5, 11, 21, 43, 85, 171, ...
// J(n) = J(n-1) + 2 * J(n-2)

// Generate insertion groups based on Jacobsthal:
// Group 1: insert index 1 (1 element)
// Group 2: insert indices 3, 2 (2 elements, in reverse within group)
// Group 3: insert indices 5, 4 (2 elements)
// Group 4: insert indices 11, 10, 9, 8, 7, 6 (6 elements)
// Group 5: insert indices 21, 20, ..., 12 (10 elements)
// ...

// The key insight: by inserting in this order, each binary search has a 
// bounded search range (the known upper bound from the pairing reduces the range)
```

### Binary search for insertion (std::lower_bound)

When inserting a pending element into the main sorted chain:

```cpp
#include <algorithm>

std::vector<int> chain = {2, 5, 8, 12};
int toInsert = 7;

// Binary search: find the right position
std::vector<int>::iterator pos = std::lower_bound(chain.begin(), chain.end(), toInsert);
// pos points to 8 (first element >= 7)

// Insert before that position
chain.insert(pos, toInsert);
// chain = {2, 5, 7, 8, 12}
```

`std::lower_bound` requires a sorted range and uses binary search (O(log n) comparisons). This is the comparison-efficient insertion step.

---

## 6. Measuring Time in C++

CPP09 ex02 requires displaying the time taken to sort. In C++98:

```cpp
#include <ctime>

clock_t start = clock();

// ... sorting ...

clock_t end = clock();

// clock() returns processor time in "clock ticks"
// CLOCKS_PER_SEC is the number of clock ticks per second
double seconds = static_cast<double>(end - start) / CLOCKS_PER_SEC;
double microseconds = seconds * 1e6;

std::cout << "Time: " << microseconds << " us" << std::endl;
```

**`clock()` measures CPU time** — how much time the processor spent on your process, not wall clock time. For a compute-bound task like sorting, these are approximately the same.

For very fast operations (sorting 5 elements takes microseconds), `clock()` resolution may be too coarse. Techniques to get more accurate timing:
- Sort the same input many times and divide by the count.
- Use `gettimeofday()` for higher resolution wall time.

```cpp
#include <sys/time.h>  // for gettimeofday

struct timeval start, end;
gettimeofday(&start, NULL);

// ... sorting ...

gettimeofday(&end, NULL);

long seconds  = end.tv_sec  - start.tv_sec;
long useconds = end.tv_usec - start.tv_usec;
long elapsed  = seconds * 1000000 + useconds;

std::cout << "Time: " << elapsed << " us" << std::endl;
```

---

## 7. Parsing and Input Validation Patterns

CPP09 exercises involve parsing user input, which requires validation.

### Parsing a number from a string

```cpp
#include <sstream>
#include <string>

double parseDouble(const std::string& s) {
    std::istringstream iss(s);
    double value;
    iss >> value;
    
    if (iss.fail()) {
        // Conversion failed — not a valid number
        throw std::invalid_argument("Not a valid number: " + s);
    }
    
    // Check for trailing garbage: "3.14abc" would partially parse
    char leftover;
    if (iss >> leftover) {
        // There were extra characters after the number
        throw std::invalid_argument("Invalid number format: " + s);
    }
    
    return value;
}
```

### Parsing a date string

```cpp
bool isValidDate(const std::string& date) {
    // Expected format: "YYYY-MM-DD"
    if (date.size() != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;
    
    // Check all other positions are digits
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(date[i])) return false;
    }
    
    // Parse year, month, day
    int year  = atoi(date.substr(0, 4).c_str());
    int month = atoi(date.substr(5, 2).c_str());
    int day   = atoi(date.substr(8, 2).c_str());
    
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;  // simplified — real validation more complex
    
    return true;
}
```

### Reading a CSV file line by line

```cpp
#include <fstream>
#include <sstream>

std::ifstream file("data.csv");
if (!file.is_open()) {
    throw std::runtime_error("Could not open file");
}

std::string line;
while (std::getline(file, line)) {
    // Skip header or empty lines
    if (line.empty() || line == "date,exchange_rate") continue;
    
    // Find the comma separator
    size_t commaPos = line.find(',');
    if (commaPos == std::string::npos) {
        std::cerr << "Invalid line: " << line << std::endl;
        continue;
    }
    
    std::string date = line.substr(0, commaPos);
    std::string valueStr = line.substr(commaPos + 1);
    
    // Parse value
    double value = parseDouble(valueStr);
    
    // Store in map
    database[date] = value;
}
```

---

## 8. Container Selection for CPP09

Here's a detailed reasoning for each exercise:

### ex00 — Bitcoin Exchange

**Why `std::map<std::string, double>`?**
- You need to store date→price pairs.
- You need to look up a price by date, using the closest-or-equal date.
- `std::map` keeps keys sorted, which enables `lower_bound`.
- Lookup is O(log n) — fast even with thousands of entries.
- `std::map` naturally handles duplicate dates (each date stored once — exactly what you want for a price database).

Alternative that would work: `std::set` of pairs, but `std::map` is more natural for key-value.

### ex01 — Reverse Polish Notation  

**Why `std::stack`?**
- RPN algorithm is inherently LIFO — the last pushed numbers are the first used in the next operation.
- `std::stack` exactly models this behavior.
- Operations: only push, pop, top — `std::stack` provides exactly these.
- The constraint "numbers < 10 in input" suggests inputs are small, so performance doesn't matter — correctness and clarity do.

Could you use `std::vector` and do `back()/pop_back()`? Yes, it would work. But `std::stack` expresses intent more clearly and prevents you from accidentally using operations that don't belong (like random access).

### ex02 — PmergeMe

**Why two containers?**
The exercise explicitly wants you to observe and report performance differences between two containers running the same algorithm. The comparison demonstrates that:
- `std::vector`: excellent cache behavior (contiguous memory), but inserting in the middle is O(n).
- `std::deque`: good balance, supports efficient front operations.

For Ford-Johnson specifically, insertions into the middle of the main chain are frequent (that's the whole Phase 2). This is where vector and deque will differ in performance.

---

## 9. Mental Model Summary

CPP09 brings together everything from CPP05-CPP08. The three exercises each represent a fundamental algorithmic pattern:

**ex00: Database lookup with range queries**
The pattern: "find the closest entry ≤ target" appears everywhere — price databases, version lookups, time series data. `std::map::lower_bound` is the canonical tool. This pattern tests your understanding of sorted containers and their navigation methods.

**ex01: Stack-based expression evaluation**
The stack is one of the most fundamental data structures in computer science. The call stack itself is LIFO. Compilers use stacks for expression evaluation. Undo/redo systems use stacks. Understanding how to use `std::stack` for RPN builds intuition for all of these.

**ex02: Comparison-optimal sorting**
Ford-Johnson is not about speed — it's about minimizing comparisons. This is a lesson in algorithmic theory: O(n log n) is the complexity, but the constant factor (how many comparisons per "log n step") can still vary. Ford-Johnson minimizes this constant, approaching the information-theoretic lower bound.

The meta-lesson of CPP09: **choosing the right data structure transforms impossible problems into trivial ones.** The Bitcoin Exchange without `std::map::lower_bound` would require manual linear search or complex binary search implementations. With it, the core logic is a handful of lines.

---

*End of CPP09 Reference — STL Applied: Real Algorithms & Container Strategy*
