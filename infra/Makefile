CXX ?= g++
AR  ?= ar
MAKE ?= make

LIBS := -lOpenCL

CXXFLAGS := -I. \
			-Wl,-no-as-needed

BUILT_LIBS := \

all:

	$(CXX) $(CXXFLAGS) -c *.cpp

clean:
	rm -f *.o
	rm -f *.a
