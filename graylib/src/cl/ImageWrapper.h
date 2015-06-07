#ifndef IMAGEWRAPPER_H
#define IMAGEWRAPPER_H

#include <utility>
#include <CL/cl.hpp>

#include "ContextWrapper.h"

namespace grl
{
	class ImageWrapper;
}

class grl::ImageWrapper
{

	public:
		ImageWrapper(ContextWrapper &cwrapper, unsigned int width, unsigned int height);
		virtual ~ImageWrapper();

		// You might want to override this
		virtual cl_int BuildTexture(GLuint texture);
		cl_int BindSimple(void);
		cl_int Compute(bool blocking);
		cl_int WaitForResult(void);

	protected:
		ContextWrapper &cwrapper;
		unsigned int width;
		unsigned int height;

		cl::Image2DGL *image;
		cl::CommandQueue *queue;
		cl::Event event;

		bool built;	
};

#endif

