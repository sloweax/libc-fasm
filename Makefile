include config.mk

all: $(LIBC).a

OBJ=$(patsubst %.asm,%.o,$(wildcard src/*/*.asm))
OBJ+=$(patsubst %.asm,%.o,$(wildcard src/sys/*/*.asm))

%.o: %.asm
	$(FASM) $(FASMFLAGS) $^ $@

$(LIBC).a: $(OBJ)
	ar rcs $@ $^
	@[ $(PREFIX) ] && objcopy $@ --prefix-symbols=$(PREFIX) || true

clean:
	rm -f $(LIBC).a $(OBJ)
	cd test && $(MAKE) $@

test:
	cd test && $(MAKE)

.PHONY: clean all test
