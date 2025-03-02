# Hack Assembler

An assembler for an HDL-like symbolic code called the Hack machine language described in the [Elements of Computing Systems (Nand2Tetris)](https://mitpress.mit.edu/books/elements-computing-systems-second-edition). The assembler converts symbolic programs into their binary representations in ASCII for the Hack computer, written in C.

## How does it work?

The Hack Assembler uses input and output redirection, forcing the standard input stream to read from `.asm` source files and the standard output to write to `.out` files.

The assembly process consists of five main components:

- **Tokenizer Module**: Breaks input into meaningful symbols.
- **Parser Module**: Analyzes the syntax of the instructions.
- **Symbol Table Module**: Manages labels and variable symbols.
- **Scanner Module**: Reads and resolves labels and variable symbols.
- **Code Module**: Translates instructions into binary.

## A-Instruction and C-Instruction

### A-Instruction (`@value`)

The A-instruction sets the **A register** to a given value.

- **Symbolic syntax**: `@value` (where `value` is a non-negative constant or symbol).
- **Binary syntax**: `0vvvvvvvvvvvvvvv` (15-bit binary representation of `value`).
- **Example**:
  - `@21` → `0000000000010101`

### C-Instruction (`dest = comp ; jump`)

The C-instruction performs computation and optionally stores the result or jumps.

- **Symbolic syntax**: `dest = comp ; jump`
- **Binary syntax**: `111 a c1 c2 c3 c4 c5 c6 d1 d2 d3 j1 j2 j3`
- Components:
  - `comp` (computation)
  - `dest` (destination of result)
  - `jump` (optional control flow change)
- **Example**:
  - `D=M+1` → `1110011111010000`

## Installation & Usage

### 1. Build the Assembler

Ensure you have `gcc` installed. Then, compile the assembler using:

```sh
make
```

This generates an executable called `assembler`.

### 2. Run the Assembler

To assemble a Hack assembly file (`.asm`), use:

```sh
./assembler < input.asm > output.out
```

This converts `input.asm` into a binary machine code file `output.out`.

### 3. Clean Up

To remove the compiled assembler:

```sh
make clean
```

## Resources

- Book: [Elements of Computing Systems](https://mitpress.mit.edu/books/elements-computing-systems-second-edition)
- Website: [Nand2Tetris](https://www.nand2tetris.org/)
- Digital HDL Tools:
  - [Digital](https://github.com/hneemann/Digital)
  - [Digital Logic Sim](https://github.com/SebLague/Digital-Logic-Sim)
- [Nand2Tetris VS Code Plugin](https://marketplace.visualstudio.com/items?itemName=Throvn.nand2tetris)

###

This project is licensed under the MIT License – see the [LICENSE](https://github.com/PeterKwesiAnsah/hack-assembler/blob/main/LICENSE) file for details.
