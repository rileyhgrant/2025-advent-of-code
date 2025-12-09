# 2025-advent-of-code
My solutions to [Advent of Code](https://adventofcode.com) (AoC) 2025 in C

## Requirements

- [make](https://www.gnu.org/software/make/)
- [clang](https://clang.llvm.org)
- [clang-format](https://clang.llvm.org/docs/ClangFormat.html)

## Input

My personal inputs are not included in this repo per [https://adventofcode.com/2025/about](https://adventofcode.com/2025/about).

Currently, the expected location of the inputs are: `./input/dayNN.txt` and `./input/dayNN_test.txt`
e.g. `./input/day02.txt` and `./input/day02_test.txt`

Place your input(s) in that directory, with the same naming convention to have this repo work as-is for your problem inputs.

## Usage

Run `make run` from the command line with an argument for the day you wish to solve, e.g.

```
$ make run day=5
```

```
====================
Advent of Code 2025!

=== Day 05 ===
 -- Part 1: 613
 -- Part 2: 336495597913098
```

Run with `day=all` to solve every day so far, e.g.

```
$ make run day=all
```

```
====================
Advent of Code 2025!

=== Day 01 ===
 -- Part 1: 1071
 -- Part 2: 6700

=== Day 02 ===
 -- Part 1: 19128774598
 -- Part 2: 21932258645

=== Day 03 ===
 -- Part 1: 17359
 -- Part 2: 172787336861064

=== Day 04 ===
 -- Part 1: 1502
 -- Part 2: 9083

=== Day 05 ===
 -- Part 1: 613
 -- Part 2: 336495597913098
```
