CC = gcc
FLAGS = -Wall $(pkg-config allegro-5 allegro_font-5 allegro_audio-5 allegro_acodec-5 --libs --cflags) `pkg-config --cflags --libs gtk+-3.0`
BIN = main libbt.a libfdr.a
SOURCE = main.c

all:
	$(CC) $(SOURCE) $(FLAGS) -o $(BIN)
