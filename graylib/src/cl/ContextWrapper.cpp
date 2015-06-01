#include <iostream>
#include <cstdlib>
#include <fstream>

#include "ContextWrapper.h"
#include "utils.h"

ContextWrapper::ContextWrapper():
	context(0),
	created(false)
{
}

ContextWrapper::~ContextWrapper()
{
	delete context;
}

void ContextWrapper::CreateContext(void)
{
	const char *CHECK_MESSAGE = "Please check your drivers and hardware";
	if(!created)
	{
		cl_int err;
		cl::Platform::get(&platforms);

		if(!platforms.size())
		{
			std::cerr << "ERROR: OpenCL cannot detect any platform." << std::endl << CHECK_MESSAGE << std::endl;
			exit(0);
		}

		// Takes the first platform
		cl_context_properties cprops[3] = {CL_CONTEXT_PLATFORM, (cl_context_properties)(platforms[0])(), 0};
		
		context = new cl::Context(CL_DEVICE_TYPE_ALL, cprops, 0, 0, &err);
		checkErr(err, "Context::Context");

		devices = context->getInfo<CL_CONTEXT_DEVICES>();

		if(!devices.size())
		{
			std::cerr << "ERROR: OpenCL cannot detect any device in the selected platform." << std::endl << CHECK_MESSAGE << std::endl;
			exit(0);
		}

		created = true;
	}
}

cl::Program *ContextWrapper::LoadProgram(const std::string &filename)
{
	if(created)
	{
		std::string src;
		cl::Program *program;
		cl_int err;

		// Open file
		std::ifstream srcfile(filename.c_str());
		checkErr(srcfile.is_open() ? CL_SUCCESS : -1, "Cannot open file cl/sample.cl");
		
		// Read file
		src.append(std::istreambuf_iterator<char>(srcfile), std::istreambuf_iterator<char>());
		
		// Build sources and program
		cl::Program::Sources sources(1, std::make_pair(src.c_str(), src.size() + 1));
		program = new cl::Program(*context, sources);
		err = program->build(devices, "");
		checkErr(err, "Program::build");
		return program;
	}
	return 0;
}

const cl::Context &ContextWrapper::GetContext(void) const
{
	return *context;
}

const cl::vector<cl::Device> &ContextWrapper::GetDevices(void) const
{
	return devices;
}

