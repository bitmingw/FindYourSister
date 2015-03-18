# Copyright (c) 2015, Ming Wen
 
# define variables
CC = g++
SOURCES = util.cpp json_handler.cpp main.cpp
OBJS = fys
CFLAGS = -g
LDFLAGS = -I/usr/local/lib
LDLIBS = -l opencv_core -l opencv_highgui -l opencv_features2d -l opencv_nonfree

# make target
all:
	mkdir -p bin
	cd src; \
	$(CC) $(CFLAGS) $(SOURCES) -o $(OBJS) $(LDFLAGS) $(LDLIBS); \
	mv $(OBJS) ../bin/

clean:
	cd bin; \
	rm -f *

