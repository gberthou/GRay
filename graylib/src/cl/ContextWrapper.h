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
		virtual cl_int CreateContext(void *glhRC, void *glhDC);

		// Override this one too	
		virtual cl::Program *LoadProgram(cl_int *err);

		cl::Buffer *CreateBuffer(cl_mem_flags flags, size_t size, void *host_ptr, cl_int *err) const;
		
		cl::Image2DGL *CreateImage2DGL(cl_mem_flags flags, GLenum target, GLint miplevel, GLuint texobj, cl_int *err) const;
		cl_int BindImageSimple(cl::Image2DGL *image);
		
		cl::CommandQueue *CreateQueue(cl_command_queue_properties prop, cl_int *err) const;
		
		// Must not be called before CreateContext
		const cl::Context &GetContext(void) const;
		const cl::vector<cl::Device> &GetDevices(void) const;
		const cl::Kernel &GetKernelSimple(void) const;

	protected:
		cl::vector<cl::Platform> platforms;
		cl::vector<cl::Device> devices;

		cl::Context *context;
		cl::Program *program;

		// Kernels
		cl::Kernel *krSimple;

		bool created;
		bool programLoaded;
};

#endif

