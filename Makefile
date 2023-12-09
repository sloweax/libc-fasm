include config.mk

all: $(LIBC).a

OBJ=$(patsubst %.asm,%.o,$(wildcard src/*/*.asm))

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
