# ---------- Configuracion ----------
CXX       := g++
CXXFLAGS  := -std=c++17 -Wall -Wextra -Wpedantic -g -Iinclude
TARGET    := build/practica
SRC_DIR   := src
OBJ_DIR   := build

SRCS      := $(wildcard $(SRC_DIR)/*.cpp)
OBJS      := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
DEPS      := $(OBJS:.o=.d)

# ---------- Reglas ----------
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# -MMD -MP genera archivos .d con las dependencias de headers
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

run: $(TARGET)
	./$(TARGET)

# Autoinclusion de dependencias (recompila si cambia un header)
-include $(DEPS)

.PHONY: all clean run