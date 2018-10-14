SOURCES=$(wildcard *.cpp)
HEADERS=$(wildcard *.hpp)
OBJECTS=$(SOURCES: .cpp= .o)
EXEC=iaos
OPTIONS=-g -lm -O0
%.o : %.cpp 
	g++ -c $^ -o $@

$(EXEC) : $(OBJECTS) $(HEADERS)
	g++  $^ $(OPTIONS) -o $@ 
	
clean :
	rm $(OBJECTS) $(EXEC)
