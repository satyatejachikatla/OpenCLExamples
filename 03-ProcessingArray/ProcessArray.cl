__kernel void ProcessArray(__global const int* data, __global int* outData) {
	int idx = get_global_id(0);
	outData[idx] = data[idx] * 2;
}