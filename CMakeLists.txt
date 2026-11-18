cmake_minimum_required(VERSION 3.21)

project(taskrunner LANGUAGES CXX)

add_executable(taskrunner
    src/main.cpp
)

target_include_directories(taskrunner PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_compile_features(taskrunner PRIVATE cxx_std_20)
set_target_properties(taskrunner PROPERTIES CXX_EXTENSIONS OFF)

# Keep the example available under examples/ when running from the build directory.
configure_file(examples/sample.tasks examples/sample.tasks COPYONLY)

# Move the supplied headers to include/ and source files to src/.
# Add the source files to the taskrunner target as you develop the project.
