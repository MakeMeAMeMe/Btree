SRCDIR  	:= src/
OBJDIR  	:= obj/
BINDIR  	:= bin/
NAME    	:= btree
EXE     	:= $(BINDIR)$(NAME)

SFILES  	:= cpp
HFILES  	:= hpp
OFILES  	:= o
CC      	:= g++
CFLAGS  	:= -c -Wall

SOURCES 	:= $(shell find $(SRCDIR) -name "*.$(SFILES)")
HEADERS 	:= $(shell find $(SRCDIR) -name "*.$(HFILES)")
OBJECTS 	:= $(patsubst $(SRCDIR)%.$(SFILES), $(OBJDIR)%.$(OFILES), $(SOURCES))

ALLFILES := $(SOURCES)

.PHONY: all clean

all: check_folders $(EXE)

$(EXE): $(OBJECTS)
	$(CC) $^ -o $@ $(LFLAGS)

$(OBJDIR)%$(OFILES): $(SRCDIR)%$(SFILES) $(SRCDIR)%$(HFILES)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -o $@

check_folders:
	@mkdir -p $(SRCDIR) $(OBJDIR) $(BINDIR)

clean:
	rm -fr $(OBJECTS) $(EXE)
	@rm -fr $(OBJDIR) $(BINDIR)