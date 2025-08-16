CC=gcc
O=main

.PHONY: build
build:
	@$(CC) *.c -o $(O) -O2 -Wall

.PHONY: run
run:
	@./$(O)

.PHONY: format
format:
	clang-format -i ./*.c ./*.h
