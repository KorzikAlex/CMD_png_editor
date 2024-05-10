CC = gcc
CFLAGS = -g -Werror -std=gnu99
LIBS = -lpng
SRCDIR = sources
OBJDIR = objects
INCDIR = include
DOCSDIR = docs/html

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))
EXECUTABLE = cw
DOXYGEN_CONFIG = Doxyfile

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean_objects:
	rm -rf $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(EXECUTABLE)

clean_docs:
	rm -rf $(DOCSDIR)

docs:
	@doxygen $(DOXYGEN_CONFIG)

.PHONY: all clean docs
