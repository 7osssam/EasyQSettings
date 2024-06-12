# CMakeLists.txt in the root directory

cmake_minimum_required(VERSION 3.14)

project(EasyQSettingsDemo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the include directory for the EasyQSettings library
add_subdirectory(include)

# Add the demo directory
add_subdirectory(demo)
