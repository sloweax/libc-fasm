include config.mk

all: $(LIBC).a

OBJ+=$(patsubst %.asm,%.o,$(wildcard src/unistd/*.asm))
OBJ+=$(patsubst %.asm,%.o,$(wildcard src/string/*.asm))
OBJ+=$(patsubst %.asm,%.o,$(wildcard src/stdlib/*.asm))
OBJ+=$(patsubst %.asm,%.o,$(wildcard src/env/*.asm))
OBJ+=$(patsubst %.asm,%.o,$(wildcard src/fcntl/*.asm))
OBJ+=$(patsubst %.asm,%.o,$(wildcard src/crt/*.asm))

%.o: %.asm
	$(FASM) $(FASMFLAGS) $^ $@

$(LIBC).a: $(OBJ)
	ar rcs $@ $^

clean:
	rm -f $(LIBC).a $(OBJ)
	cd test && $(MAKE) $@

test:
	cd test && $(MAKE)

.PHONY: clean all test
