OBJS	= prog.o coffee.o display.o menu.o order.o shop.o
SOURCE	= prog.cpp coffee.cpp display.cpp menu.cpp order.cpp shop.cpp
HEADER	= coffee.h display.h menu.h order.h shop.h
OUT	= prog
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

prog.o: prog.cpp
	$(CC) $(FLAGS) prog.cpp 

coffee.o: coffee.cpp
	$(CC) $(FLAGS) coffee.cpp 

display.o: display.cpp
	$(CC) $(FLAGS) display.cpp 

menu.o: menu.cpp
	$(CC) $(FLAGS) menu.cpp 

order.o: order.cpp
	$(CC) $(FLAGS) order.cpp 

shop.o: shop.cpp
	$(CC) $(FLAGS) shop.cpp 


clean:
	rm -f $(OBJS) $(OUT)