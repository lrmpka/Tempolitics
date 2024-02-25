all: temp_stat

temp_stat: main.o temp_functions.o
		echo "Linking program temp_stat"
		gcc -o temp_stat main.o temp_functions.o

main.o: main.c temp_functions.h
		echo "Compile main.c"
		gcc -c -o main.o main.c

temp_functions.o: temp_functions.c temp_functions.h
		echo "Compile temp_functions.c"
		gcc -c -o temp_functions.o temp_functions.c

clean:
		rm -rf *.o temp_stat
