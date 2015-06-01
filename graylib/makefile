BINDIR=build
SRCDIR=src

BINNAME=libgray
CLEAN=clean

DEBUGDIR=Debug
RELEASEDIR=Release

DEBUG=debug
RELEASE=release

GPP=g++
AR=ar
CFLAGS=-Wall -Wextra -Werror
INCLUDE=-I$(SRCDIR)

CPPFILES=$(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/cl/*.cpp)

OBJ=$(patsubst $(SRCDIR)/%.cpp,%.o,$(CPPFILES))

OBJDEBUG=$(addprefix $(DEBUGDIR)/,$(OBJ))
OBJRELEASE=$(addprefix $(RELEASEDIR)/,$(OBJ))

BINDEBUG=$(BINDIR)/$(BINNAME)-d.a
BINRELEASE=$(BINDIR)/$(BINNAME).a

FLAGSDEBUG=-g -pg
FLAGSRELEASE=-O2

LIBS=-lOpenCL


$(DEBUG): $(OBJDEBUG)
	$(AR) rcs $(BINDEBUG) $(OBJDEBUG)

$(RELEASE): $(OBJRELEASE)
	$(AR) rcs $(BINRELEASE) $(OBJRELEASE)

$(CLEAN):
	rm -f $(BINDEBUG) $(BINRELEASE) $(OBJDEBUG) $(OBJRELEASE)

$(DEBUGDIR)/%.o: $(SRCDIR)/%.cpp
	$(GPP) $(CFLAGS) $(FLAGSDEBUG) $(INCLUDE) -DDEBUG -c -o $@ $<

$(RELEASEDIR)/%.o: $(SRCDIR)/%.cpp
	$(GPP) $(CFLAGS) $(FLAGSRELEASE) $(INCLUDE) -c -o $@ $<

