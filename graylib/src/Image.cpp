#include "Image.h"

using namespace grl;

Image::Image(unsigned int w, unsigned int h, Endianness endian):
	width(w),
	height(h),
	depth(32), // TODO: Change this
	endianness(endian),
	buffer(0),
	data(0),
	built(false)
{
	size = width * height; // TODO: Change this
}

Image::~Image()
{
	delete buffer;
	delete data;
}

cl_int Image::BuildBuffer(const ContextWrapper &wrapper)
{
	if(!built)
	{
		cl_int err;
		buffer = wrapper.CreateBuffer(CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, size, data, &err);
		if(err != CL_SUCCESS)
			return err;

		data = new unsigned int[size];
		if(!data)
			return -1;

		built = true;
	}

	return CL_SUCCESS;
}

