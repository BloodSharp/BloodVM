# BloodSharp's Virtual Machine
BloodSharp's Virtual Machine or BloodVM is a project which emulate a new imaginary virtual CPU which can be found at many software protectors. I originally [developed this for fun in 2021](https://foro.elhacker.net/programacion_cc/ejemplo_de_virtualizacion_de_codigo_con_cpu_imaginaria-t512606.0.html) but I recently decided to release as free and open source software.

## Features
+ Run the code inside a new CPU.
+ Limited, yet functional Custom ISA.

## TODO
+ Add more instructions
+ Generate an instruction encoder, decoder and functions markers to protect custom functions sections in custom software.
+ Add support for 64 bits and other architectures.

# Demo
First make sure to disable ASLR (Properties -> Linker -> Advanced -> Dynamic base -> NO)
![ASLR Image](Images/ASLR.png)

## Test
The original output:

![Original Output](Images/OriginalOutput.png)

The original reverse engineered code:

![Original Ghidra code](Images/Original.png)

## Test Encrypted
The encrypted output:

![Encrypted Output](Images/EncryptedOutput.png)

The encrypted reverse engineered code:

![Encrypted Ghidra code](Images/Encrypted.png)


B#