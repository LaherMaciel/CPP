# Ford-Johnson (merge-insertion sort) — traced

The hard part of CPP09 ex02. Most explanations cover the pairing, which is the
easy half, and skip the part that actually *is* the algorithm: the order the
leftover elements go back in.

---

## It is not the fastest sort. It is the thriftiest.

Ford-Johnson minimises the **number of comparisons**, not the running time. It
moves more memory than quicksort and is more code than merge sort. What it buys
you is the fewest `a < b` questions known for small *n*.

That matters when a comparison is expensive — records on disk, or asking a
human. For sorting `int`s in RAM it is not the practical choice. It is on the
syllabus because getting it right proves you can hold a non-obvious recursive
structure in your head.

Say this out loud at evaluation. *"It's the fastest sort"* is wrong and easy to
catch.

---

## Not merge sort

Pairs, then cells of 2, then 4, then 8, biggest cell moves right — that is
**bottom-up merge sort**. Real algorithm, different one.

Ford-Johnson shares only the first move. It compares elements in pairs, then
does the thing merge sort never does: **it sets half the elements aside and
recurses on the winners only.** The losers come back at the end, one at a time,
in an order that looks arbitrary and is not.

---

## Notation

| | meaning |
|---|---|
| **a** | the **larger** of a pair — these form the main chain |
| **b** | the **smaller** of a pair — inserted at the end |
| aₖ / bₖ | partners: bₖ was paired with aₖ, so `bₖ < aₖ` is already known |

---

## Phase 1 — Pair and compare

Take elements two at a time. One comparison per pair. Larger becomes an **a**,
smaller becomes its **b**, and they stay linked. An odd count leaves one element
with no partner — the *straggler*.

Input `3 5 9 7 4 8 1 6 2`:

```
a:  5   9   8   6        straggler: 2
b:  3   7   4   1
```

Four comparisons so far.

## Phase 2 — Recurse on the winners only

Sort `5 9 8 6` — **the a's alone** — with this same algorithm. The b's do not
participate. This is the recursion, and it is the step most people's mental
model is missing.

**Each b travels with its a.** When the recursion moves `6` ahead of `8`, its
partner `1` moves with it. Lose that link and the algorithm collapses. This is
the single most common implementation bug, and the reason a plain `std::sort`
over an array of ints cannot be the inner sort.

```
5 9 8 6   ->   5 6 8 9

renumbered, partners intact:
a1=5  a2=6  a3=8  a4=9
b1=3  b2=1  b3=4  b4=7
```

## Phase 3 — Insert the b's

The sorted a's are the **main chain**. Each b is binary-inserted into it. Two
facts make this cheap:

- **b₁ is free.** It is smaller than a₁, and a₁ is the chain minimum, so b₁ goes
  straight to the front. Zero comparisons.
- **Every other bₖ only searches below aₖ.** You already know `bₖ < aₖ` from
  Phase 1, so the search space is the part of the chain *before* aₖ — never the
  whole thing.

And then the part that decides everything: **the order you insert them in.**

---

## The full trace

Insertion order is **b₁, b₃, b₂, b₄**, then the straggler.

| step | chain | what happened |
|---|---|---|
| main chain | `5 6 8 9` | sorted a's, out of the recursion |
| insert b₁ = 3 | `3 5 6 8 9` | free — 3 < 5 already known, 5 is the minimum |
| insert b₃ = 4 | `3 4 5 6 8 9` | searches only `3 5 6`, the part below a₃ = 8 → 2 comparisons |
| insert b₂ = 1 | `1 3 4 5 6 8 9` | searches only below a₂ = 6 → 2 comparisons |
| insert b₄ = 7 | `1 3 4 5 6 7 8 9` | searches below a₄ = 9 → 3 comparisons |
| insert straggler = 2 | `1 2 3 4 5 6 7 8 9` | no partner, no shortcut — search the whole chain |

Ford-Johnson needs **at most 19 comparisons** for nine elements. `ceil(log2(9!))`
is also 19 — the floor *any* comparison sort must pay. For n = 9 the algorithm
is provably optimal.

---

## Why b₃ before b₂

Two facts, and the whole thing falls out.

**Fact one: binary search cost is a step function.** Searching *k* elements
costs `ceil(log2(k+1))`:

| range size | 1 | 2 | **3** | 4 | 5 | 6 | **7** | 8 |
|---|---|---|---|---|---|---|---|---|
| comparisons | 1 | 2 | **2** | 3 | 3 | 3 | **3** | 4 |

Sizes **3** and **7** — the `2^k - 1` values — are the last size that still fits
in its price bracket. A range of 3 costs the same as 2. A range of 4 costs one
more.

**Fact two: every insertion makes the chain longer**, widening the search range
for every b after it.

So the rule is: **insert the b that is already sitting exactly on a boundary,
before another insertion pushes it over.** The b's with slack can wait.

### Count it both ways

Chain after b₁ goes in: `b1 a1 a2 a3 a4`. Each bₖ searches only below its own aₖ.

| order | insert | range below its a | size | cost |
|---|---|---|---|---|
| **Jacobsthal** | b₃ | `b1 a1 a2` | 3 | **2** |
| | b₂ | `b1 a1 b3?` | 3 | **2** |
| | | | | **4 total** |
| **Naive** | b₂ | `b1 a1` | 2 | **2** |
| | b₃ | `b1 b2 a1 a2` | 4 | **3** |
| | | | | **5 total** |

**b₃'s range is already 3** — exactly on the boundary. Insert it now, pay 2.
Wait, let b₂ go first, and the range becomes 4 and costs 3.

**b₂'s range is 2, which has slack** — costs 2 now, would still cost 2 at size 3.
So b₂ can safely wait while b₃ goes first.

One comparison saved on two elements. Multiply across 1500 insertions.

---

## The Jacobsthal numbers

Not primes. Named after Ernst Jacobsthal, and built exactly like Fibonacci:

```
Fibonacci    F(n) = F(n-1) +     F(n-2)     1, 1, 2, 3,  5,  8, 13 ...
Jacobsthal   J(n) = J(n-1) + 2 * J(n-2)     0, 1, 1, 3,  5, 11, 21, 43 ...
```

One coefficient apart. Both are **Lucas sequences** — second-order linear
recurrences. Jacobsthal has a closed form, which is where the powers of two come
from and why it lands on binary-search boundaries:

```
J(n) = (2^n - (-1)^n) / 3

n:     0  1  2  3   4   5   6   7    8    9    10    11    12
J(n):  0  1  1  3   5  11  21  43   85  171   341   683  1365
```

The numbers are **group boundaries**. Within each group you insert **downward**.

### Example — 20 numbers

20 elements gives 10 pairs: a₁…a₁₀ and b₁…b₁₀, no straggler.

| group | boundary | insertion order |
|---|---|---|
| 1st | J = 1 | `b1` |
| 2nd | J = 3 | `b3 b2` |
| 3rd | J = 5 | `b5 b4` |
| 4th | J = 11, capped at 10 | `b10 b9 b8 b7 b6` |

Full order: `b1 b3 b2 b5 b4 b10 b9 b8 b7 b6`

Note the last group: the boundary is 11 but only 10 b's exist, so you **start at
b₁₀** and walk down. Your loop must clamp the group's upper end to the number of
b's you actually have. Off-by-one here is the second most common bug, after
losing the a-b link.

For 3000 elements you have ~1500 b's, so the sequence must run past 1500 — up to
`2731`, around thirteen terms. Generate them in a loop until the value exceeds
your b count; do not hardcode a table.

**If you skip Jacobsthal ordering entirely, your program still sorts correctly.**
It just uses more comparisons — and that is exactly what an evaluator checks,
because it is the only thing distinguishing Ford-Johnson from "pair up and
binary insert".

---

## Implementation notes for ex02

**Keep pairs linked.** The recursion sorts a's while b's must follow. Sort a
container of pairs, or sort indices — never sort the a's in isolation and try to
reunite them afterwards.

**Write it twice.** The subject says to implement the algorithm separately for
each container rather than one generic version. That is advice, not a language
limitation — a template would compile fine. They want the two implementations
visible side by side so the timing comparison means something.

**`std::deque` is not restricted to its ends.** Push/pop at both ends is its
*cheap* operation (vector cannot do the front), but deque also has `operator[]`,
random-access iterators, and `insert()` anywhere. Middle insertion is O(n), same
as vector. Everything here works identically in both.

**You never swap manually.** Binary insertion is
`container.insert(iterator, value)` — the container does the shifting, and
`std::lower_bound` finds the iterator.

**Time everything.** "Both the sorting part and the data management part" — the
clock starts at parsing, not at the sort call. C++98 has no `<chrono>`; use
`gettimeofday` or `std::clock`.

**Mind the straggler.** An odd count leaves one element with no partner. No free
comparison, no bounded search — it goes into the finished chain at the very end.

---

## Order of attack

1. **Parse.** Positive integers only; `"-1"` is an error. Fill both containers,
   print `Before:`. Nothing algorithmic yet.
2. **Pair and recurse** on one container. Get the main chain sorted, ignore the
   b's entirely — verify the a's come out in order.
3. **Insert b's in plain order.** Now it sorts correctly. This is a working,
   submittable program.
4. **Add Jacobsthal ordering.** Output does not change; the comparison count
   drops. Count comparisons before and after to prove it worked.
5. **Port to the second container** and add timing.

Step 3 is a complete correct sort. Step 4 is what makes it Ford-Johnson.
Getting to step 3 first means you always have something that runs.

---

*Merge insertion — Ford & Johnson, 1959. Knuth, "The Art of Computer
Programming", Vol. 3, §5.3.1, p. 184, as the subject cites.*
