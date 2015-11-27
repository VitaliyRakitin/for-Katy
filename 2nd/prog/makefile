CC=gcc
CFLAGS=-c -Wall -O3 -Werror -g
LDFLAGS=
SOURCES=main.c vect.c RK_koeff.c change_me.c RK.c RK_out.c RK_step.c new_step.c delta.c newton.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=p

all: $(SOURCES) $(EXECUTABLE)
	rm -rf *.o 	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	

.c.o:
	$(CC) $(CFLAGS) $< -o $@ 

clean:
	rm -rf *.o 