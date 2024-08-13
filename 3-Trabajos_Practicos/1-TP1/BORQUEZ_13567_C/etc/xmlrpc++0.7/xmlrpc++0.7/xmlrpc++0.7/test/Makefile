# makefile written for gnu make
CXX		= g++ 
SRCDIR		= ../src
INCDIR		= ../include
CPPFLAGS	= -I$(INCDIR)
BUILDIR		= ./build
DEBUG		= -g
#OPTIMIZE	= -O2
GCCWARN		= -Wall -Wstrict-prototypes
CXXFLAGS	= $(DEBUG) $(GCCWARN) $(OPTIMIZE) $(CPPFLAGS)

LIB		= ../lib/xmlrpc.a

SYSTEMLIBS	= -lws2_32

LDLIBS		= $(LIB) $(SYSTEMLIBS) 

SOURCES 		= $(wildcard ./*cpp)
TESTS			= $(patsubst ./%.cpp, $(BUILDIR)/%.exe, $(SOURCES))

all:		$(TESTS)

$(TESTS):	$(SOURCES)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDLIBS)

clean:
	rm -f $(TESTS)
