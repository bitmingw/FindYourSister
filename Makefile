# Copyright (c) 2015, Ming Wen
.SUFFIXES: 

CXX := g++
CXXFLAGS := -Wall -g
INCLUDES := -Iinclude -I/usr/local/lib
LIBS := -l opencv_core -l opencv_highgui -l opencv_features2d -l opencv_nonfree
TARGET := fys

INCLUDEDIR := include
OBJDIR := bin
SRCDIR := src
TESTDIR := test
INCLUDESOURCE := $(wildcard $(INCLUDEDIR)/*.hpp)
SRCOBJ := $(patsubst %.cpp, %.o, $(wildcard $(SRCDIR)/*.cpp))
TESTOBJ := $(patsubst %.cpp, %.o, $(wildcard $(TESTDIR)/*.cpp))

.PHONY: all clean`

# make target
all: $(TARGET)

$(TARGET): $(SRCOBJ) $(TESTOBJ)
	$(CXX) $(INCLUDES) $(CXXFLAGS) $(LIBS) $^ -o $@
	@mkdir -p bin
	@mv $@ bin/$@

$(SRCOBJ): $(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $< -o $@
$(TESTOBJ): $(TESTDIR)/%.o: $(TESTDIR)/%.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $< -o $@

$(SRCDIR)/%.cpp: $(INCLUDESOURCE)
$(TESTDIR)/%.cpp: $(INCLUDESOURCE)

clean:
	@rm -f bin/*
	@rm -f src/*.o
	@rm -f test/*.o

