#include <renderer.h>
#include <glad/glad.h>

Renderer::Renderer()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

Renderer::~Renderer()
{
	// not implmented 
}
