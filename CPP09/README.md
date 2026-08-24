# CPP Module 09 - STL

> **Continuing on another machine?** Read **[HANDOFF.md](HANDOFF.md)** first —
> current state, the next step, and the one-function-at-a-time working method.

## Overview

Module 09 applies everything learned about the STL to solve concrete algorithmic problems. Each exercise mandates a different container type.

## Learning objectives

- Choosing the right STL container for the task
- `std::stack` for expression evaluation
- `std::map` for key-value lookups
- `std::deque`/`std::list` for the Ford-Johnson merge-insert sort

## Exercises

| Exercise | Name | Key concepts |
|----------|------|-------------|
| ex00 | Bitcoin Exchange | `std::map` — parse a CSV database, look up closest past date |
| ex01 | Reverse Polish Notation | `std::stack` — evaluate an RPN expression |
| ex02 | PmergeMe | Ford-Johnson merge-insert sort with two different containers, compare performance |

## Compilation

```bash
cd ex00  # or ex01, ex02
make
```

Compiles with `-Wall -Wextra -Werror -std=c++98`.

## Understanding Ford-Johnson (ex02)

The merge-insert sort is the hardest part of this module, and the part most
explanations skip is the *insertion order* of the smaller elements — not the
pairing, which is the easy half.

**[FORD_JOHNSON.md](FORD_JOHNSON.md)** — the algorithm worked through step by
step on nine numbers, with the Jacobsthal insertion order explained by counting
comparisons both ways.

Three things it clears up:

- The recursion runs on the **larger** element of each pair only. The smaller
  ones are set aside and inserted at the end — this is what makes it *not*
  merge sort.
- Each smaller element must stay **linked to its partner** through the
  recursion. Losing that link is the most common implementation bug.
- The b's go back in **Jacobsthal order** (1, 3, 2, 5, 4, 11, 10, 9, 8, 7, 6 …),
  which makes every binary search land on a `2^k - 1` range. Inserting them in
  plain order still sorts correctly — it just costs more comparisons, and that
  is the only thing distinguishing Ford-Johnson from "pair up and binary insert".

---

## The block representation — how we actually implement it

> This panel answers the question *"how do we convert from the pairs to the
> blocks?"* The short version: **we don't convert. Concatenating is the pairing.**

### Why `std::pair` has to go

`std::pair<int, int>` holds exactly two ints, forever. That is fine for level 0.
It is useless at level 1, because the recursion does not pair *numbers* — it
pairs *the things it just built*. Level 1 pairs groups of 2, level 2 pairs groups
of 4, level 3 pairs groups of 8.

A pair cannot grow. `pair<pair<int,int>, pair<int,int> >` is a different C++ type
at every level, so the recursion could not call itself. That is the wall.

**The replacement is one type that works at every level:**

```
std::vector<std::vector<int> >
```

The inner `vector<int>` is a **block**. The outer vector is the list of blocks
currently being sorted. The recursive function takes that type and returns that
type — same type in, same type out, so it can call itself.

### The one invariant

> **A block's key is its LAST element, and that element is the block's maximum.**

Everything below depends only on this. `block.back()` is the only thing ever
compared.

### Pairing = concatenation

Two blocks. One comparison on their keys. Then build **one** block: the loser's
elements first, the winner's elements after.

```
loser  [3, 5]        key 5
winner [7, 9]        key 9
                          one comparison: 5 < 9
merged [3, 5, 7, 9]  key 9   <- still the max, invariant holds
```

That is the whole conversion. The loser is not stored *next to* the winner, it
is stored **inside** the winner's block, in the front half. So the a–b link that
`FORD_JOHNSON.md` calls the most common bug to lose is not tracked by any
pointer, index, or parallel array — **it is physical position.** The recursion
moves the merged block around; the loser rides along because it is part of it.

### Splitting back

When the recursion returns, every block has the same size. Cut it in half:

```
merged  [3, 5, 7, 9]
half = size / 2 = 2

losers  = merged[0 .. half)    -> [3, 5]     the b's
winners = merged[half .. size) -> [7, 9]     the a's, the main chain
```

`losers[j]` is the partner of `winners[j]`, by construction, for free.

### Full trace — 8 numbers

Input `3 5 9 7 4 8 1 6`.

**Going down (pair and merge):**

| level | blocks (key in bold) | |
|---|---|---|
| 0 | `[3] [5] [9] [7] [4] [8] [1] [6]` | 8 blocks of size 1 |
| 1 | `[3,5] [7,9] [4,8] [1,6]` | 4 blocks of size 2, keys 5 9 8 6 |
| 2 | `[3,5,7,9] [1,6,4,8]` | 2 blocks of size 4, keys 9 8 |
| 3 | `[1,6,4,8,3,5,7,9]` | 1 block — recursion bottoms out |

**Coming back up (split and insert):**

| level | winners (chain) | losers (pend) | result |
|---|---|---|---|
| 2 | `[3,5,7,9]` | `[1,6,4,8]` | b1 free → `[1,6,4,8] [3,5,7,9]` keys 8 9 |
| 1 | `[4,8] [7,9]` | `[1,6] [3,5]` | insert b2=`[3,5]` below a2 → keys 5 6 8 9 |
| 0 | `[5] [6] [8] [9]` | `[3] [1] [4] [7]` | order b3 b2 b4 → `1 3 4 5 6 7 8 9` |

Watch the last row. The chain is `3 5 6 8 9`. Insert b3 = `4`: its partner a3 is
`8`, sitting at index 3, so the binary search only looks at `3 5 6` — never the
whole chain. That bounded search is where the comparisons are saved.

### Answering your two questions directly

**"Will we have a vector with two index?"** — No. One `vector<int>` per block,
of size 1, 2, 4, 8 … The two-element case is just level 1; nothing special
about it.

**"A second vector of vectors that adds index as we go?"** — Yes, exactly that.
The main chain is a second `vector<vector<int> >`, built by starting from the
winners and calling `.insert()` on it once per loser. It grows by one block per
insertion. That is the container the binary search runs on.

### The function we are going to write

One function, called once per container. Signature and skeleton only — we build
the body one step at a time:

```cpp
std::vector<std::vector<int> >
    sortBlocks(std::vector<std::vector<int> > const& blocks);
```

Six steps inside it:

1. **Base case** — fewer than 2 blocks, return as-is.
2. **Straggler** — odd count, set the last block aside.
3. **Pair and merge** — walk in twos, one key comparison, push `loser + winner`.
4. **Recurse** — `sortBlocks(merged)`. Blocks come back ordered by key.
5. **Split** — `half = size / 2`, front half = losers, back half = winners.
6. **Insert** — chain starts as `losers[0]` + all winners. Then binary-insert
   the rest in Jacobsthal order, each bounded by its own partner's position.
   The straggler joins the pend as one extra element with **no partner**, so its
   search range is the whole chain.

Top level: wrap every input number in a 1-element block, call `sortBlocks`, then
read `block[0]` back out of each.

### Jacobsthal order, generated not hardcoded

Boundaries are `1, 3, 5, 11, 21, 43, 85 …` from `J(n) = J(n-1) + 2*J(n-2)`.
Walk **downward** inside each group, and clamp the top of the last group to the
number of pend elements you actually have:

```
k = 4   ->  3 2 4
k = 10  ->  3 2 5 4 10 9 8 7 6
```

### Measured, not assumed

This design was prototyped and checked before being written down here:

| check | result |
|---|---|
| 5000 random inputs, n = 0…40, duplicates included | 0 mismatches |
| worst case at n = 9 | **19** comparisons — equals F(9), provably optimal |
| n = 5 / 10 / 11 / 21 | 7 / 22 / 26 / 66 — each equals `ceil(log2(n!))` |
| n = 3000 | ~30 380 comparisons against a floor of 30 332 |

Step 6's straggler handling is the detail that matters: inserting it **last**
costs 20 comparisons at n = 9. Folding it into the Jacobsthal order as an extra
pend element costs 19. Same output, one comparison apart.
