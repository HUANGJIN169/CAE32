#Por si se ocupa export PKG_CONFIG_PATH=/usr/lib/x86_64-linux-gnu/pkgconfig

all:
	gcc `pkg-config --cflags gtk+-3.0` main.c -o as `pkg-config --libs gtk+-3.0`

