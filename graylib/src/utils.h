#ifndef UTILS_H
#define UTILS_H
#include <CL/cl.hpp>

#define __NO_STD_VECTOR

// CheckErr:
//   Returns true if the given code is CL_CORRECT
//   Returns false otherwise
bool CheckErr(cl_int code, const char *name);

#endif

