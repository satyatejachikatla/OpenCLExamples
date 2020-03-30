#include <CL/cl.hpp>
#include <iostream>
#include <vector>
#include <assert.h>
#include <fstream>
#include <string>

int main() {
	std::vector<cl::Platform> platforms;
	cl::Platform::get(&platforms);

	auto platform = platforms.front();

	std::vector<cl::Device> devices;
	platform.getDevices(CL_DEVICE_TYPE_GPU,&devices);

	auto device = devices.front();
	auto name    = device.getInfo<CL_DEVICE_NAME>();
	auto vendor  = device.getInfo<CL_DEVICE_VENDOR>();
	auto version = device.getInfo<CL_DRIVER_VERSION>();

	std::cout << "Name    :"<< name    << std::endl;
	std::cout << "Vendor  :"<< vendor  << std::endl;
	std::cout << "Version :"<< version << std::endl;

	std::ifstream helloWorldFile("./HelloWorld.cl");
	std::string src((std::istreambuf_iterator<char>(helloWorldFile)),
					 std::istreambuf_iterator<char>());

	std::cout << "Source Cl code:" << std::endl;
	std::cout << src << std::endl;
	
	cl::Program::Sources sources(1,std::make_pair(src.c_str() , src.length() + 1));

	cl::Context context(device);
	cl::Program program(context,sources);

	auto err =program.build("-cl-std=CL1.2");
	if (err != CL_SUCCESS) {
		std::cerr << "Program build failed" <<std::endl;
	}

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