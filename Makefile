CC = g++ -std=c++11

OFLAGS = -std=c++11 -O3
CFLAGS = -g3 -Wall -Wextra
LDFLAGS =

BDIR = bin
ODIR = build
IDIR = include
SDIR = src

EXEC1 = lsh

_DEPS = data.h input.h LSH.h hashTable.h hyperCube.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o input.o data.o LSH.o hashTable.o hyperCube.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) $(OFLAGS) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

all: $(BDIR)/$(EXEC1)

$(BDIR)/$(EXEC1): $(OBJ)
	$(CC) $(OFLAGS) $(CFLAGS) $^ -o $@ $(LDFLAGS)

.PHONY: clean run valgrind

run:
	./$(BDIR)/$(EXEC1) \
	-d /home/michalis/Downloads/project/train \
	-o /home/michalis/Downloads/project/logs.txt \
	-N 10

valgrind:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(BDIR)/$(EXEC1) \
	-d /home/michalis/Downloads/project/train \
	-o /home/michalis/Downloads/project/logs.txt \
	-N 10

clean:
	rm -f $(ODIR)/*.o
	rm -f $(BDIR)/$(EXEC1)
