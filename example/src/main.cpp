#include <utility>
#define __NO_STD_VECTOR
#include <CL/cl.hpp>

#include <iostream>
#include <fstream>
#include <string>

#include "cl/ContextWrapper.h"
#include "Image.h"
#include "utils.h"

int main(void)
{
	cl_int err;

	grl::ContextWrapper cwrapper;
	grl::Image image(cwrapper, 640, 480, grl::GRL_LITTLE_ENDIAN);

	err = cwrapper.CreateContext();
	if(!CheckErr(err, "ContextWrapper::CreateContext"))
		return EXIT_FAILURE;

	cwrapper.LoadProgram(&err);
	if(!CheckErr(err, "ContextWrapper::LoadProgram"))
		return EXIT_FAILURE;
	
	err = image.BuildBuffer();
	if(!CheckErr(err, "Image::BuildBuffer"))
		return EXIT_FAILURE;

	err = image.BindSimple();
	if(!CheckErr(err, "Image::BindSimple"))
		return EXIT_FAILURE;
	
	/*
	// Using program
	cl::Event event;
	cl::CommandQueue queue(cwrapper.GetContext(), cwrapper.GetDevices()[0], 0, &err);
	if(!CheckErr(err, "CommandQueue::CommandQueue"))
		return EXIT_FAILURE;

	err = queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(CHAR_COUNT + 1), cl::NDRange(1, 1), 0, &event);
	if(!CheckErr(err, "CommandQueue::enqueueNDRangeKernel"))
		return EXIT_FAILURE;

	event.wait();

	err = queue.enqueueReadBuffer(resultBuffer, CL_TRUE, 0, CHAR_COUNT + 1, result);
	if(!CheckErr(err, "CommandQueue::enqueueReadBuffer"))
		return EXIT_FAILURE;

	std::cout << "Result: " << result << std::endl;
	*/

	return EXIT_SUCCESS;
}

