.PHONY : clean


ifdef OS
   RM = del /Q
else
   ifeq ($(shell uname), Linux)
      RM = rm -f
   endif
endif



all : main

main : main.o
		gcc main.o

main.o : main.c
		gcc -c main.c

clean:
		$(RM) *.exe
		$(RM) *.out
		$(RM) *.o

