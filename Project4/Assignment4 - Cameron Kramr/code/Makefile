CC = gcc
CFLAGS = -g
DEPS = cordic.h
OBJ  = cordic.o cordic_test.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
cordic_test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
