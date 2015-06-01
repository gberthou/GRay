#ifndef CONTEXT_WRAPPER_H
#define CONTEXT_WRAPPER_H

#include <utility>
#define __NO_STD_VECTOR
#include <CL/cl.hpp>

#include <string>

class ContextWrapper
{
	public:
		ContextWrapper();
		virtual ~ContextWrapper();

		// Override this in order to modify behavior
		virtual void CreateContext(void);

		// Override this one too	
		cl::Program *LoadProgram(const std::string &filename);

		// Must not be called before CreateContext
		const cl::Context &GetContext(void) const;
		const cl::vector<cl::Device> &GetDevices(void) const;

	protected:
		cl::vector<cl::Platform> platforms;
		cl::vector<cl::Device> devices;

		cl::Context *context;
		bool created;
};

#endif

