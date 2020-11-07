#Makefile
.PHONY:clean
string_app:	main.o bm.o distseq.o
	gcc -o string_app main.o bm.o distseq.o
main.o:	main.c bm.h distseq.h
	gcc -c main.c
bm.o: bm.c bm.h
	gcc -c bm.c
distseq.o: distseq.c distseq.h
	gcc -c distseq.c

clean:
	$(RM) *.o string_app
