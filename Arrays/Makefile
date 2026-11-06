SRC := $(wildcard ./*.cpp)
OUT = ./build
OBJ := $(addprefix $(OUT)/, $(notdir $(SRC:.cpp=.o)))
CXX := g++
FLAGS := -std=c++11 -Wall -Wextra
BIN := $(OUT)/arrays

$(info == Compiler info INIT ==)
$(info $(CXX))
$(info $(SRC))
$(info $(OBJ))
$(info $(OUT))
$(info $(FLAGS))
$(info == Compiler info END ==)

.PHONY: all clean

all: clean $(BIN)

clean:
	rm -fr $(OUT)

exec:
	$(BIN)

$(OUT):
	mkdir -p $(OUT)

$(OUT)/%.o: %.cpp | $(OUT)
	@echo "Compiling C++: $<"
	$(CXX) $(FLAGS) -c $< -o $@

$(BIN): $(OBJ) | $(OUT)
	$(CXX) $(CXXFLAGS) $^ -o $@
