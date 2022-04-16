CC = gcc
CFLAGS = -Wall --std=c99
OBJECTS = main.o my_string.o unit_test.o test_def.o avl.o super_vector.o

string_driver: $(OBJECTS)
	$(CC) $(CFLAGS) -o string_driver $(OBJECTS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o 

my_string.o: my_string.c
	$(CC) $(CFLAGS) -c my_string.c -o my_string.o

super_vector.o: super_vector.c
	$(CC) $(CFLAGS) -c super_vector.c -o super_vector.o

avl.o: avl.c
	$(CC) $(CFLAGS) -c avl.c -o avl.o

clean:
	rm -f $(OBJECTS) string_driver unit_test 

unit_test: my_string.o unit_test.o test_def.o
	$(CC) $(CFLAGS) -o unit_test unit_test.o test_def.o my_string.o