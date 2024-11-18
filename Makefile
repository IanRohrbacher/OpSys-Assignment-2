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
	@echo 'make run 	- Compiles main then outputs main.o'
	@echo 'make clean	- removes all .o files'

###############################################################
# Variables
#
CXX = g++
CXXFLAGS = -std=c++11
TARGETS = main

#####################################################
# Used when running 'run' command
#
$(TARGETS): $(TARGETS).o
	$(CXX) $(CXXFLAGS) -o $(TARGETS) $(TARGETS).o

$(TARGETS).o: $(TARGETS).cpp
	$(CXX) $(CXXFLAGS) -c $(TARGETS).cpp


#####################################################
# Compiles and outputs main
#
run: $(TARGETS)
	./$(TARGETS)& 

#####################################################
# Removes all .o files
#
clean:
	rm -f *.o $(TARGETS)

#####################################################
