#include "Image.h"

using namespace grl;

Image::Image(unsigned int w, unsigned int h, Endianness endian):
	width(w),
	height(h),
	depth(32), // TODO: Change this
	endianness(endian),
	buffer(0),
	data(0)
{
	size = width * height; // TODO: Change this
}

Image::~Image()
{
	delete buffer;
}

cl_int Image::BuildBuffer(const ContextWrapper &wrapper)
{
	cl_int err;
	buffer = wrapper.CreateBuffer(CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, size, data, &err);
	return err;
}

