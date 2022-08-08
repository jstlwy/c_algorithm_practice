CC := gcc
CFLAGS := -Wall -Wextra -Werror
LDFLAGS := -lncurses
# ncurses used in:
# main
# utils
# input
# arrayutils
# dllist
.PHONY: all clean

srcdir := ./src
objdir := ./obj
exclude := $(srcdir)/pqueue.c
src := $(filter-out $(exclude), $(wildcard $(srcdir)/*.c))
headers := $(filter-out $(srcdir)/main.h, $(patsubst %.c, %.h, $(src)))
obj := $(patsubst $(srcdir)/%.c, $(objdir)/%.o, $(src))
binary := algorithm_comparator

all: $(binary)

$(binary): $(obj)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

# Generic object file creation rule
$(objdir)/%.o: $(srcdir)/%.c
	$(CC) -c $< -o $@

# Individual file dependencies
$(objdir)/main.o: $(srcdir)/main.c $(headers)
$(objdir)/utils.o: $(srcdir)/utils.c $(srcdir)/utils.h
$(objdir)/input.o: $(srcdir)/input.c $(srcdir)/input.h
$(objdir)/wqunion.o: $(srcdir)/wqunion.c $(srcdir)/wqunion.h
$(objdir)/maxsubarray.o: $(srcdir)/maxsubarray.c $(srcdir)/maxsubarray.h
$(objdir)/arrayutils.o: $(srcdir)/arrayutils.c $(srcdir)/arrayutils.h
$(objdir)/arraysort.o: $(srcdir)/arraysort.c $(srcdir)/arraysort.h
$(objdir)/listsort.o: $(srcdir)/listsort.c $(srcdir)/listsort.h $(srcdir)/dllist.h
$(objdir)/dllist.o: $(srcdir)/dllist.c $(srcdir)/dllist.h

clean:
	rm -f $(obj) $(binary)
