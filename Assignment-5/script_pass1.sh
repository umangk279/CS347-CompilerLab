FILE="$1"
bison --warning=none -d -v parser.y
lex analyzer.lex
g++ lex.yy.c parser.tab.c struct.cpp

VAR2=$(./a.out < $FILE)
if [[ $VAR2 == *"Segmentation"* ]]; then
	echo "Semantic error. Aborting"
else
	echo -e "$VAR2"
fi
