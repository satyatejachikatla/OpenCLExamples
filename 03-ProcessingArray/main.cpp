#include <CL/cl.hpp>
#include <iostream>
#include <vector>
#include <assert.h>
#include <fstream>
#include <string>
#include <OpenCLHelper.h>

int main() {

	auto program = CreateProgram("./ProcessArray.cl");
	auto context = program.getInfo<CL_PROGRAM_CONTEXT>();
	auto devices = context.getInfo<CL_CONTEXT_DEVICES>();
	auto& device  = devices.front();

	std::vector<int> vec(1024);
	//for(int i=0;i<vec.size();i++) vec[i] = i;

	cl::Buffer inBuf(context,CL_MEM_READ_ONLY | CL_MEM_HOST_NO_ACCESS | CL_MEM_COPY_HOST_PTR, sizeof(int) * vec.size(),vec.data());
	cl::Buffer outBuf(context,CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY , sizeof(int) * vec.size());

	cl_int err;
	cl::Kernel kernel(program,"ProcessArray",&err);
	if (err != CL_SUCCESS) {
		std::cerr << "Failed to init Kernel" <<std::endl;
	}
	kernel.setArg(0,inBuf);
	kernel.setArg(1,outBuf);
	if (err != CL_SUCCESS) {
		std::cerr << "Failed to setArg" <<std::endl;
	}

	cl::CommandQueue queue(context);

	queue.enqueueFillBuffer(inBuf,3 ,sizeof(int) * 10 , sizeof(int)*(vec.size()-10));
	queue.enqueueNDRangeKernel(kernel,cl::NullRange, cl::NDRange(vec.size()));
	queue.enqueueReadBuffer(outBuf,CL_FALSE,0,sizeof(int)*vec.size(),vec.data());

	cl::finish();

	for(int i=0;i<vec.size();i++) std::cout << vec[i] << " ";
	std::cout << std::endl;

	return 0;
}