SRCDIR  	:= src/
OBJDIR  	:= obj/
BINDIR  	:= bin/
DATADIR  	:= data/avl data/btree
NAME    	:= btree
EXE     	:= $(BINDIR)$(NAME)

SFILES  	:= c
HFILES  	:= h
OFILES  	:= o
CC      	:= gcc
CFLAGS  	:= -c -Wall -g

SOURCES 	:= $(shell find $(SRCDIR) -name "*.$(SFILES)")
HEADERS 	:= $(shell find $(SRCDIR) -name "*.$(HFILES)")
OBJECTS 	:= $(patsubst $(SRCDIR)%.$(SFILES), $(OBJDIR)%.$(OFILES), $(SOURCES))

ALLFILES := $(SOURCES)

.PHONY: all clean

all: check_folders $(EXE)

obj/main.o: $(SRCDIR)main.$(SFILES)
	$(CC) $(SRCDIR)main.$(SFILES) $(CFLAGS) -o obj/main.o

$(EXE): $(OBJECTS)
	$(CC) $^ -o $@

$(OBJDIR)%$(OFILES): $(SRCDIR)%$(SFILES) $(SRCDIR)%$(HFILES)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -o $@

plot:
	python ./scripts/plot.py

check_folders:
	@mkdir -p $(SRCDIR) $(OBJDIR) $(BINDIR) $(DATADIR)

clean:
	rm -fr $(OBJECTS) $(EXE)
	@rm -fr $(OBJDIR) $(BINDIR)
