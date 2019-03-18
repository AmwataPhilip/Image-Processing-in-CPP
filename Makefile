CC=g++
CFLAG= -std=c++11
TARGETS= volimage
OBJECTS= volimage.o driver.o
SOURCES= volimage.cpp driver.cpp
RESULTS= *.raw *.dat

$(TARGETS): $(OBJECTS)
	$(CC) $(CFLAG) $(OBJECTS) -o $(TARGETS)

$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAG) $(SOURCES) -c

clean:
	rm $(OBJECTS)
	rm $(TARGETS)
	rm $(RESULTS)
run:
	./$(TARGETS) MRI