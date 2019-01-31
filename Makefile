# Modified from https://spin.atomicobject.com/2016/08/26/makefile-c-projects/

TARGET_EXEC ?= a.out

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src

GTEST_DIR := ./extern/googletest/googletest
GTEST_INC_DIR := $(GTEST_DIR)/include
GTEST_SRC_DIR := $(GTEST_DIR)/src

INC_DIRS ?= $(GTEST_INC_DIR)

SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
#$(info SRCS = $(SRCS))
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

CXX := clang++
#CXX := g++
CXXFLAGS := -std=c++14 -Wall -Wextra -Wpedantic -g -fsanitize=address -fno-omit-frame-pointer -pthread
LDFLAGS := -g -fsanitize=address -pthread

INC_FLAGS := $(addprefix -I,$(INC_DIRS))
CPPFLAGS ?= $(INC_FLAGS) -MMD -MP

$(BUILD_DIR)/$(TARGET_EXEC): $(BUILD_DIR)/libgtest.a $(OBJS)
	$(CXX) $(OBJS) $(BUILD_DIR)/libgtest.a -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.cpp.o: %.cpp 
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/libgtest.a: $(GTEST_SRC_DIR)/gtest-all.cc
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(GTEST_DIR) -c $< -o $(BUILD_DIR)/gtest-all.o
	ar -rv $(BUILD_DIR)/libgtest.a $(BUILD_DIR)/gtest-all.o

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p

