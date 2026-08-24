# CPP09 — session handoff

**Written 2026-08-24. Read this first on the other machine.**

Deadline: **2026-10-18**. Near-term wall: webserv started 24-Aug, Beth is back.
CPP09 needs to close.

---

## 1. How we work — read this before writing any code

This is not a preference. It is the working method, and it exists for a reason:
**Laher's right arm is immobilised and he codes by voice.** Both shoulders need
surgery, roughly a year with an arm out, so this is the primary method now, not
a temporary workaround.

**Only his hands are affected. Never treat him as impaired.** He reasons, argues,
and finds bugs in my recommendations — that has happened more than once and he
was right.

### The rules

1. **ONE FUNCTION AT A TIME.** Write one function, stop, let him interrogate it.
   Never write a batch of code and then ask him to trace it.
2. **No file-dump-plus-comment-wall.** A named past failure with another AI.
   Do not reproduce it.
3. **He proposes, I type, he interrogates.** Dictation is not delegation.
   **Never invent logic — ask him for it.** No vibe coding.
4. **Do not ask for a full design up front.** He builds emergently — the same
   method that got him through minishell: parse → execute → parse → execute.
5. **Report every edit as WHAT / WHERE (`file:line`) / WHY.** One file or one
   concept per message.
6. **Never propose stopping and never offer him an exit.** He calls the stop.
7. **Fix lists come in threes, ranked by consequence, behaviour-changing first.**
   Lists of eight only half-land — measured, twice.
8. **Re-read a file immediately before reporting on it.** Reporting from a stale
   read has burned us; he caught it and he was right to.
9. Health is JARVIS's domain. Not raised here.
10. The if-else-tree rule is settled. Do not re-raise it.

Best hours are early afternoon. He goes cloudy around 20:00–21:00.

In this repo the assistant is called **Wally**.

---

## 2. Where the module stands

| exercise | state |
|---|---|
| **ex00 BitcoinExchange** | **COMPLETE.** Two NEMESIS passes, valgrind clean on all four paths, 8/8 compiler matrix incl. clang `-Weverything`, ASan+UBSan clean, 120 000 differential lines zero mismatches. Ready for evaluation. |
| **ex01 RPN** | **COMPLETE.** All three subject examples exact, `(1 + 1)` → `Error`, valgrind clean, UBSan clean, 6000-case differential fuzz zero mismatches, OCF verified. |
| **ex02 PmergeMe** | **In progress — steps 1 and 2 of 5 done.** Builds clean, runs, pairs correctly. The sort itself is not written yet. |

### ex00 evaluation defence — memorise this one

The subject shows `2011-01-03 => 3 = 2.1`, but `data.csv` has **no 2011-01-03
row**. Nearest lower is `2011-01-01,0.3`, so **0.9 is correct** and the subject's
example was generated against a different CSV. `2011-01-09 → 0.32` and
`2012-01-11 → 7.1` both exist and match exactly. Show those two.

---

## 3. ex02 — the files

Six files. The split was deliberate, at his request.

```
ex02/
  include/PmergeMe.hpp     class + declarations only; #includes PmergeMe.tpp at the bottom
  include/PmergeMe.tpp     printContainer, PmergeMe::parse, PmergeMe::makePairs
  src/PmergeMe.cpp         OCF, parseToken, nowMicroseconds, printTime
  src/PmergeMeVector.cpp   runVector, sortVector
  src/PmergeMeDeque.cpp    runDeque, sortDeque   <- sortDeque is an empty stub
  src/main.cpp             runVector then runDeque, one try/catch each
```

`nowMicroseconds` and `printTime` had to become **non-static** when the split
made them cross-translation-unit. That is why they are free functions declared
in the header.

### What currently works

Build is clean under `-Wall -Wextra -Werror -std=c++98`. `./PmergeMe 3 5 9 7 4 8 1 6 2`:

```
Before: 3 5 9 7 4 8 1 6 2
  a=5  b=3
  a=9  b=7
  a=8  b=4
  a=6  b=1
  straggler=2
After: 3 5 9 7 4 8 1 6 2
Time to process a range of 9 elements with std::vector : ... us
```

The `a= b=` lines are **temporary debug output in `sortVector`** proving the
pairing. They match the trace in `FORD_JOHNSON.md` exactly. Delete them when the
real sort lands. `After:` is unsorted because nothing sorts yet — expected.

---

## 4. What gets implemented next

Read **`README.md` → "The block representation"** first. It is the design, and
it was **prototyped and verified before being written down** — 5000 random
trials zero mismatches, worst case at n=9 is 19 comparisons which equals F(9)
and is provably optimal, n=3000 lands ~30 380 against a floor of 30 332.

### The decision already made

`std::pair` is **dropped**. It cannot grow, and the recursion pairs groups of
2, then 4, then 8. `pair<pair<int,int>,pair<int,int> >` is a different C++ type
at every level, so the recursion could not call itself.

Replacement: **`std::vector<std::vector<int> >`**. Inner vector = a *block*.

> **Invariant: a block's key is its LAST element, and that element is its
> maximum.** `block.back()` is the only thing ever compared.

Pairing is **concatenation** — `loser + winner` into one block. The loser lives
physically *inside* the winner's block, front half. That is how the a–b link
survives the recursion with no pointers, indices, or parallel arrays.

Splitting back: `half = size / 2`, front half = losers, back half = winners,
and `losers[j]` partners `winners[j]` for free.

### The function to build, one step at a time

```cpp
std::vector<std::vector<int> >
    sortBlocks(std::vector<std::vector<int> > const& blocks);
```

Six steps. **Build them in this order, one per message, stopping for
interrogation between each:**

1. **Base case** — fewer than 2 blocks, return as-is.
2. **Straggler** — odd count, set the last block aside.
3. **Pair and merge** — walk in twos, one key comparison, push `loser + winner`.
4. **Recurse** — `sortBlocks(merged)`; blocks come back ordered by key.
5. **Split** — `half = size / 2`, front = losers, back = winners.
6. **Insert** — chain starts as `losers[0]` plus all winners. Binary-insert the
   rest in Jacobsthal order, each bounded by its own partner's position.

**Step 6 detail that is worth a comparison:** the straggler joins the pend as one
extra element with **no partner**, so its search range is the whole chain — and
it goes in *in Jacobsthal order*, not last. Inserting it last costs 20 at n=9.
Folding it in costs **19**. Same output, one comparison apart, and that is the
difference between "optimal" and "nearly optimal" when an evaluator counts.

Jacobsthal boundaries `1, 3, 5, 11, 21, 43, 85 …` from `J(n) = J(n-1) + 2*J(n-2)`.
Walk **downward** inside each group, clamp the last group to the pend size.
Generate them in a loop — do not hardcode a table.

```
k = 4   ->  3 2 4
k = 10  ->  3 2 5 4 10 9 8 7 6
```

### Remaining order of attack

- [ ] `sortBlocks` steps 1–6 in `PmergeMeVector.cpp`, one step per exchange
- [ ] Wire `sortVector` to wrap ints in 1-element blocks, call it, unwrap
- [ ] Delete the temporary `a= b=` debug loop
- [ ] Port to `sortDeque` — **written separately, not templated.** The subject
      wants the two implementations visible side by side so the timing means
      something
- [ ] Verify `After:` is sorted, and `./PmergeMe $(shuf -i 1-100000 -n 3000 | tr '\n' ' ')`
- [ ] valgrind + UBSan, then NEMESIS Mode 1 on ex02
- [ ] NEMESIS Mode 2 (interrogation) on ex00 and ex01 — still pending

---

## 5. Settled decisions — do not relitigate

- **`std::deque` is not end-only.** It has `operator[]`, random-access
  iterators, and `insert()` anywhere. Push/pop at both ends is its *cheap*
  operation, not its only one. Middle insertion is O(n), same as vector.
- **`std::stack` in ex01 is pinned to `std::list`** (`std::stack<int, std::list<int> >`)
  because it defaults to deque, and ex02 needs deque unburned.
- **The clock covers parse + sort, NOT printing.** Writing 3000 numbers to a
  terminal costs more than the sort and would drown the measurement.
- **`parseToken` accepts `0`** and rejects any sign, even `'+'`. The subject
  calls 0 part of "a positive integer" (ex00, p.179).
- **Function templates in headers are allowed** — subject p.70 exempts them.
- **Access control is about naming, not touching.** A member function may name
  `_vector` and pass it to a template. No getters needed, and a
  `std::vector<int> const getVector(void)` returning by value would be a silent
  no-op anyway.
- **Ford-Johnson is not the fastest sort, it is the thriftiest** — fewest
  comparisons, not fastest wall clock. Saying "it's the fastest" at evaluation
  is wrong and easy to catch.

## 6. Traps already paid for

- **Signed overflow is UB and cannot be inspected afterwards** — range-check
  *before* the operation. `INT_MIN / -1` traps in hardware.
- **Evaluation order of `<<` chain operands is unspecified in C++98.** A throw
  inside a `cout` chain prints half a line glued to the error with no newline.
  Compute into a variable first, then print. Verified on g++ and clang.
- **`std::isdigit` needs `static_cast<unsigned char>`** — plain char is signed.
- **`const` is part of a function's signature.** A definition missing it is a
  different, undeclared function.
- **inotify does not work on `/mnt/c` from WSL.** If VS Code will not refresh on
  the other machine and it is also WSL, set `remote.WSL.fileWatcher.polling`.
  Otherwise `git diff` is the reliable review channel.

---

## 7. Reference docs in this directory

- **`FORD_JOHNSON.md`** — the algorithm traced on nine numbers, why b₃ goes
  before b₂ counted both ways, the Jacobsthal derivation.
- **`README.md`** — module overview plus the **block representation** panel,
  which is the implementation design for ex02.
