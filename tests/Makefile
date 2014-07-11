# Source files
SRC =  $(wildcard *.cc)
SRC += $(wildcard constants/*.cc)
SRC += $(wildcard dsl/*.cc)
SRC += $(wildcard dsp/*.cc)
SRC += $(wildcard operators/*.cc)

OBJ = $(SRC:.cc=.o)
DEPS = $(SRC:.cc=.d)
EXE = test_runner

GMOCK_DIR ?= ../../gmock-1.6.0

# Compiler options
CXX ?= g++
CXXFLAGS = -Werror -Wall -Wno-unused-local-typedefs -g -std=c++11
INC = -I ../ -I $(GMOCK_DIR)/include -I $(GMOCK_DIR)/gtest/include
LIB = -l pthread
GMOCK = $(GMOCK_DIR)/make/gmock.a

all: $(EXE)

test:
	./test_runner

$(EXE): $(OBJ) $(DEPS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ) $(GMOCK) $(LIB)

%.o: %.cc
	$(CXX) $(INC) $(CXXFLAGS) -o $@ -c $<

%.d: %.cc
	$(CXX) $(INC) $(CXXFLAGS) -MM $< -MF $@
	
clean:
	rm -f $(EXE) $(OBJ) $(DEPS)

ifneq ($(MAKECMDGOALS), clean)
-include $(DEPS)
endif

