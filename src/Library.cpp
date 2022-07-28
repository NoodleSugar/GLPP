#include <GLPP/Library.hpp>

#include <GLFW/glfw3.h>

namespace glpp
{

const char* glppInitException::what() const noexcept { return "Failed to initialize GLAD"; }

void Library::initialize() noexcept(false)
{
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw glppInitException();
}

} // namespace glpp
