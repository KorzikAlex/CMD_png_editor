$(CC) = gcc
$(CFLAGS) = -g -Wall
$(LIBS) = -lpng
$(SRC_DIR) = sources
$(INCDIR) = include
$(OBJDIR) = sources

SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(patsubst $(SRC_DIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))
EXECUTABLE := coursework

all:
	$(CC) $(CXXFLAGS) $^ -o $@ $(LIBS)

clean:
	rm -r $(OBJDIR) $(EXECUTABLE)