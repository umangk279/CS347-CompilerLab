FILE=./output.cpp
FILE2=./output
bison -d parser.y
lex analyzer.lex 
gcc -w -o intermediate lex.yy.c parser.tab.c

VAR=$(./intermediate)
echo -e "$VAR"

if test -f "$FILE"; then
	g++ -o output output.cpp
fi
if test -f "$FILE2"; then
	./output
elif [[ $VAR == *"File"*"exist"* ]]; then
	echo "Enter correct database."
elif [[ $VAR == *"INVALID SYNTAX"* ]]; then
	printf ""
else
	echo "Type mismatch in attributes in the input query."
fi
