a4: 	main.o mh.o
	gcc -o a4 main.o mh.o

main.o:	main.c mhDefs.h stuDefs.h
	gcc -c main.c

mh.o:	mh.c mhDefs.h stuDefs.h
	gcc -c mh.c

clean:
	rm *.o a4
