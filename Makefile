EXEC = main

SRC = main.cpp compression.cpp dicionario.cpp

CXX = g++
CXXFLAGS = 

$(EXEC): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXEC)

run: $(EXEC)
	./$(EXEC)

clean:
	rm -f $(EXEC)

.PHONY: clean run