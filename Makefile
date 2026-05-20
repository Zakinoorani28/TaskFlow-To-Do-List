# =====================================================
#   Simple To-Do List — Makefile
#   Type: make       → compile
#         make run   → compile and run
#         make clean → delete compiled file
# =====================================================

CXX      = g++
CXXFLAGS = -std=c++17 -Wall
TARGET   = simpletodo
SRC      = main.cpp

# Compile
$(TARGET): $(SRC)
	@echo "  Compiling..."
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)
	@echo "  Done! Type: ./simpletodo"

# Compile and run
run: $(TARGET)
	./$(TARGET)

# Delete compiled file
clean:
	rm -f $(TARGET)
	@echo "  Cleaned."

.PHONY: run clean
