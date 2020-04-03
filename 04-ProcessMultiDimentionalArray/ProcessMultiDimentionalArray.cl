__kernel void ProcessMultiDimentionalArray(__global int* data) {
	size_t idx = get_global_id(1)*get_global_size(0) + get_global_id(0);
	data[idx] = data[idx] * 2;
}