#pragma OPENCL EXTENSION cl_khr_byte_addressable_store : enable


__kernel void simple(__global image2d_t image)
{
   size_t tid = get_global_id(0);
}

