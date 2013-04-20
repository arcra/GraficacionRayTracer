CC=g++-4.4
CFLAGS=-c -Wall -g `pkg-config --cflags --libs gtk+-2.0`
#Si se usan cosas del estándar C++11
#CFLAGS=-c -Wall -g `pkg-config --cflags --libs gtk+-2.0` -std=c++0x
LDFLAGS=-fpermissive `pkg-config --cflags --libs gtk+-2.0`

HEADERSDIR= headers
SOURCESDIR= src
BINDIR= bin

EXCLUDED=ISurface.cpp

INCLUDESDIR=$(HEADERSDIR)/

HEADERS= $(wildcard $(HEADERSDIR)/*.h)
SOURCES= $(filter-out $(addprefix $(SOURCESDIR)/,$(EXCLUDED)),$(wildcard $(SOURCESDIR)/*.cpp))

OBJECTS = $(patsubst $(SOURCESDIR)/%.cpp, $(BINDIR)/%.o, $(SOURCES))
EXECUTABLE=RayTracer

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(BINDIR)/$@

.cpp.o: $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@ 

$(OBJECTS): $(BINDIR)/%.o : $(SOURCESDIR)/%.cpp
	$(CC) $(CFLAGS) -I$(INCLUDESDIR) $< -o $@

clean:
	rm -f $(BINDIR)/*
