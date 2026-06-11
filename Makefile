CC      := gcc
TARGET  := warpframe

SRC_DIR   := src
INC_DIR   := include
BUILD_DIR := build

CFLAGS  := -std=c11 -Wall -Wextra -Wpedantic -O2 -g
CFLAGS  += -I$(INC_DIR)

LDFLAGS := -lSDL2 -lpthread -lm

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

.PHONY: all run clean debug release dirs

all: dirs $(TARGET)

dirs:
	@mkdir -p $(BUILD_DIR)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | dirs
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

run: all
	./$(TARGET)

debug: CFLAGS += -O0 -DWF_DEBUG
debug: clean all

release: CFLAGS += -O3 -DNDEBUG
release: clean all

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

-include $(DEPS)
