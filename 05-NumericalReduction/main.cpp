#include <CL/cl.hpp>
#include <iostream>
#include <vector>
#include <assert.h>
#include <fstream>
#include <string>
#include <array>
#include <OpenCLHelper.h>

int main() {

	auto program = CreateProgram("./NumericalReduction.cl");
	auto context = program.getInfo<CL_PROGRAM_CONTEXT>();
	auto devices = context.getInfo<CL_CONTEXT_DEVICES>();
	auto& device  = devices.front();

	std::vector<int> vec(1024);  // 256 for my gpu, will match with workGorupSize or be more, try changing it to > 256
	for(int i=0;i<vec.size();i++) vec[i] =i; 

	cl_int err;
	cl::Kernel kernel(program,"NumericalReduction",&err);
	if (err != CL_SUCCESS) {
		std::cerr << "Failed to init Kernel" <<std::endl;
	}

	auto workGroupSize = kernel.getWorkGroupInfo<CL_KERNEL_WORK_GROUP_SIZE>(device);
	auto numWorkGroups  = vec.size() / workGroupSize;

	std::cout << "Work Group Size is :" <<  workGroupSize << std::endl;

	cl::Buffer buf(context,CL_MEM_READ_ONLY | CL_MEM_HOST_NO_ACCESS | CL_MEM_COPY_HOST_PTR, sizeof(int) * vec.size(), vec.data());
	cl::Buffer outBuf(context,CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY , sizeof(int) * numWorkGroups);

	kernel.setArg(0,buf);
	kernel.setArg(1,sizeof(int) * workGroupSize,nullptr);
	kernel.setArg(2,outBuf);
	if (err != CL_SUCCESS) {
		std::cerr << "Failed to setArg" <<std::endl;
	}

	std::vector<int> outVec(numWorkGroups);

	cl::CommandQueue queue(context);
	queue.enqueueNDRangeKernel(kernel,cl::NullRange, cl::NDRange(vec.size()),cl::NDRange(workGroupSize));
	queue.enqueueReadBuffer(outBuf,CL_TRUE,0,sizeof(int)*outVec.size(),outVec.data());

	// change the logic of output based on the vec size
	for(int i=0 ;i < outVec.size() ; i++) {
		if(outVec[i] == 0)
			break;
		std::cout << "Sum at "<< i <<" :" << outVec[i] << std::endl;
	}

	return 0;
}