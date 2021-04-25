TARGET_EXEC ?= trab3

BUILD_DIR ?= .
SRC_DIRS ?= ./src ./lib

MKDIR_P ?= mkdir -p

SRCS := $(shell find $(SRC_DIRS) -name *.c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CC = gcc
CFLAGS ?= $(INC_FLAGS) -pedantic -g -Wall -Werror -Wwrite-strings -O4

VALGRIND ?= valgrind
VALZIN_FLAGS ?=
VAL_FLAGS ?= $(VALZIN_FLAGS) --leak-check=full --track-origins=yes -s
VALZAO_FLAGS ?= $(VAL_FLAGS) --show-leak-kinds=all

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@
	make clean

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) */*.o */*.d

run: $(TARGET_EXEC)
	$(BUILD_DIR)/$(TARGET_EXEC) $(ARGS)

valzin: $(TARGET_EXEC)
	$(VALGRIND) $(VALZIN_FLAGS) $(FLAGS) $(BUILD_DIR)/$(TARGET_EXEC) $(ARGS)
val: $(TARGET_EXEC)
	$(VALGRIND) $(VAL_FLAGS) $(FLAGS) $(BUILD_DIR)/$(TARGET_EXEC) $(ARGS)
valzao: $(TARGET_EXEC)
	$(VALGRIND) $(VALZAO_FLAGS) $(FLAGS) $(BUILD_DIR)/$(TARGET_EXEC) $(ARGS)
