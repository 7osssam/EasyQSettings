# include/CMakeLists.txt

# Define the library target
add_library(EasyQSettings_lib INTERFACE)

# Specify the include directory for the library
target_include_directories(EasyQSettings_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
