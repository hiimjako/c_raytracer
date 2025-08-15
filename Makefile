CC=gcc
O=main

.PHONY: build
build:
	$(CC) main.c -o $(O) -O2 -Wall

.PHONY: run
run:
	./$(O)
