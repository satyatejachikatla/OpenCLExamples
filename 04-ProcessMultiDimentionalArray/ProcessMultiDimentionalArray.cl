__kernel void ProcessMultiDimentionalArray(__global const int* data) {
	size_t idx = get_global_id(1)*get_global_size(1) + get_global_id(0);
	data[idx] = data[idx] * 2;
}