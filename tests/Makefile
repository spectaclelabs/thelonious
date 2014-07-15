BUILD_DIR = build
TEST_BUILD_DIR = $(BUILD_DIR)/tests
THELONIOUS_BUILD_DIR = $(BUILD_DIR)/thelonious

# Source files
TEST_SRC =  $(wildcard *.cc)
TEST_SRC += $(wildcard constants/*.cc)
TEST_SRC += $(wildcard dsl/*.cc)
TEST_SRC += $(wildcard dsp/*.cc)
TEST_SRC += $(wildcard operators/*.cc)

THELONIOUS_SRC = $(shell find ../thelonious -type f -name *.h)
THELONIOUS_OBJ = $(addprefix $(THELONIOUS_BUILD_DIR)/, $(THELONIOUS_SRC:../%.h=%.o))

TEST_OBJ = $(addprefix $(TEST_BUILD_DIR)/, $(TEST_SRC:.cc=.o))
TEST_DEPS = $(addprefix $(TEST_BUILD_DIR)/, $(TEST_SRC:.cc=.d))
TEST_EXE = test_runner

GMOCK_DIR ?= ../../gmock-1.6.0

# Compiler options
CXX ?= g++
CXXFLAGS = -Werror -Wall -Wno-unused-local-typedefs -g -std=c++11
INC = -I ../ -I $(GMOCK_DIR)/include -I $(GMOCK_DIR)/gtest/include
LIB = -l pthread
GMOCK = $(GMOCK_DIR)/make/gmock.a

vpath thelonious/%.h ../
vpath test/%.cc .

all: $(THELONIOUS_OBJ) $(TEST_EXE)

echo:
	echo $(THELONIOUS_OBJ)

test:
	./$(TEST_EXE)

$(TEST_EXE): $(TEST_OBJ) $(TEST_DEPS)
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_OBJ) $(GMOCK) $(LIB)

$(TEST_BUILD_DIR)/%.o: %.cc
	mkdir -p $(@D)
	$(CXX) $(INC) $(CXXFLAGS) -o $@ -c $<

$(THELONIOUS_BUILD_DIR)/%.o: %.h
	mkdir -p $(@D)
	$(CXX) $(INC) $(CXXFLAGS) -o $@ -c $<

$(TEST_BUILD_DIR)/%.d: %.cc
	mkdir -p $(@D)
	$(CXX) $(INC) $(CXXFLAGS) -MM $< -MF $@

clean:
	rm -f $(TEST_EXE)
	rm -rf $(BUILD_DIR)

ifneq ($(MAKECMDGOALS), clean)
-include $(DEPS)
endif

