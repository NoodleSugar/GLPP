#pragma once

#include <glad/glad.h>

#include <exception>

namespace glpp
{

class glppInitException : public std::exception
{
public:
	glppInitException()			  = default;
	~glppInitException() noexcept = default;

	const char* what() const noexcept override;
};

namespace Library
{

void initialize() noexcept(false);

}; // namespace Library

} // namespace glpp