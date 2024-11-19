# Nome do executável
EXEC = main

# Arquivos de origem
SRC = main.cpp compression.cpp dicionario.cpp

# Compilador e flags
CXX = g++
CXXFLAGS = # Flags opcionais de compilação

# Regra para compilar e criar o executável
$(EXEC): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXEC)

# Regra para rodar o executável
run: $(EXEC)
	./$(EXEC)

# Limpeza dos arquivos compilados
clean:
	rm -f $(EXEC)

# Phony targets (não correspondem a arquivos físicos)
.PHONY: clean run