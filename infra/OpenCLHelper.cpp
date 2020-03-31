#include <CL/cl.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include <OpenCLHelper.h>

cl::Program CreateProgram(const std::string& file) {

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


	std::ifstream programFile(file);
	std::string src((std::istreambuf_iterator<char>(programFile)),
					 std::istreambuf_iterator<char>());

	std::cout << "Source : " << std::endl;
	std::cout << src << std::endl;

	cl::Program::Sources sources(1,std::make_pair(src.c_str() , src.length() + 1));

	cl::Context context(device);
	cl::Program program(context,sources);

	auto err =program.build("-cl-std=CL1.2");
	if (err != CL_SUCCESS) {
		std::cerr << "Program build failed" <<std::endl;
		std::cerr << "Exit code : " << err <<std::endl;
		exit(EXIT_FAILURE);
	}

	return program;
}