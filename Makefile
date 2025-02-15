TARGET_EXEC := gfxproto

BUILD_DIR := ./build
SRC_DIRS := ./src 

SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')
SRCS += ./lib/Adafruit-GFX-Library/Adafruit_GFX.cpp

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d) ./lib/Adafruit-GFX-Library
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
LDFLAGS := `sdl2-config --cflags --libs`

CPPFLAGS := $(INC_FLAGS) -MMD -MP -DARDUINO=100 `sdl2-config --cflags --libs`

$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR) $(TARGET_EXEC)

init_subs:
	git submodule update --init --recursive --depth=1

update_subs:
	git submodule update --recursive --remote

-include $(DEPS)
