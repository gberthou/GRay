#include <utility>
#define __NO_STD_VECTOR
#include <CL/cl.hpp>

#include <SDL2/SDL.h>
#include <GL/gl.h>

#include <iostream>
#include <fstream>
#include <string>

#include "cl/ContextWrapper.h"
#include "cl/ImageWrapper.h"
#include "utils.h"

static GLuint createTexture(GLsizei width, GLsizei height)
{
	float *buf = new float[width * height * 3];
	GLuint tex;
	int i;

	for(i = 0; i < width * height * 3; ++i)
		buf[i] = .5f;

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, buf);
	delete [] buf;

	return tex;
}

int main(void)
{
	// Constants
	const GLsizei WIDTH = 640;
	const GLsizei HEIGHT = 480;

	bool done = false;
	
	// SDL-related variables
	SDL_Event event;
	SDL_Window *window;
	SDL_GLContext glcontext;
	
	// GL-related variables
	GLuint texture;
	
	// GRay-related variables
	cl_int err;
	grl::ContextWrapper cwrapper;
	grl::ImageWrapper image(cwrapper, WIDTH, HEIGHT);

	// SDL & GL initialization
	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	window = SDL_CreateWindow("Sample", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	glcontext = SDL_GL_CreateContext(window);
	SDL_GL_SetSwapInterval(1);

	glClearColor(0, 0, 0, 1);

	texture = createTexture(WIDTH, HEIGHT);

	std::cout << texture << std::endl;
	std::cout << GL_TEXTURE_2D << std::endl;
	
	// GRay initialization
	err = cwrapper.CreateContext(window, glcontext);
	if(!CheckErr(err, "ContextWrapper::CreateContext"))
		return EXIT_FAILURE;

	cwrapper.LoadProgram(&err);
	if(!CheckErr(err, "ContextWrapper::LoadProgram"))
		return EXIT_FAILURE;
	
	err = image.BuildTexture(texture);
	if(!CheckErr(err, "Image::BuildBuffer"))
		return EXIT_FAILURE;

	err = image.BindSimple();
	if(!CheckErr(err, "Image::BindSimple"))
		return EXIT_FAILURE;

	// And here begins the program...
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	while(!done)
	{
		while(SDL_PollEvent(&event) && !done)
		{
			if(event.type == SDL_QUIT)
				done = true;
		}
		
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_QUADS);
			glTexCoord2f(0, 1);  glVertex2f(-1, -1);
			glTexCoord2f(1, 1);  glVertex2f(1, -1);
			glTexCoord2f(1, 0);  glVertex2f(1, 1);
			glTexCoord2f(0, 0);  glVertex2f(-1, 1);
		glEnd();	

		SDL_GL_SwapWindow(window);
		SDL_Delay(10);
	}


	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}

