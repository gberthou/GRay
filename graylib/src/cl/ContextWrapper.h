#ifndef CONTEXT_WRAPPER_H
#define CONTEXT_WRAPPER_H

#include <utility>
#define __NO_STD_VECTOR
#include <CL/cl.hpp>

#include <string>

namespace grl
{
	class ContextWrapper;
}

class grl::ContextWrapper
{
	public:
		ContextWrapper();
		virtual ~ContextWrapper();

		// Override this in order to modify behavior
		virtual cl_int CreateContext(void);

		// Override this one too	
		virtual cl::Program *LoadProgram(const std::string &filename);

		cl::Buffer *CreateBuffer(cl_mem_flags flags, size_t size, void *host_ptr, cl_int *err) const;

		// Must not be called before CreateContext
		const cl::Context &GetContext(void) const;
		const cl::vector<cl::Device> &GetDevices(void) const;

	protected:
		cl::vector<cl::Platform> platforms;
		cl::vector<cl::Device> devices;

		cl::Context *context;
		bool created;
		bool programLoaded;
};

#endif

