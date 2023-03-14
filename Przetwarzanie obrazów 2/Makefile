CC = g++
#CFLAGS = -std=gnu99 -Wextra -Wall

TARGET = grafika1102

SRCS = functions.cpp main.cpp #grconnect.hpp 
OBJS = functions.o main.o #grconnect.o

.PHONY: all clean distclean

all = $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

clean:
		$(RM) $(OBJS) 

distclean:
		$(RM) $(OBJS) $(TARGET)