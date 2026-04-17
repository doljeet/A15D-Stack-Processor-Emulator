# STOS-A15D Emulator

A lightweight C++17 emulator for a fictional stack-based esoteric programming language / processor architecture. Originally created as an academic project.

The core gimmick of this processor is that it operates entirely on a **stack of doubly-linked character lists**. It performs arbitrary-precision arithmetic (big integers) manually digit-by-digit, without relying on standard C++ math libraries.
---

## Building

```bash
make        # produces ./stos
make clean
```

Requires a C++17-compatible compiler (g++ or clang++).

---

## Usage

```
./stos < program.txt
```

`program.txt` format:
```
<program instructions on line 1>
<input characters on line 2>
```

---

## Instruction Set

| Instruction | Name          | Description |
|-------------|---------------|-------------|
| `'`         | push          | Push an empty list onto the stack |
| `,`         | pop           | Discard the top list |
| `:`         | duplicate     | Push a copy of the top list |
| `;`         | swap          | Swap the top two lists |
| `@`         | at            | Pop index A; push a copy of the list at position A (0 = top) |
| `.`         | read char     | Read one character from stdin; prepend to top list |
| `>`         | print char    | Print the first character of the top list; pop the list |
| `!`         | logical NOT   | Replace top with `1` if it is empty or `0`, otherwise replace with `0` |
| `<`         | less than     | Pop A, pop B; push `1` if B < A, else `0` |
| `=`         | equal         | Pop A, pop B; push `1` if B = A, else `0` |
| `~`         | tilde         | Push the index of this instruction |
| `?`         | jump          | Pop T (target), pop W (condition); if W is non-empty and non-zero, jump to instruction T |
| `-`         | negate        | Toggle trailing `-` on the top list (changes sign of a number) |
| `^`         | abs           | Remove trailing `-` from the top list if present |
| `$`         | split         | Detach the first character of the top list and push it as a new list |
| `#`         | append        | Pop list A; append A to the end of the new top list |
| `+`         | add           | Pop A, pop B; push A + B (big-integer addition) |
| `[`         | char to int   | Pop list A; push the ASCII code of its first character |
| `]`         | int to char   | Pop number A; push the character with ASCII code A |
| `&`         | debug print   | Print the entire stack contents to stdout |
| other       | literal       | Prepend the character to the top list |

### Number format

A list represents a number when it contains only digits and at most one trailing `-`.
The least-significant digit is stored first:

```
List: 4 3 2 1 -
Number: -1234
```

### Instruction `?` (conditional jump)

```
'<target>'<condition>?
```

- Pops `T` (jump target instruction index)
- Pops `W` (condition list)
- If `W` is non-empty and is not the single character `0`, sets the instruction pointer to `T`
- Otherwise continues to the next instruction

---

## Example Programs

### Hello (print a pushed string)

```
'!dlrow ,olleh>>>>>>>>>>>>>
```

Pushes characters in reverse (least-significant first), then prints them one by one.

### Count from 5 down to 1

```
'5~,'>~,?
```

- `'5` — push `5`
- `~,` — push & immediately discard the instruction pointer (used for loop address)
- `'>` — print top character (prints `5`, then `4` ... `1`)
- `~,?` — push current address, conditional jump back

### Addition

```
'12'34+>
```

Pushes 12 and 34, adds them, prints `46`.

---

## Project structure

```
.
├── README.md
├── Makefile
└── src/
    ├── main.cpp
    ├── DigitNode.h
    ├── DigitNode.cpp
    ├── DigitList.h
    ├── DigitList.cpp
    ├── Stack.h
    └── Stack.cpp
```

---

## Implementation notes

- **Big integers** — numbers of arbitrary size are supported; arithmetic operates digit-by-digit on the linked lists
- **Signed numbers** — sign is stored as a trailing `-` node; `^` (abs) and `-` (negate) manipulate this node
- **No stdlib arithmetic** — all addition and subtraction is implemented manually using carry/borrow propagation
- **Memory** — nodes are freed explicitly; `DigitList::clear()` traverses and deletes the chain

---

## License

Academic project. See course materials for context.
