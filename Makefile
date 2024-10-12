.SUFFIXES: .o .c

EX = examples
OBJS = sort.o
EXAMPLES = $(EX)/repeat.c

CFLAGS = -std=c11 -Wall -Wextra -Werror -ggdb
CFLAGS += -fsanitize=address,undefined

LINKLIBS = -levth -lasan -lubsan

evth: $(OBJS)
	$(AR) rcs libevth.a $(OBJS) 

example: evth
	$(CC) $(CFLAGS) $(EXAMPLES) -L. $(LINKLIBS) -o $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o libevth.a example
