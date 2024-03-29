# Simple makefile

EXE=doAnalysis

SOURCES=$(wildcard *.cc)
OBJECTS=$(SOURCES:.cc=.o)
HEADERS=$(SOURCES:.cc=.h)

CC          = g++
CXX         = g++
CXXFLAGS    = -g -O2 -Wall -fPIC -Wshadow -Woverloaded-virtual
LD          = g++
LDFLAGS     = -g -O2
SOFLAGS     = -g -shared
CXXFLAGS    = -g -O2 -Wall -fPIC -Wshadow -Woverloaded-virtual
LDFLAGS     = -g -O2
ROOTLIBS    = $(shell root-config --libs)
ROOTCFLAGS  = $(shell root-config --cflags)
CXXFLAGS   += $(ROOTCFLAGS)
CFLAGS      = $(ROOTCFLAGS) -Wall -Wno-unused-function -g -O2 -fPIC -fno-var-tracking
EXTRACFLAGS = $(shell rooutil-config)
EXTRAFLAGS  = -fPIC -ITMultiDrawTreePlayer -Wunused-variable -lTMVA -lEG -lGenVector -lXMLIO -lMLP -lTreePlayer

$(EXE): process.o SDL.o helper.o
	$(LD) $(CXXFLAGS) $(LDFLAGS) $^ $(ROOTLIBS) $(EXTRAFLAGS) -o $@

multiplicity: multiplicity.o SDL.o helper.o
	$(LD) $(CXXFLAGS) $(LDFLAGS) $^ $(ROOTLIBS) $(EXTRAFLAGS) -o $@

inefficiency: inefficiency.o SDL.o helper.o
	$(LD) $(CXXFLAGS) $(LDFLAGS) $^ $(ROOTLIBS) $(EXTRAFLAGS) -o $@

temp: temp.o SDL.o helper.o
	$(LD) $(CXXFLAGS) $(LDFLAGS) $^ $(ROOTLIBS) $(EXTRAFLAGS) -o $@

SDL.o: SDL.cc SDL.h
	$(CC) $(CFLAGS) $(EXTRACFLAGS) $< -c -o $@

process.o: process.cc process.h sdl_types.h
	$(CC) $(CFLAGS) $(EXTRACFLAGS) $< -c -o $@

multiplicity.o: multiplicity.cc multiplicity.h sdl_types.h
	$(CC) $(CFLAGS) $(EXTRACFLAGS) $< -c -o $@

inefficiency.o: inefficiency.cc inefficiency.h sdl_types.h
	$(CC) $(CFLAGS) $(EXTRACFLAGS) $< -c -o $@

temp.o: temp.cc sdl_types.h
	$(CC) $(CFLAGS) $(EXTRACFLAGS) $< -c -o $@

helper.o: helper.cc helper.h
	$(CC) $(CFLAGS) $(EXTRACFLAGS) $< -c -o $@

all: doAnalysis multiplicity inefficiency temp

clean:
	rm -f $(OBJECTS) $(EXE)
