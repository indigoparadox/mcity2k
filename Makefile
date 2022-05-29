
# vim: ft=make noexpandtab

OBJECTS := src/mctyfile.o src/mctymaps.o
OBJECTS_TESTS := tests/check.o tests/chkmcfil.o tests/chkmcmap.o tests/chksetup.o

BINDIR = bin

OBJDIR = obj

MD=mkdir -v -p

CFLAGS := -Wall -Werror -fpic

$(BINDIR)/libmcity2k.a: OBJDIR := obj/linux

test_mcity2k: LDFLAGS += $(shell pkg-config --libs check) -L$(BINDIR)/static -lmcity2k
test_mcity2k: CFLAGS += -DCHECK -g

all: $(BINDIR)/static/libmcity2k.a $(BINDIR)/shared/libmcity2k.so test_mcity2k

test_mcity2k: $(BINDIR)/static/libmcity2k.a $(addprefix $(OBJDIR)/,$(OBJECTS_TESTS))
	$(MD) $(dir $@)
	$(CC) -o $@ $^ $(LDFLAGS)

$(BINDIR)/static/libmcity2k.a: $(addprefix $(OBJDIR)/,$(OBJECTS))
	$(MD) $(dir $@)
	$(AR) rcs $@ $^

$(BINDIR)/shared/libmcity2k.so: $(addprefix $(OBJDIR)/,$(OBJECTS))
	$(MD) $(dir $@)
	$(CC) -shared -o $@ $^

$(OBJDIR)/%.o: %.c
	$(MD) $(dir $@)
	$(CC) -c -o $@ $(CFLAGS) $<

.PHONY: clean

clean:
	rm -rf obj; \
	rm -f test_mcity2k; \
	rm -rf bin

