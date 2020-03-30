#include <CL/cl.hpp>
#include <iostream>
#include <vector>
#include <assert.h>
#include <fstream>
#include <string>
#include <OpenCLHelper.h>

int main() {

	auto program = CreateProgram("./HelloWorld.cl");
	auto context = program.getInfo<CL_PROGRAM_CONTEXT>();
	auto devices = context.getInfo<CL_CONTEXT_DEVICES>();
	auto& device  = devices.front();

	cl_int err;

	char buf[16];
	cl::Buffer memBuf(context,CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY, sizeof(buf));
	cl::Kernel kernel(program,"HelloWorld",&err);
	if (err != CL_SUCCESS) {
		std::cerr << "Failed to init Kernel" <<std::endl;
	}
	kernel.setArg(0,memBuf);
	if (err != CL_SUCCESS) {
		std::cerr << "Failed to setArg" <<std::endl;
	}

	cl::CommandQueue queue(context);
	queue.enqueueTask(kernel);
	queue.enqueueReadBuffer(memBuf,CL_TRUE,0,sizeof(buf),buf);
	if (err != CL_SUCCESS) {
		std::cerr << "Failed to run" <<std::endl;
	}

	std::cout << "Buffer from kernel" << std::endl;
	std::cout << buf << std::endl;

	return 0;
}