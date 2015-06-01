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

	ContextWrapper cwrapper;

	cwrapper.CreateContext();

	result = new char[CHAR_COUNT + 1];

	cl::Buffer resultBuffer(cwrapper.GetContext(), CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, CHAR_COUNT + 1, result, &err);
	checkErr(err, "Buffer::Buffer");

	program = cwrapper.LoadProgram("cl/sample.cl");

	cl::Kernel kernel(*program, "hello", &err);
	checkErr(err, "Kernel::Kernel");

	err = kernel.setArg(0, resultBuffer);
	checkErr(err, "Kernel::setArg(0, ...)");

	// Using program
	cl::Event event;
	cl::CommandQueue queue(cwrapper.GetContext(), cwrapper.GetDevices()[0], 0, &err);
	checkErr(err, "CommandQueue::CommandQueue");

	err = queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(CHAR_COUNT + 1), cl::NDRange(1, 1), 0, &event);
	checkErr(err, "CommandQueue::enqueueNDRangeKernel");

	event.wait();

	err = queue.enqueueReadBuffer(resultBuffer, CL_TRUE, 0, CHAR_COUNT + 1, result);
	checkErr(err, "CommandQueue::enqueueReadBuffer");

	std::cout << "Result: " << result << std::endl;

	free(result);
	delete program;

	return 0;
}

