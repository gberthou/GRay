#include <utility>
#define __NO_STD_VECTOR
#include <CL/cl.hpp>

#include <iostream>
#include <cstdlib>

#include "utils.h"

void checkErr(cl_int code, const char *name)
{
	if(code != CL_SUCCESS)
	{
		std::cerr << "Error (" << code << "): " << name << std::endl;
		exit(EXIT_FAILURE);
	}
}

