#include <CL/cl.hpp>
#include <iostream>
#include <vector>
#include <assert.h>
#include <fstream>
#include <string>
#include <array>
#include <OpenCLHelper.h>

int main() {

	auto program = CreateProgram("./ProcessMultiDimentionalArray.cl");
	auto context = program.getInfo<CL_PROGRAM_CONTEXT>();
	auto devices = context.getInfo<CL_CONTEXT_DEVICES>();
	auto& device  = devices.front();

	const int numRows = 3;
	const int numCols = 2;
	const int count = numRows * numCols;
	std::array<std::array<int,numCols>,numRows> arr= {{{1,1},{2,2},{3,3}}};

	cl::Buffer buf(context,CL_MEM_READ_WRITE | CL_MEM_HOST_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int) * count, arr.data());

	cl_int err;
	cl::Kernel kernel(program,"ProcessMultiDimentionalArray",&err);
	if (err != CL_SUCCESS) {
		std::cerr << "Failed to init Kernel" <<std::endl;
	}
	kernel.setArg(0,buf);
	if (err != CL_SUCCESS) {
		std::cerr << "Failed to setArg" <<std::endl;
	}

	cl::CommandQueue queue(context);
	queue.enqueueNDRangeKernel(kernel,cl::NullRange, cl::NDRange(numCols,numRows));
	queue.enqueueReadBuffer(buf,CL_TRUE,0,sizeof(int)*count,arr.data());

	for(int i=0;i<numRows;i++) {
		for(int j=0;j<numCols;j++) std::cout << arr[i][j] << " ";
		std::cout << std::endl;
	}

	return 0;
}