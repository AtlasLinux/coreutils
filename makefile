# Directories
SRC_DIR := src
BIN_DIR := bin

CC := clang

# Find all .c source files in SRC_DIR
SRCS := $(wildcard $(SRC_DIR)/*.c)

# Generate list of binaries in BIN_DIR by replacing src/ with bin/ and .c with nothing
BINS := $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%, $(SRCS))

# Default target
all: $(BINS)

# Rule to build each binary
$(BIN_DIR)/%: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $<

# Create bin directory if it doesn't exist
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# Clean target
clean:
	@rm -rf $(BIN_DIR)

.PHONY: all clean
