CC = g++
#CFLAGS = -std=gnu99 -Wextra -Wall

TARGET = grpr

SRCS = grfunctions.cpp grmain.cpp #grconnect.hpp 
OBJS = grfunctions.o grmain.o #grconnect.o

.PHONY: all clean distclean

all = $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

clean:
		$(RM) $(OBJS) 

distclean:
		$(RM) $(OBJS) $(TARGET)



# default:
# 	g++ grmain.cpp -o out 


# program: modul_obrazy1.o main_obrazy1.c
# 	gcc -o program modul_obrazy1.o main_obrazy1.c

# modul_obrazy1.o:modul_obrazy1.c
# 	gcc -c -std=c99  modul_obrazy1.c
