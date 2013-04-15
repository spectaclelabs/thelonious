# Source files
SRC =  $(wildcard *.cc)
EXE = $(SRC:.cc=)

# Compiler options
CXX = g++
CXXFLAGS = -Werror -Wall -g -std=c++11 -Wno-parentheses
INC = -I ../
LIB = -l rtaudio -l pthread

all: $(EXE) .gitignore

.cc:
	$(CXX) $(INC) $(CXXFLAGS) $< -o $@ $(LIB)

clean:
	rm -f $(EXE)

# Autogenerate .gitignore to ignore executable files
.gitignore:
	@echo $(EXE) | sed 's/ /\n/g' > $@
