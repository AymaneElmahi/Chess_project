CC = g++
CFLAGS ?= -Wall -W -Werror -g -O2 -std=c++11 -pedantic -Ofast

LDLIBS?=-lm -lstdc++

INCLUDE_PATH = ./include

TARGET   = echecs

SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(INCLUDE_PATH)/*.hpp)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)


$(BINDIR)/$(TARGET): $(OBJECTS)
	mkdir -p $(BINDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)
	@echo "\033[92mLinking complete!\033[0m"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDE_PATH)

run:
ifneq ($(wildcard $(BINDIR)/*),)
	$(BINDIR)/$(TARGET)
else
	@echo "\033[91mError: $(BINDIR)/$(TARGET) not found!\033[0m"
endif


debug:
	valgrind --leak-check=full --show-reachable=yes ./$(BINDIR)/$(TARGET)


.PHONY: clean 
clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(OBJDIR)/*.gcda
	rm -f $(OBJDIR)/*.gcno
	rm -f $(BINDIR)/$(TARGET)
