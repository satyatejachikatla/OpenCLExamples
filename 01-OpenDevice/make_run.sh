#!/bin/bash

make all
export LD_RUN_PATH="/opt/intel/system_studio_2020/opencl-sdk/lib64"
export LD_LIBRARY_PATH="/opt/intel/system_studio_2020/opencl-sdk/lib64"
ldd ./run | grep OpenCL
./run
make clean