CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SRCS = main.c io.c test.c move.c pentaroll.c weakai.c
OBJS = $(SRCS:.c=.o)

TARGET = fuji.out

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) *.h~ *.c~
