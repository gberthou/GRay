#pragma OPENCL EXTENSION cl_khr_byte_addressable_store : enable
__constant char hw[] = "Hej pa dig!";
__kernel void hello(__global char * out)
{
   size_t tid = get_global_id(0);
   out[tid] = hw[tid];
}
