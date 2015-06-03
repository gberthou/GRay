#ifndef IMAGE_H
#define IMAGE_H

#include <utility>
#include <CL/cl.hpp>

#include "cl/ContextWrapper.h"

namespace grl
{
	class Image;
	enum Endianness
	{
		GRL_LITTLE_ENDIAN,
		GRL_BIG_ENDIAN
	};
}

class grl::Image
{

	public:
		Image(unsigned int width, unsigned int height, grl::Endianness endianness);
		virtual ~Image();

		// You might want to override this
		virtual cl_int BuildBuffer(const ContextWrapper &wrapper);

	protected:
		unsigned int width;
		unsigned int height;
		unsigned int depth;
		size_t size;

		grl::Endianness endianness;
		cl::Buffer *buffer;
		unsigned int *data;
		bool built;	
};

#endif

