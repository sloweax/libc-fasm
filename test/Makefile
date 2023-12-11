include ../config.mk

CFLAGS+=-fno-builtin -ffreestanding

all: test

%.o: %.c
	$(CC) $(CFLAGS) $^ -c -o $@

../$(LIBC).a:
	cd .. && $(MAKE) PREFIX=fasm_ $(LIBC).a

test-bin: test.o unit.o ../$(LIBC).a
	$(CC) $(CFLAGS) $^ -o $@

test: test-bin
	TEST_ENV=123 TEST_EMPTY= TEST_EQ== ./$^

clean:
	rm -f *.o test-bin

.PHONY: clean all test
