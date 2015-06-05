#include "Image.h"

using namespace grl;

Image::Image(ContextWrapper &wrapper, unsigned int w, unsigned int h, Endianness endian):
	cwrapper(wrapper),
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
	delete [] data;
}

cl_int Image::BuildBuffer(void)
{
	if(!built)
	{
		cl_int err;
		data = new unsigned int[size];
		if(!data)
			return -1;

		buffer = cwrapper.CreateBuffer(CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, size, data, &err);
		if(err != CL_SUCCESS)
		{
			delete [] data;
			data = 0;
			return err;
		}

		built = true;
	}

	return CL_SUCCESS;
}

cl_int Image::BindSimple(void)
{
	return cwrapper.BindBufferSimple(buffer);
}

