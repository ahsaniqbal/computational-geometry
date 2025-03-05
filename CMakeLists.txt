cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

cmake_policy(SET CMP0072 NEW) # Prefer modern GLVND over legacy OpenGL
set(OpenGL_GL_PREFERENCE "GLVND") # Explicitly set preference

# Set the project name
project(Geometry)

# Add debug flags
set(CMAKE_BUILD_TYPE Debug)   # Force Debug mode
set(CMAKE_CXX_FLAGS_DEBUG "-g")  # Ensure debug symbols are included

# Add the 'src' directory to the list of source files
file(GLOB SOURCES "src/*.cpp")

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)  # Find GLEW
find_package(glfw3 REQUIRED)  # Find GLFW

# Create the executable from the source files
add_executable(Geometry ${SOURCES})
# Add the 'headers' directory to the list of include directories
target_include_directories(Geometry PUBLIC
    ${CMAKE_SOURCE_DIR}/includes
    ${CMAKE_SOURCE_DIR}/includes/algorithms)
target_link_libraries(Geometry OpenGL::GL GLEW::GLEW glfw)
