all:
	clang $(shell find ./kson -type f -name "*.c") main.c -o program
