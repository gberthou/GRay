#pragma OPENCL EXTENSION cl_khr_byte_addressable_store : enable


__kernel void simple(__global unsigned int *pixels)
{
   size_t tid = get_global_id(0);
   pixels[tid] = 0xFFA0A0A0;
}

