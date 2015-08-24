all: gates.h gates.c chips.h chips.c alu.h alu.c main.c
	gcc -Wall -o cpu gates.c chips.c alu.c main.c
