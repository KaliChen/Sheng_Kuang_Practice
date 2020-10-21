#Makefile
.PHONY:clean
combinat_app:	main.o direct.o graycode.o intpart.o intpart_sharp.o ksubset.o lexical.o permu_lr.o permut_r.o setpart.o
	gcc -o combinat_app main.o direct.o graycode.o intpart.o intpart_sharp.o ksubset.o lexical.o permu_lr.o permut_r.o setpart.o
main.o:	main.c direct.h graycode.h intpart.h intpart_sharp.h ksubset.h lexical.h permu_lr.h permut_r.h setpart.h
	gcc -c main.c
direct.o:direct.c direct.h
	gcc -c direct.c
graycode.o:graycode.c graycode.h
	gcc -c graycode.c
intpart.o: intpart.c intpart.h
	gcc -c intpart.c
intpart_sharp.o: intpart_sharp.c intpart_sharp.h
	gcc -c intpart_sharp.c
ksubset.o: ksubset.c ksubset.h
	gcc -c ksubset.c
lexical.o: lexical.c lexical.h
	gcc -c lexical.c
permu_lr.o: permu_lr.c permu_lr.h
	gcc -c permu_lr.c
permut_r.o: permut_r.c permut_r.h
	gcc -c permut_r.c
setpart.o: setpart.c setpart.h
	gcc -c setpart.c
clean:
	$(RM) *.o combinat_app
