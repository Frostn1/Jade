<img align="left" width="190" src="/images/Jade-Logo-2.jpg"/>


<h1>Jade</h1>

### A basic assembly like instruction set built entirley in native C<br><br>![Language](https://img.shields.io/badge/language-C-6A7FC8.svg?style=for-the-badge)

--- 

* [The Language](#the-language)<br>
* [Documentation](#docs)<br>
---

## <b>The Language</b>

The Official Jade Instruction Set by Frostn.
This is a basic assembly like instruction set built entirley in native C.  
Runs off the shell without outputing an .exe file.

## <b>Docs</b>

While the content of a code file can be what ever your heart desires, every program got to end with the op `stp`,  
as it tells the compiler to stop processing ops and that the code generation has ended.

### Basic Registers
The lang has currently 3 basic registers for memory use:
- dx
- ex
- fx

### Stack Ops
In the current Jade has 3 main stack ops,  
more may come in the future if the lang will need it.

#### Push
Pushes constant integer value or value stored in a register into the memory stack.  
Also moves the sp index.

The following program will push the constant value `15` in the stack and move th sp index.
```asm
push 15
```

#### Pop
Pops a value from the stack at the current sp index, into the register submitted.  

The following program will pop the most recent stack value into the `ex` register.
```asm
pop ex
```

#### Drop
Drops the sp index by a constant value and pops from the stack, at the calculated place.

The following program will pop the constant value `5` into `ex` and not `2` even tho is came last.
```asm
push 5
push 2
drop ex 2
```


