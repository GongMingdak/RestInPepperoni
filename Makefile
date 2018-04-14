FLAGS = -Wall
SOURCES = createFile.cpp
OBJECTS = createFile.o
EXEBIN = createFile

all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS)
	g++ -o $(EXEBIN) $(OBJECTS)

$(OBJECTS) : $(SOURCES)
	g++ -c $(FLAGS) $(SOURCES)

clean :
	rm $(EXEBIN) $(OBJECTS)
