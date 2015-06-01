BINDIR=bin
OBJDIR=obj
SRCDIR=src

BINNAME=sample
BIN=$(BINDIR)/$(BINNAME)
CLEAN=clean

DEBUGDIR=Debug
RELEASEDIR=Release

DEBUG=debug
RELEASE=release

GPP=g++
CFLAGS=-Wall -Wextra -Werror

GRAYLIB_DIR=../graylib

INCLUDE="-I$(GRAYLIB_DIR)/src"
LIB="-L$(GRAYLIB_DIR)/build"

CPPFILES=$(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/cl/*.cpp)

OBJ=$(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(CPPFILES))

OBJDEBUG=$(addprefix $(DEBUGDIR)/,$(OBJ))
OBJRELEASE=$(addprefix $(RELEASEDIR)/,$(OBJ))

BINDEBUG=$(addprefix $(DEBUGDIR)/,$(BIN))
BINRELEASE=$(addprefix $(RELEASEDIR)/,$(BIN))

FLAGSDEBUG=-g -pg
FLAGSRELEASE=-O2

LIBS=-lOpenCL

$(DEBUG): $(OBJDEBUG)
	$(GPP) -o $(BINDEBUG) $(OBJDEBUG) $(LIB) -lgray-d $(LIBS)

$(RELEASE): $(OBJRELEASE)
	$(GPP) -o $(BINRELEASE) $(OBJRELEASE) $(LIB) -lgray $(LIBS)

$(CLEAN):
	rm -f $(BINDEBUG) $(BINRELEASE) $(OBJDEBUG) $(OBJRELEASE)

$(DEBUGDIR)/$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(GPP) $(CFLAGS) $(FLAGSDEBUG) $(INCLUDE) -c -o $@ $<

$(RELEASEDIR)/$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(GPP) $(CFLAGS) $(FLAGSRELEASE) $(INCLUDE) -c -o $@ $<

