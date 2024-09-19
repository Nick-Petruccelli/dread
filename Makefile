CC=g++
CFLAGS= -lSDL2 -lSDL2_image
SRC=src
OBJ=obj
SRCS=$(wildcard $(SRC)/*.cpp)
OBJS=$(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))
BINDIR=bin
BIN=$(BINDIR)/main
TEST=tests
TESTS=$(wildcard $(TEST)/*.cpp)
TESTOBJS=$(patsubst $(TEST)/%.c, $(OBJ)/$(TEST)/%.o, $(TESTS))
TESTBIN=$(BINDIR)/test

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $@ $(CFLAGS)

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

run: $(BIN)
	./$(BIN)
clean:
	$(RM) $(BINDIR)/* $(OBJ)/*

test: $(TESTOBJS) $(filter-out $(OBJ)/main.o, $(OBJS))
	$(CC) $(filter-out $(OBJ)/main.o, $(OBJS)) $(TESTOBJS) -o $(TESTBIN) $(CFLAGS)
	./$(TESTBIN)
	rm ./$(TESTBIN)

$(OBJ)/$(TEST)/%.o: $(TEST)/%.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

debug: $(OBJS)
	$(CC) $(OBJS) -g -o $(BINDIR)/$@ $(CFLAGS)
