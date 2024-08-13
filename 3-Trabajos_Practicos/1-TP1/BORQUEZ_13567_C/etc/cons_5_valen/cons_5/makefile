# makefile written for gnu make
SRCDIR = ./src
BUILDDIR = ./bin
INCLDIR = ./include/xmlrpc
INCLVAL = ./include/valen
CXX		= g++
CPPFLAGS	= -I$(INCLDIR) -I$(INCLVAL)
DEBUG		= -g
OPTIMIZE	= -O2
GCCWARN		= -Wall
CXXFLAGS	= $(DEBUG) $(GCCWARN) $(OPTIMIZE)

LIB		= ./lib/libXmlRpc.a
SYSTEMLIBS	= -lws2_32

LDLIBS		= $(LIB) $(SYSTEMLIBS)

SOURCES		= $(wildcard $(SRCDIR)/*cpp)
OBJECTS		= $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SOURCES))
EXECUTABLE	= ./bin/Servidor.exe

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@


$(EXECUTABLE):	$(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)


.PHONY: all clean

all:		$(OBJECTS)

clean:
	rm -f $(BUILDDIR)/*.o $(EXE)
