Implemented the various phases of a Compiler, for a subset of the C language consisting of the following operations:
1. Variable declarations, for int and float data types.
2. Arithmetic, logical and relational expressions.
3. Function calls and function definitions.
4. Conditional expressions: if-else and switch-case statements.
5. Loops: for and while.

The above task is performed in 2 passes: The first pass performs Lexical analysis, Parsing, Semantic analysis and Intermediate code generation operations, taking as input a C program (as .c format file) and producing as output the 3 address code in the Quadruple format. The second pass takes as input the generated quadruple format Intermediate code and produces as output the target MIPS code.

To run the compiler
Step1:
run bash script script_pass1.sh as follows:
./script_pass1.sh <path-to-file>
Step2:
run bash script script_pass2.sh as follows:
./script_pass2.sh

In first pass, IntermediateCode.txt is generated
In second pass, IntermediateCode.txt is processed to generate output.mips and data.mips

Source of error:
Passing array as a parameter to a function has not been handled. Error is displayed.
