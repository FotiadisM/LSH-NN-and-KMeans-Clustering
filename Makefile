CC = g++ -std=c++11

OFLAGS = -std=c++11 -O3
CFLAGS = -g3 -Wall -Wextra
LDFLAGS =

BDIR = bin
ODIR = build
IDIR = include
SDIR = src

EXEC1 = lsh
EXEC2 = cube
EXEC3 = cluster

_DEPS = data.h input.h LSH.h hashTable.h kmeansplusplus.h hyperCube.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o input.o data.o LSH.o hashTable.o kmeansplusplus.o hyperCube.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) $(OFLAGS) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

all: $(BDIR)/$(EXEC1) $(BDIR)/$(EXEC2) $(BDIR)/$(EXEC3)

$(BDIR)/$(EXEC1): $(OBJ)
	$(CC) $(OFLAGS) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BDIR)/$(EXEC2): $(OBJ)
	$(CC) $(OFLAGS) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BDIR)/$(EXEC3): $(OBJ)
	$(CC) $(OFLAGS) $(CFLAGS) $^ -o $@ $(LDFLAGS)

.PHONY: clean run* valgrind*

run-lsh:
	./$(BDIR)/$(EXEC1) \
	-i ./assets/t10k \
	-o ./logs/logs.txt \
	-N 10

valgrind-lsh:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(BDIR)/$(EXEC1) \
	-i ./assets/t10k \
	-o ./logs/logs.txt \
	-N 10

run-hc:
	./$(BDIR)/$(EXEC2) \
	-i ./assets/t10k \
	-o ./logs/logs.txt \
	-N 10

valgrind-hc:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(BDIR)/$(EXEC2) \
	-i ./assets/t10k \
	-o ./logs/logs.txt \
	-N 10


run-cluster:
	./$(BDIR)/$(EXEC3) \
	-i ./assets/t10k \
	-c ./cluster.conf \
	-o ./logs/logs.txt \
	-m LSH

valgrind-cluster:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(BDIR)/$(EXEC3) \
	-i ./assets/t10k \
	-c ./cluster.conf \
	-o ./logs/logs.txt \
	-m LSH

clean:
	rm -f $(ODIR)/*.o
	rm -f $(BDIR)/$(EXEC1)
	rm -f $(BDIR)/$(EXEC2)
	rm -f $(BDIR)/$(EXEC3)
