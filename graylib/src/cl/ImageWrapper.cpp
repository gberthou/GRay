#include <iostream>

#include "ImageWrapper.h"
#include "../utils.h"

using namespace grl;

ImageWrapper::ImageWrapper(ContextWrapper &wrapper, unsigned int w, unsigned int h):
	cwrapper(wrapper),
	width(w),
	height(h),
	image(0),
	queue(0),
	built(false)
{
}

ImageWrapper::~ImageWrapper()
{
	delete image;
	delete queue;
}

cl_int ImageWrapper::BuildTexture(GLuint texture)
{
	if(!built)
	{
		cl_int err;

		image = cwrapper.CreateImage2DGL(CL_MEM_READ_WRITE, GL_TEXTURE_2D, 0, texture, &err);
		
		if(!CheckErr(err, "ImageWrapper::BuildTexture"))
		{
			return err;
		}

		built = true;
	}

	return CL_SUCCESS;
}

cl_int ImageWrapper::BindSimple(void)
{
	return cwrapper.BindImageSimple(image);
}

cl_int ImageWrapper::Compute(bool blocking)
{
	if(built)
	{
		cl_int err;
		queue = cwrapper.CreateQueue(0, &err);
		if(!CheckErr(err, "ImageWrapper::Compute"))
			return err;

		if(queue)
			delete queue;
		err = queue->enqueueNDRangeKernel(cwrapper.GetKernelSimple(), cl::NullRange, cl::NDRange(width * height), cl::NDRange(1, 1), 0, &event);
		if(!CheckErr(err, "CommandQueue::enqueueNDRangeKernel"))
			return err;

		if(blocking)
			return WaitForResult();

		return CL_SUCCESS;
	}
	
	std::cerr << "The image buffer must be built before the image can be computed" << std::endl;
	return -1;
}

cl_int ImageWrapper::WaitForResult(void)
{
	if(built && queue)
	{
		event.wait();
		
		delete queue;
		queue = 0;
		return CL_SUCCESS;
	}

	std::cerr << "The image buffer must be built" << std::endl;
	return -1;
}

