CC = g++

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
	-d ./assets/t10k \
	-i ../project3/output_dataset \
	-q ./assets/queryFile \
	-s ../project3/output_queryset \
	-o ./logs/logs.txt \
	-N 1

valgrind-lsh:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(BDIR)/$(EXEC1) \
	-i ./assets/t10k \
	-q ./assets/queryFile \
	-o ./logs/logs.txt \
	-N 10

run-cluster-classic:
	./$(BDIR)/$(EXEC3) \
	-d ./assets/t10k \
	-i ./assets/output_dataset \
	-n ./assets/cluster_dataset \
	-c ./cluster.conf \
	-o ./logs/logs.txt

valgrind-cluster:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(BDIR)/$(EXEC3) \
	-d ./assets/t10k \
	-i ../project3/output_dataset \
	-n ../Neural-Net/cluster_dataset \
	-c ./cluster.conf \
	-o ./logs/logs.txt
clean:
	rm -f $(ODIR)/*.o
	rm -f $(BDIR)/$(EXEC1)
	rm -f $(BDIR)/$(EXEC2)
	rm -f $(BDIR)/$(EXEC3)
