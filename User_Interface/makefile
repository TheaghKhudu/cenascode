SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES: .cpp= .o)
EXEC=iaos
OPTIONS=-g -lm -O0
%.o : %.cpp 
	g++ -c $^ -o $@

$(EXEC) : $(OBJECTS)
	g++  $^ $(OPTIONS) -o $@ 
	
clean :
	rm $(OBJECTS) $(EXEC)
