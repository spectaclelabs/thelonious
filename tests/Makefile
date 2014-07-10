# Source files
SRC = $(wildcard *.cc)
SRC +=  $(wildcard */*.cc)
EXE = $(SRC:.cc=)

GMOCK_DIR = ../../gmock-1.6.0

# Compiler options
CXX = g++
CXXFLAGS = -Werror -Wall -Wno-unused-local-typedefs -g -std=c++11
INC = -I ../ -I $(GMOCK_DIR)/include -I $(GMOCK_DIR)/gtest/include
LIB = -L $(GMOCK_DIR) -l gmock -l pthread

all: $(EXE) .gitignore

.cc:
	$(CXX) $(INC) $(CXXFLAGS) $< -o $@ $(LIB)

clean:
	rm -f $(EXE)

# Autogenerate .gitignore to ignore executable files
.gitignore:
	@echo $(EXE) | sed 's/ /\n/g' > $@
