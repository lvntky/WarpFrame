CC        := gcc
TARGET    := warpframe
SRC_DIR   := src
INC_DIR   := include
BUILD_DIR := build
VENDOR_DIR:= vendor
VENDOR_SRC_DIR := $(VENDOR_DIR)/src

CFLAGS  := -std=c11 -Wall -Wextra -Wpedantic -O2 -g
CFLAGS  += -I$(INC_DIR) -I$(VENDOR_DIR)/include
LDFLAGS := -lSDL2 -lpthread -lm

SRCS        := $(wildcard $(SRC_DIR)/*.c)
VENDOR_SRCS := $(wildcard $(VENDOR_SRC_DIR)/*.c)

OBJS        := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
VENDOR_OBJS := $(patsubst $(VENDOR_SRC_DIR)/%.c,$(BUILD_DIR)/vendor_%.o,$(VENDOR_SRCS))
ALL_OBJS    := $(OBJS) $(VENDOR_OBJS)
DEPS        := $(ALL_OBJS:.o=.d)

.PHONY: all run clean debug release dirs

all: dirs $(TARGET)

dirs:
	@mkdir -p $(BUILD_DIR)

$(TARGET): $(ALL_OBJS)
	$(CC) $(ALL_OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | dirs
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DIR)/vendor_%.o: $(VENDOR_SRC_DIR)/%.c | dirs
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
