
# vim: ft=make noexpandtab

BINDIR := bin
OBJDIR := obj

OBJECTS := src/mctyfile.o src/mctymaps.o
OBJECTS_TESTS := \
	$(OBJDIR)/tests/check.o \
	$(OBJDIR)/tests/chkmcfil.o \
	$(OBJDIR)/tests/chkmcmap.o \
	$(OBJDIR)/tests/chksetup.o

MD := mkdir -v -p

CFLAGS := -Wall -Werror -fpic

test_mcity2k: LDFLAGS += $(shell pkg-config --libs check) -L$(BINDIR)/static -lmcity2k
test_mcity2k: CFLAGS += -DCHECK -g

all: $(BINDIR)/static/libmcity2k.a $(BINDIR)/shared/libmcity2k.so test_mcity2k

test_mcity2k: $(BINDIR)/static/libmcity2k.a $(OBJECTS_TESTS)
	$(MD) $(dir $@)
	$(CC) -o $@ $^ $(LDFLAGS)

$(BINDIR)/static/libmcity2k.a: $(OBJECTS)
	$(MD) $(dir $@)
	$(AR) rcs $@ $^

$(BINDIR)/shared/libmcity2k.so: $(OBJECTS)
	$(MD) $(dir $@)
	$(CC) -shared -o $@ $^

$(OBJDIR)/%.o: %.c
	$(MD) $(dir $@)
	$(CC) -c -o $@ $(CFLAGS) $<

.PHONY: clean

clean:
	rm -rf $(OBJDIR); \
	rm -f test_mcity2k; \
	rm -rf $(BINDIR)

