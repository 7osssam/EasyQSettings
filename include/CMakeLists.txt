# include/CMakeLists.txt

# Define the library target
add_library(EasyQSettings INTERFACE)

# Specify the include directory for the library
target_include_directories(EasyQSettings INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
