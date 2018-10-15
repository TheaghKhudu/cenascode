# Makefile to compile and run test programs

CXX = g++
CXXFLAGS = -W
CC = gcc
CCFLAGS = -W
LFLAG = -lm
RM = rm -f

# LBRS = 
# SRCS = 
# OBJS = 
#INCLUDES = 

test_iaos : test_iaos.o
	$(CXX) $(CXXFLAGS) $^ -o $@

test_expr : expression_maker.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $(LFLAGS) $^ -o $@

clean:
	$(RM)
