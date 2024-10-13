B = build
E = examples

OBJS = $(B)/sort.o $(B)/volume.o $(B)/vec.o $(B)/binheap.o $(B)/utils.o

CFLAGS = -std=c11 -Wall -Wextra -Werror -ggdb
CFLAGS += -fsanitize=address,undefined

LINKLIBS = -levth -lasan -lubsan

evth: $(OBJS)
	$(AR) rcs $(B)/libevth.a $(OBJS)

$(B)/%.o: %.c
	mkdir -p $(B)
	$(CC) $(CFLAGS) -c $< -o $@

sort: evth examples_dir
	$(CC) $(CFLAGS) $(E)/sort.c -L$(B) $(LINKLIBS) -o $(B)/$(E)/$@

binheap: evth examples_dir
	$(CC) $(CFLAGS) $(E)/binheap.c -L$(B) $(LINKLIBS) -o $(B)/$(E)/$@

examples_dir:
	mkdir -p $(B)/$(E)

clean:
	rm -rf build
