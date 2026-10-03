.DEFAULT_GOAL := archive
BUILD ?= debug
CC ?= gcc
AR ?= ar


# DIRECTORIES AND FILES

## source files .c
SRCDIR := src
## header files .h
INCDIR := include
## build artefacts .o
OBJDIR := build/$(BUILD)
## dependency files .d
DEPDIR := $(OBJDIR)/.dep
## archive files .a
LIBDIR := lib/$(BUILD)
## compiled binaries
BINDIR := bin/$(BUILD)

SRCFILES := $(wildcard $(SRCDIR)/*.c)
OBJFILES := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCFILES))
DEPFILES := $(patsubst $(SRCDIR)/%.c, $(DEPDIR)/%.d, $(SRCFILES))

TESTSOURCES := $(filter $(SRCDIR)/%.test.c, $(SRCFILES))
TESTBINARIES := $(patsubst $(SRCDIR)/%.test.c, $(BINDIR)/%-test, $(TESTSOURCES))


# C PREPROCESSOR/COMPILER/LINKER FLAGS

CPPFLAGS := -I$(INCDIR)
CFLAGS := -std=c99 -Wall -Wextra -pedantic -Werror
LDFLAGS := -L$(LIBDIR)
LDLIBS := -ljzds

ifeq ($(BUILD), debug)
  CFLAGS += -g -fsanitize=address,undefined
  LDFLAGS += -g -fsanitize=address,undefined
else ifeq ($(BUILD), release)
  CPPFLAGS += -DNDEBUG
  CFLAGS += -O2
else
  $(error BUILD must be either 'debug' or 'release')
endif


# DEPENDENCY MANAGEMENT

## intentionally no colon
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
## force .d to have a later timestampt than corresponding .o
POSTCOMP = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d && touch $@

$(DEPDIR):
	mkdir -p $@


# COMMANDS

## intentionally no colon
COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) -c
## intentionally no colon
LINK.o = $(CC) $(LDFLAGS)


# ACTUAL BUILD INSTRUCTIONS

$(OBJDIR):
	mkdir -p $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPDIR)/%.d \
             | $(OBJDIR) $(DEPDIR)
	$(COMPILE.c) $(OUTPUT_OPTION) $<
	$(POSTCOMP)

$(LIBDIR):
	mkdir -p $@

$(LIBDIR)/libjzds.a: $(filter-out $(OBJDIR)/%.test.o, $(OBJFILES)) \
                   | $(LIBDIR)
	$(AR) rcs $@ $^

$(BINDIR):
	mkdir -p $@

$(BINDIR)/%-test: $(OBJDIR)/%.test.o $(LIBDIR)/libjzds.a \
                | $(BINDIR)
	$(LINK.o) $(OUTPUT_OPTION) $< $(LDLIBS)

.PHONY: archive
archive: $(LIBDIR)/libjzds.a

.PHONY: test
test: $(TESTBINARIES)
	@for test in $(TESTBINARIES); do \
		echo "$$test";               \
		./$$test || exit 1;          \
	done

.PHONY: clean
clean:
	rm -rf build/ lib/ bin/


# DEPENDENCY MANAGEMENT, CONTINUED

## intentionally no recipe
$(DEPFILES):

## must stay at the end of the file
include $(wildcard $(DEPFILES))
