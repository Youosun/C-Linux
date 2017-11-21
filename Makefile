SOURCE:=$(wildcard *.c)
OBJET:=$(patsubst %.c,%.o,$(SOURCE))
ELF:=main
CFLAGS:=-g -Wall
main:$(OBJET)
	gcc $(OBJET) -o $(ELF)
.PHONY:clear
clear:
	rm $(OBJET)
