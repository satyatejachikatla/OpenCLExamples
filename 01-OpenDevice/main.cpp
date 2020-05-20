#define CL_TARGET_OPENCL_VERSION 120

#include <CL/cl.hpp>
#include <iostream>
#include <vector>
#include <assert.h>



int main() {
	std::vector<cl::Platform> platforms;
	cl::Platform::get(&platforms);
	assert(platforms.size()>0);
	std::cout << "Num platforms : " << platforms.size() << std::endl;

	for(auto platform : platforms){
		std::vector<cl::Device> devices;
		platform.getDevices(CL_DEVICE_TYPE_ALL,&devices);

		std::cout << "Num Devices : " << devices.size() << std::endl;

		std::cout << "Devices are :" << std::endl;
		for(auto device : devices) {
			auto name    = device.getInfo<CL_DEVICE_NAME>();
			auto vendor  = device.getInfo<CL_DEVICE_VENDOR>();
			auto version = device.getInfo<CL_DRIVER_VERSION>();

			std::cout << "Name    :"<< name    << std::endl;
			std::cout << "Vendor  :"<< vendor  << std::endl;
			std::cout << "Version :"<< version << std::endl;
		}
	}
}