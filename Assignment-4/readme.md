Parsing of the SQL query can be done using the bash script.
To use the bash script:
	Run `bash script.sh`
	Enter the input query.
	The result is displayed on stdout.

The syntax of queries is as follows:
	SELECT < condition > (Table-name)
	PROJECT < attribute-list > (Table-name) where attribute list are attributes seperated by commas
	(Table-name-1) CARTESIAN_PRODUCT (Table-name-2)
	(Table-name-1) EQUI_JOIN < join-condition > (Table-name-2)

Sample input queries are given in file testcases.

The SQL query can also be parsed by manually executing the following commands in order:
	bison -d parser.y
	lex analyzer.lex 
	gcc -o intermediate lex.yy.c parser.tab.c
	./intermediate followed by query input
If output.cpp is successfully generated, run
	g++ -o output output.cpp
	./output
	