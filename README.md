# Mealy ⇄ Moore Finite State Machine Converter

A console program written in **C** that converts a **Mealy machine** into an equivalent **Moore machine**, and a **Moore machine** into an equivalent **Mealy machine**. Built as a Theory of Automata project.

---

## Table of Contents

- [Background](#background)
- [Features](#features)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Input Format](#input-format)
- [Examples](#examples)
- [How It Works](#how-it-works)
- [Limitations](#limitations)
- [Project Files](#project-files)
- [Authors](#authors)

---

## Background

Mealy and Moore machines are two kinds of finite state machines used in digital system design.

| | Mealy Machine | Moore Machine |
|---|---|---|
| **Output depends on** | Current state **and** current input | Current state **only** |
| **Output attached to** | Transitions | States |
| **Typical size** | Fewer states | Often more states |

Designers often need to move between the two representations. This tool automates the conversion for machines with a binary input alphabet (`0` and `1`) and binary outputs (`0` and `1`).

---

## Features

- **Mealy → Moore** conversion, including automatic creation of new states when a state is reached with more than one different output
- **Moore → Mealy** conversion
- Menu-driven interface that lets you run as many conversions as you like in one session
- Prints the intermediate **new Mealy table** during Mealy → Moore, so you can follow the steps

---

## Getting Started

### Prerequisites
- A C compiler (e.g. `gcc`, MinGW, or any IDE such as Dev-C++ / Code::Blocks)

### Build and run

```bash
git clone https://github.com/Talha-Munir-Saeed3/Mealy-Moore-Finite-State-Machine-Converter.git
cd Mealy-Moore-Finite-State-Machine-Converter
gcc -o converter Project.cpp
./converter        # Windows: converter.exe
```

> If your compiler complains about the `.cpp` extension for C code, use `gcc -x c Project.cpp -o converter`.

---

## Usage

```
MENU
****
1-MEALY TO MOORE CONVERSION
2-MOORE TO MEALY CONVERSION
EXIT

Choice :
```

Enter `1` or `2` to run a conversion. Entering any other number exits the program. After each conversion you return to the menu.

---

## Input Format

States and outputs are entered as **integers**, so letters must be mapped to numbers first (for example `a = 0`, `b = 1`).

### Mealy → Moore
States are numbered **starting from 1** (state `0` is not allowed). Each row has five numbers:

```
State  NextState(input 0)  Output(input 0)  NextState(input 1)  Output(input 1)
```

### Moore → Mealy
States may be numbered **starting from 0**. Each row has four numbers:

```
State  NextState(input 0)  NextState(input 1)  Output
```

---

## Examples

### Moore → Mealy

Moore machine with states `A=0, B=1, C=2` and outputs `a=0, b=1`:

| State | 0 | 1 | Output |
|:-:|:-:|:-:|:-:|
| A (0) | B | A | b |
| B (1) | B | C | b |
| C (2) | B | A | a |

Session:

```
Choice : 2
Enter The Number Of States : 3
0 1 0 1
1 1 2 1
2 1 0 0
```

Result:

```
MEALY MACHINE
State | Input 0 | Output 0 | Input 1 | Output 1
  0        1          1          0         1
  1        1          1          2         0
  2        1          1          0         1
```

Each transition's output is simply the output of the state it leads to.

### Mealy → Moore

Mealy machine with states `A=1, B=2, C=3` and outputs `a=0, b=1`:

| State | 0 / out | 1 / out |
|:-:|:-:|:-:|
| A (1) | B / a | C / a |
| B (2) | B / b | C / a |
| C (3) | B / a | C / b |

Session:

```
Choice : 1
Enter The Number Of States : 3
1 2 0 3 0
2 2 1 3 0
3 2 0 3 1
```

States `B` and `C` are each reached with two different outputs, so each is split into two new states (`2 → 20, 21` and `3 → 30, 31`). The program reports 5 total states (2 new) and builds this intermediate Mealy table:

```
State | Input 0 | Output 0 | Input 1 | Output 1
  1       20         0         30         0
  20      21         1         30         0
  21      21         1         30         0
  30      20         0         31         1
  31      20         0         31         1
```

The Moore table is then derived from it: each new state takes the output it was created for (`20 → 0`, `21 → 1`, `30 → 0`, `31 → 1`).

---

## How It Works

### Mealy → Moore
1. **Input** the Mealy table (integer-coded).
2. **Output encoding:** for every state, check whether it is entered with output `0`, output `1`, or both. A state entered with both outputs needs to be split in two.
3. **Count states:** total states = old states + new states.
4. **Assign new state numbers** using `10 × old_state + output`, e.g. state `2` becomes `20` and `21`.
5. **Rebuild the Mealy table** with the split states and redirect transitions to the correct new state.
6. **Build the Moore table** by attaching each state's output to the state itself.

### Moore → Mealy
1. **Input** the Moore table.
2. For each state and each input (`0`/`1`), follow the transition to its destination state.
3. Use the **destination state's output** as the output on that transition.
4. Print the resulting Mealy table.

---

## Limitations

- Binary input alphabet (`0`, `1`) and binary outputs only
- States and outputs must be entered as integers
- Mealy → Moore expects state numbers `1..N` (no zero)
- No input validation yet

---

## Project Files

| File | Description |
|---|---|
| `Project.cpp` | Source code (`Mealy_Moore()`, `Moore_Mealy()`, and a menu in `main()`) |
| `TOA_PROJECT.pptx` | Project presentation |
| `Project.pdf` | Hand-worked examples of both conversions |

---

## Authors

*Talha Munir Saeed*

---

## License

This project is licensed under the [MIT License](LICENSE).
