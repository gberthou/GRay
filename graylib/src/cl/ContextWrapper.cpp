#include <iostream>
#include <cstdlib>
#include <fstream>

#include "ContextWrapper.h"
#include "utils.h"

using namespace grl;

ContextWrapper::ContextWrapper():
	context(0),
	program(0),
	krSimple(0),
	created(false)
{
}

ContextWrapper::~ContextWrapper()
{
	delete context;
	delete program;
	delete krSimple;
}

cl_int ContextWrapper::CreateContext(void)
{
	const char *CHECK_MESSAGE = "Please check your drivers and hardware";
	if(!created)
	{
		cl_int err;
		cl::Platform::get(&platforms);

		if(!platforms.size())
		{
			std::cerr << "ERROR: OpenCL cannot detect any platform." << std::endl << CHECK_MESSAGE << std::endl;
			return -1;
		}

		// Takes the first platform
		cl_context_properties cprops[3] = {CL_CONTEXT_PLATFORM, (cl_context_properties)(platforms[0])(), 0};
		
		context = new cl::Context(CL_DEVICE_TYPE_ALL, cprops, 0, 0, &err);
		if(!CheckErr(err, "Context::Context"))
		{
			delete context;
			context = 0;
			return err;
		}

		devices = context->getInfo<CL_CONTEXT_DEVICES>();

		if(!devices.size())
		{
			std::cerr << "ERROR: OpenCL cannot detect any device in the selected platform." << std::endl << CHECK_MESSAGE << std::endl;
			delete context;
			context = 0;
			return -1;
		}

		created = true;
	}

	return CL_SUCCESS;
}

cl::Program *ContextWrapper::LoadProgram(cl_int *err)
{
	const std::string FILENAME = "cl/gray.cl"; // TODO: cl code should be embedded
	
	if(created && !programLoaded)
	{
		std::string src;

		// Open file
		std::ifstream srcfile(FILENAME.c_str());
		if(!CheckErr(srcfile.is_open() ? CL_SUCCESS : -1, "Cannot open file cl/gray.cl"))
		{
			*err = -1;	
			return 0;
		}
		
		// Read file
		src.append(std::istreambuf_iterator<char>(srcfile), std::istreambuf_iterator<char>());
		
		// Build sources and program
		cl::Program::Sources sources(1, std::make_pair(src.c_str(), src.size() + 1));
		program = new cl::Program(*context, sources);
		*err = program->build(devices, "");
		if(!CheckErr(*err, "Program::build"))
		{
			delete program;
			program = 0;
		}

		krSimple = new cl::Kernel(*program, "simple", err);
		if(!CheckErr(*err, "Kernel::Kernel") || !krSimple)
		{
			delete program;
			program = 0;
			if(!krSimple)
				*err = -1;
			return 0;
		}

		programLoaded = true;
		return program;
	}
	return 0;
}

cl::Buffer *ContextWrapper::CreateBuffer(cl_mem_flags flags, size_t size, void *host_ptr, cl_int *err) const
{
	if(!context)
	{
		*err = -1;
		return 0;
	}
	return new cl::Buffer(*context, flags, size, host_ptr, err);
}

cl_int ContextWrapper::BindBufferSimple(cl::Buffer *buffer)
{
	if(krSimple && !buffer)
	{
		cl_int err = krSimple->setArg(0, buffer);
		CheckErr(err, "Kernel::setArg(0, ...)");
		return err;
	}
	return -1;
}

const cl::Context &ContextWrapper::GetContext(void) const
{
	return *context;
}

const cl::vector<cl::Device> &ContextWrapper::GetDevices(void) const
{
	return devices;
}

