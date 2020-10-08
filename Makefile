CC = g++

OFLAGS = -std=c++11 -O3
CFLAGS = -g3 -Wall -Wextra
LDFLAGS =

BDIR = bin
ODIR = build
IDIR = include
SDIR = src

EXEC1 = lsc

_DEPS =
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o input.o data.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) $(OFLAGS) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

all: $(BDIR)/$(EXEC1)

$(BDIR)/$(EXEC1): $(OBJ)
	$(CC) $(OFLAGS) $(CFLAGS) $^ -o $@ $(LDFLAGS)

.PHONY: clean run valgrind

run:
	./$(BDIR)/$(EXEC1) \
	-d /home/fotiadis/Downloads/project/pr/assets/t10k-images-idx3-ubyte \
	-k 10 \
	-R 2.4 \

valgrind:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(BDIR)/$(EXEC1) \
	-d /home/fotiadis/Downloads/project/pr/assets/t10k-images-idx3-ubyte \
	-k 10 \
	-R 2.4 \

clean:
	rm -f $(ODIR)/*.o
	rm -f $(BDIR)/$(EXEC1)
