
# vim: ft=make noexpandtab

OBJECTS := src/mctyfile.o

BINDIR_LINUX = bin/linux

OBJDIR_TESTS = obj/test_mcity2k

MD=mkdir -v -p

CFLAGS := -Wall -Werror

$(BINDIR_LINUX)/libmcity2k.a: OBJDIR := obj/linux

test_mcity2k: LDFLAGS += $(shell pkg-config --libs check) -Lbin/linux/ -lmcity2k
test_mcity2k: CFLAGS += -DCHECK -g -Wall -Werror
test_mcity2k: OBJDIR := $(OBJDIR_TESTS)

mcity2k: LDFLAGS += -Lbin/linux/ -lmcity2k
mcity2k: CFLAGS += -g -Wall -Werror
mcity2k: OBJDIR := obj/mcity2k

all: $(BINDIR_LINUX)/libmcity2k.a test_mcity2k

test_mcity2k: $(BINDIR_LINUX)/libmcity2k.a $(OBJDIR_TESTS)/check.o $(OBJDIR_TESTS)/chkmcfil.o
	$(MD) $(dir $@)
	$(CC) -o $@ $^ $(LDFLAGS)

$(BINDIR_LINUX)/libmcity2k.a: $(addprefix obj/linux/,$(OBJECTS))
	$(MD) $(dir $@)
	$(AR) rcs $@ $^

obj/linux/%.o: %.c
	$(MD) $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJDIR_TESTS)/%.o: tests/$(notdir %.c)
	$(MD) $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS)

obj/msp430g2553/%.o: $(notdir %.c)
	$(MD) $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -rf obj; \
	rm -f test_mcity2k; \
	rm -rf bin

