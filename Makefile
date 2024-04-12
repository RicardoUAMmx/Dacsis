
IDIR=include
SRC=src
CC=gcc
CFLAGS=-I$(IDIR)


_DEPS=dacsis.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=dacsis.o main.o
OBJ=$(patsubst %,$(SRC)/%,$(_OBJ))

$(SRC)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

dacsis: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(SRC)/*.o *~ core $(INCDIR)/*~
