CXX ?= g++ -std=c++11 
AR  ?= ar
MAKE ?= make

LIBS := 	-L/opt/intel/system_studio_2020/opencl-sdk/lib64/ \
			-lOpenCL

CXXFLAGS := -I/opt/intel/system_studio_2020/opencl-sdk/include/ \
			-I. \
			-Wl,-no-as-needed

BUILT_LIBS := \


OBJS := *.o


all:

	$(MAKE) app

app:
	$(CXX) $(CXXFLAGS) $(LIBS)  -c main.cpp 
	$(CXX) $(CXXFLAGS) $(LIBS) $(OBJS)  $(BUILT_LIBS) -o run

clean:
	rm -f run
	rm -f *.o
