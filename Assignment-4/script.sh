FILE=./output.cpp
bison -d parser.y
lex analyzer.lex 
gcc -w -o intermediate lex.yy.c parser.tab.c
./intermediate

if test -f "$FILE"; then
	g++ -o output output.cpp
	./output
fi
