BUILD_DIR = build
TEST_BUILD_DIR = $(BUILD_DIR)/tests
THELONIOUS_BUILD_DIR = $(BUILD_DIR)/thelonious

THELONIOUS_SRC = $(shell find ../thelonious -type f -name "*.h")
THELONIOUS_GCH = $(addprefix $(THELONIOUS_BUILD_DIR)/, $(THELONIOUS_SRC:../%.h=%.h.gch))

TEST_SRC = $(shell find . -type f -name "*.cc")
TEST_OBJ = $(addprefix $(TEST_BUILD_DIR)/, $(TEST_SRC:.cc=.o))
TEST_DEPS = $(addprefix $(TEST_BUILD_DIR)/, $(TEST_SRC:.cc=.d))
TEST_EXE = test_runner

GMOCK_DIR ?= ../../gmock-1.7.0

# Compiler options
CXX ?= g++
CXXFLAGS = -Werror -Wall -Wno-missing-braces -g -std=c++11
INC = -I ../ -I $(GMOCK_DIR)/include -I $(GMOCK_DIR)/gtest/include
LIB = -l pthread
GMOCK = $(GMOCK_DIR)/make/gmock.a

vpath thelonious/%.h ../
vpath test/%.cc .

all: $(THELONIOUS_GCH) $(TEST_EXE)

test: $(TEST_EXE)
	./$(TEST_EXE)

compiletest: $(THELONIOUS_GCH)

$(TEST_EXE): $(TEST_OBJ) $(TEST_DEPS)
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_OBJ) $(GMOCK) $(LIB)

$(TEST_BUILD_DIR)/%.o: %.cc
	mkdir -p $(@D)
	$(CXX) $(INC) $(CXXFLAGS) -o $@ -c $<

$(THELONIOUS_BUILD_DIR)/%.h.gch: %.h
	mkdir -p $(@D)
	$(CXX) $(INC) $(CXXFLAGS) -x c++-header -o $@ $<

$(TEST_BUILD_DIR)/%.d: %.cc
	mkdir -p $(@D)
	$(CXX) $(INC) $(CXXFLAGS) -MM $< -MF $@

clean:
	rm -f $(TEST_EXE)
	rm -rf $(BUILD_DIR)

ifneq ($(MAKECMDGOALS), clean)
-include $(DEPS)
endif

