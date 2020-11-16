#Makefile
.PHONY:clean
sorting_app: 	main.o binsert.o contain.o heapmerg.o
	gcc -o sorting_app main.o binsert.o contain.o heapmerg.o
main.o:	main.c binsert.h contain.h heapmerg.h
	gcc -c main.c
binsert.o: binsert.c binsert.h
	gcc -c binsert.c
contain.o: contain.c contain.h
	gcc -c contain.c
heapmerg.o: heapmerg.c heapmerg.h
	gcc -c heapmerg.c
clean:
	$(RM) *.o sorting_app
