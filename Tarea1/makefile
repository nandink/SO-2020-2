TARGET = pruebita
CFLAGS = -Wall -g

all:
	gcc prueba.c -o $(TARGET) $(CFLAGS)
	make clear

run: all
	./$(TARGET)

clear:
	find . -name '*.o' -type f -delete