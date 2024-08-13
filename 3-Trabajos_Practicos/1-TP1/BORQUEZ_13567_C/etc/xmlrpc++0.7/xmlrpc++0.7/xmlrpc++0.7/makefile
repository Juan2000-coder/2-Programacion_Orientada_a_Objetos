# makefile written for gnu make
CXX		= g++
SRCDIR	= ./src
INCDIR = ./include
BINDIR = ./bin
LIBDIR = ./lib
CPPFLAGS	= -I$(INCDIR)
DEBUG		= -g
OPTIMIZE	= -O2
GCCWARN		= -Wall -Wstrict-prototypes
CXXFLAGS	= $(DEBUG) $(GCCWARN) $(OPTIMIZE) $(INCLUDES)

LIB		= $(LIBDIR)/xmlrpc.a

SYSTEMLIBS	= -lws2_32
LDLIBS		= $(LIB) $(SYSTEMLIBS)

SOURCES		= $(wildcard $(SRCDIR)/*cpp)
OBJECTS		= $(patsubst $(SRCDIR)/%.cpp, $(BINDIR)/%.o, $(SOURCES))

all:		tests $(LIB) 

$(LIB):		$(OBJECTS)
	$(AR) $(ARFLAGS) $(LIB) $(OBJECTS)

$(BINDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@
	
tests:	$(LIB)
	cd test && $(MAKE)

doc doxygen:
	cd src && doxygen Doxyfile

clean:
	rm -f $(BINDIR)/*.o
	rm -f $(SRC)/*~
	rm -f $(LIBDIR)/*.a
	cd test && $(MAKE) clean

