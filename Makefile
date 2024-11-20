###############################################################
# Fall 2024 OPERATING SYSTEMS (CS-33211-001)
# Programming Assignment #2
# Make file for Programming Assignment #2
#
# Ian Rohrbacher
# Fall 2024
#
###############################################################
msg:
	@echo 'Targets are:'
	@echo 'ARGS= make run 	- Compiles main with inputed ARGS, text file name within the input folder, then outputs main.o'
	@echo 'make runDefult 	- Compiles main with the defult text files found within the input folder then outputs main.o'
	@echo 'make clean		- removes all .o files'

###############################################################
# Variables
#
CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGETS = main
SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
DEFULTARGS = input1.txt input2.txt input3.txt input4.txt

#####################################################
# Used when running 'run' command
#
all: $(TARGETS)

$(TARGETS): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<


#####################################################
# Compiles and outputs main
#
runDefult: $(TARGETS)
	./$(TARGETS) $(DEFULTARGS) 

#####################################################
# Compiles and outputs main
#
run: $(TARGETS)
	./$(TARGETS) $(ARGS) 

#####################################################
# Removes all .o files
#
clean:
	rm -f $(OBJECTS) $(TARGET)

#####################################################
