#include <utility>
#define __NO_STD_VECTOR
#include <CL/cl.hpp>

#include <iostream>
#include <fstream>
#include <string>

#include "cl/ContextWrapper.h"
#include "utils.h"

int main(void)
{
	const unsigned int CHAR_COUNT = 16;
	char *result;
	cl::Program *program;

	cl_int err;

	grl::ContextWrapper cwrapper;

	err = cwrapper.CreateContext();
	if(!CheckErr(err, "ContextWrapper::CreateContext"))
		return EXIT_FAILURE;

	result = new char[CHAR_COUNT + 1];

	cl::Buffer resultBuffer(cwrapper.GetContext(), CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, CHAR_COUNT + 1, result, &err);
	if(!CheckErr(err, "Buffer::Buffer"))
		return EXIT_FAILURE;

	program = cwrapper.LoadProgram("cl/sample.cl");

	cl::Kernel kernel(*program, "hello", &err);
	if(!CheckErr(err, "Kernel::Kernel"))
		return EXIT_FAILURE;

	err = kernel.setArg(0, resultBuffer);
	if(!CheckErr(err, "Kernel::setArg(0, ...)"))
		return EXIT_FAILURE;

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

	free(result);
	delete program;

	return EXIT_SUCCESS;
}

