CC = g++

CFLAGS ?= -g -Wall -Wextra -Werror -std=c++11 -pipe -Wpedantic
LDLIBS ?=

INCLUDE_PATH = ./include

TARGET    = chess

SRCDIR    = src
OBJDIR    = obj
BINDIR    = bin

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(INCLUDE_PATH)/*.hpp)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

PATH_TO_EXE = $(BINDIR)/$(TARGET)

all : release

debug: CFLAGS += -Og -DDEBUG -g
debug: clean $(PATH_TO_EXE)
	@echo "\033[33mRunning in debug mode!\033[0m"

release: CFLAGS += -Ofast
release: clean $(PATH_TO_EXE)
	@echo "\033[36mRunning in release mode!\033[0m"

run:
ifneq ("$(wildcard $(PATH_TO_EXE))", "")
	./$(PATH_TO_EXE)
else
	@echo "\033[31mNo executable found!\033[0m"
endif

run-release: release
	./$(PATH_TO_EXE)

run-debug: debug
	valgrind --leak-check=full --show-leak-kinds=all --vgdb=full -s ./$(PATH_TO_EXE)

$(PATH_TO_EXE): $(OBJECTS)
	mkdir -p $(BINDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)
	@echo "\033[92mLinking complete!\033[0m"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(INCLUDES)
	mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS) -isystem$(INCLUDE_PATH)


.PHONY: clean cov
clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(OBJDIR)/*.gcda
	rm -f $(OBJDIR)/*.gcno
	rm -f $(PATH_TO_EXE)
