# Simd-Intrinsics
## Overview

This project demonstrates performance optimization techniques using **SIMD (Single Instruction, Multiple Data)** capabilities via **SSE/SSE4.2**. Implementations were done in both **C with intrinsics** and **x86-64 assembly**, exploring how to accelerate common computational tasks using data-level parallelism.

## Task Summaries

### 🧠 `decode` – Assembly Warm-Up

- Rewrote a low-level logic function in C to replicate an equivalent assembly implementation.
- Practiced reading and converting assembly into optimized, register-aware C code.

### 🧵 `strlen` – SIMD `strlen` with SSE4.2

- Implemented a custom `strlen` in x86-64 assembly using `pcmpistri`.
- Explored how SIMD compares strings in 16-byte blocks to detect the null terminator.
- Gained experience setting up the **IMM8 control byte** and **AT&T syntax**.

### 📏 `hamming` – Hamming Distance with Intrinsics

- Vectorized a string comparison using SSE4.2 intrinsics.
- Efficiently counted character mismatches using bitwise ops and mask extraction.
- Accounted for length mismatches in the final Hamming distance calculation.

### 📐 `formulas` – Mathematical Formula with Intrinsics

- Evaluated a nested floating-point expression involving square roots and products.
- Used intrinsics for fast vectorized arithmetic across float arrays.
- Carefully handled precision and performance trade-offs in numerical computation.

## What I Learned

- How to utilize **SSE4.2 intrinsics** and **inline assembly** for performance.
- Correct operand order and syntax for x86 SIMD instructions.
- Differences between scalar and vectorized operations in practice.
- Debugging and validating SIMD results using test drivers and helper utilities.
- Writing modular, testable C code backed by `Makefile` automation.

  ## Project Structure

```
.
├── decode
│   ├── Makefile
│   ├── decode.c
│   ├── decode.s
│   └── main.c
├── formulas
│   ├── Makefile
│   ├── formula1.c
│   ├── formulas.h
│   └── main.c
├── hamming
│   ├── Makefile
│   ├── hamming_intrinsics.c
│   ├── test_hamming
│   └── test_hamming.c
└── strlen
    ├── Makefile
    ├── strlen_sse42.h
    ├── strlen_sse42.s
    └── test_strlen.c
```

## How to Compile & Run

Each folder includes its own `Makefile`. Simply run:

```bash
cd <task_folder>
make
./<binary_name>
```

### Examples:

#### 🧠 Decode
```bash
cd decode
make
./decode
```

#### 🧵 Strlen
```bash
cd strlen
make
./test_strlen
```

#### 📏 Hamming
```bash
cd hamming
make
./test_hamming
```

#### 📐 Formulas
```bash
cd formulas
make
./formulas
```

## Notes
- SIMD was used in all tasks as required, either via intrinsics or pure assembly.
