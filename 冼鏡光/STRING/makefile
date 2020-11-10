#Makefile
.PHONY:clean
string_app:	main.o bm.o distseq.o h_seq.o kmp.o lcs.o max_reps.o parcount.o polish.o
	gcc -o string_app main.o bm.o distseq.o h_seq.o kmp.o lcs.o max_reps.o parcount.o polish.o
main.o:	main.c bm.h distseq.h h_seq.h kmp.h lcs.h max_reps.h parcount.h polish.h
	gcc -c main.c
bm.o: bm.c bm.h
	gcc -c bm.c
distseq.o: distseq.c distseq.h
	gcc -c distseq.c
h_seq.o: h_seq.c h_seq.h
	gcc -c h_seq.c
kmp.o: kmp.c kmp.h
	gcc -c kmp.c
lcs.o: lcs.c lcs.h
	gcc -c lcs.c
max_reps.o: max_reps.c max_reps.h
	gcc -c max_reps.c
parcount.o: parcount.c parcount.h
	gcc -c parcount.c
polish.o: polish.c polish.h
	gcc -c polish.c
clean:
	$(RM) *.o string_app
