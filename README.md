# Syntax

## Registers

A - Multipurpose register
B - Multipurpose register
C - Multipurpose register
D - Multipurpose register
E - Multipurpose register
F - Multipurpose register
IP - Instruction pointer
SP - Stack pointer

## Flags

ZF - (Zero flag)

## Instructions

### PSH {value}
Push the following value to the stack

### POP
Pop from the stack

### INC {Register}
Increment the value in the specified register

### DEC {Register}
Decrement the value in the specified register

### SET {Register} {value}

### PSR {Register}
Push the value of a register onto the stack

### ADD
Pop the two top values from the stack, add them and push the result to the stack

### MIN
Pop the two top values from the stack, subtract them and push the result to the stack

### MUL
Pop the two top values from the stack, multiply them and push the result to the stack

### DIV
Pop the two top values from the stack, divide them and push the result to the stack

### MOD
Pop the two top values from the stack, modulus them and push the result to the stack

### JMP {value}
Jumps to the following address

### JZ {value}
Jumps to the following address if the ZF is set

### JNZ {value}
Jumps to the following address if the ZF is not set

### HLT
Halts the program
