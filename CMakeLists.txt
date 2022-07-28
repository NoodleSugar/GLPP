cmake_minimum_required(VERSION 3.22.0)
project(
	GLPP
		VERSION 0.0.1
		DESCRIPTION "OpenGL Wrapper for C++"
		LANGUAGES CXX
)

add_library(${PROJECT_NAME} STATIC)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		glad
)

target_sources(${PROJECT_NAME}
	PRIVATE
		src/Library.cpp
		src/Program.cpp
		src/VertexArray.cpp
		src/TextureFactory.cpp
)