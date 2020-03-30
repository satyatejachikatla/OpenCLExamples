CXX ?= g++
AR  ?= ar
MAKE ?= make

LIBS := -lOpenCL

CXXFLAGS := -I. \
			-I../infra \
			-Wl,-no-as-needed

BUILT_LIBS := \


OBJS := *.o ../infra/*.o


all:
	$(MAKE) -C ../infra all
	$(MAKE) app

app:
	$(CXX) $(CXXFLAGS) -c main.cpp 
	$(CXX) $(OBJS) $(LIBS) $(BUILT_LIBS) -o run

clean:
	rm -f run
	rm -f *.o

	$(MAKE) -C ../infra clean
