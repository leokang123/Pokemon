CC = gcc
CFLAGS = -pthread -lopenal -lncursesw

SRCDIR = ./src
INCDIR = ./src/includedef
OBJDIR = ./obj

SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

EXEC = tstart

$(EXEC): $(OBJ)
	$(CC) $^ $(CFLAGS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) -c $< -o $@ -I$(INCDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

.PHONY: clean

clean:
	rm -f $(OBJDIR)/*.o $(EXEC)
