CC         := gcc
TARGET     := warpframe
SRC_DIR    := src
INC_DIR    := include
BUILD_DIR  := build
VENDOR_DIR := vendor
VENDOR_SRC_DIR := $(VENDOR_DIR)/src

OPT   ?= -O2 -g
SAN   ?=
EXTRA ?=

INCLUDES := -I$(INC_DIR) -I$(VENDOR_DIR)/include

CFLAGS        := -std=c11 -Wall -Wextra -Wpedantic $(OPT) $(SAN) $(EXTRA) $(INCLUDES)
VENDOR_CFLAGS := -std=c11 -w $(OPT) $(EXTRA) $(INCLUDES)
LDFLAGS       := $(SAN)
LDLIBS        := -lSDL2 -lpthread -lm

SRCS        := $(wildcard $(SRC_DIR)/*.c)
VENDOR_SRCS := $(wildcard $(VENDOR_SRC_DIR)/*.c)
OBJS        := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
VENDOR_OBJS := $(patsubst $(VENDOR_SRC_DIR)/%.c,$(BUILD_DIR)/vendor_%.o,$(VENDOR_SRCS))
ALL_OBJS    := $(OBJS) $(VENDOR_OBJS)
DEPS        := $(ALL_OBJS:.o=.d)

.PHONY: all run run-asan debug asan release clean

all: $(TARGET)

$(TARGET): $(ALL_OBJS)
	$(CC) $(LDFLAGS) $(ALL_OBJS) -o $@ $(LDLIBS)

$(BUILD_DIR):
	@mkdir -p $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DIR)/vendor_%.o: $(VENDOR_SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(VENDOR_CFLAGS) -MMD -MP -c $< -o $@

debug:
	@$(MAKE) --no-print-directory clean
	@$(MAKE) --no-print-directory OPT="-O0 -g3" EXTRA="-DWF_DEBUG"

asan:
	@$(MAKE) --no-print-directory clean
	@$(MAKE) --no-print-directory OPT="-O0 -g3" EXTRA="-DWF_DEBUG" \
		SAN="-fsanitize=address,undefined -fno-sanitize=alignment -fno-omit-frame-pointer -fno-sanitize-recover=all"

release:
	@$(MAKE) --no-print-directory clean
	@$(MAKE) --no-print-directory OPT="-O3" EXTRA="-DNDEBUG"

run: all
	./$(TARGET) ./assets/triangle.obj

run-asan: asan
	ASAN_OPTIONS=abort_on_error=1:detect_stack_use_after_return=1 \
	UBSAN_OPTIONS=print_stacktrace=1 \
	./$(TARGET) ./assets/triangle.obj

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

-include $(DEPS)
