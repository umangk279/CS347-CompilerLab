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
