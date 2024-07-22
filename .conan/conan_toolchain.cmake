

# Conan automatically generated toolchain file
# DO NOT EDIT MANUALLY, it will be overwritten

# Avoid including toolchain file several times (bad if appending to variables like
#   CMAKE_CXX_FLAGS. See https://github.com/android/ndk/issues/323
include_guard()

message(STATUS "Using Conan toolchain: ${CMAKE_CURRENT_LIST_FILE}")

if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeToolchain' generator only works with CMake >= 3.15")
endif()










string(APPEND CONAN_CXX_FLAGS " -m64")
string(APPEND CONAN_C_FLAGS " -m64")
string(APPEND CONAN_SHARED_LINKER_FLAGS " -m64")
string(APPEND CONAN_EXE_LINKER_FLAGS " -m64")

add_compile_definitions(_GLIBCXX_USE_CXX11_ABI=0)


# Extra c, cxx, linkflags and defines


if(DEFINED CONAN_CXX_FLAGS)
  string(APPEND CMAKE_CXX_FLAGS_INIT " ${CONAN_CXX_FLAGS}")
endif()
if(DEFINED CONAN_C_FLAGS)
  string(APPEND CMAKE_C_FLAGS_INIT " ${CONAN_C_FLAGS}")
endif()
if(DEFINED CONAN_SHARED_LINKER_FLAGS)
  string(APPEND CMAKE_SHARED_LINKER_FLAGS_INIT " ${CONAN_SHARED_LINKER_FLAGS}")
endif()
if(DEFINED CONAN_EXE_LINKER_FLAGS)
  string(APPEND CMAKE_EXE_LINKER_FLAGS_INIT " ${CONAN_EXE_LINKER_FLAGS}")
endif()

get_property( _CMAKE_IN_TRY_COMPILE GLOBAL PROPERTY IN_TRY_COMPILE )
if(_CMAKE_IN_TRY_COMPILE)
    message(STATUS "Running toolchain IN_TRY_COMPILE")
    return()
endif()

set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)

# Definition of CMAKE_MODULE_PATH
# Explicitly defined "builddirs" of "host" dependencies
list(PREPEND CMAKE_MODULE_PATH "/root/.conan/data/openssl/3.2.2/_/_/package/304480252b01879c8641f79a653b593b8f26cf9f/lib/cmake")
# The root (which is the default builddirs) path of dependencies in the host context
list(PREPEND CMAKE_MODULE_PATH "/root/.conan/data/zlib/1.3.1/_/_/package/dfbe50feef7f3c6223a476cd5aeadb687084a646/")
# the generators folder (where conan generates files, like this toolchain)
list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

# Definition of CMAKE_PREFIX_PATH, CMAKE_XXXXX_PATH
# The explicitly defined "builddirs" of "host" context dependencies must be in PREFIX_PATH
list(PREPEND CMAKE_PREFIX_PATH "/root/.conan/data/openssl/3.2.2/_/_/package/304480252b01879c8641f79a653b593b8f26cf9f/lib/cmake")
# The Conan local "generators" folder, where this toolchain is saved.
list(PREPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_LIST_DIR} )
list(PREPEND CMAKE_PROGRAM_PATH "/root/.conan/data/libcurl/8.8.0/_/_/package/cc81a4ac0f53bb34dfacdd1bdf7119a23670f6fb/bin" "/root/.conan/data/openssl/3.2.2/_/_/package/304480252b01879c8641f79a653b593b8f26cf9f/bin" "/root/.conan/data/zlib/1.3.1/_/_/package/dfbe50feef7f3c6223a476cd5aeadb687084a646/bin")
list(PREPEND CMAKE_LIBRARY_PATH "/root/.conan/data/libcurl/8.8.0/_/_/package/cc81a4ac0f53bb34dfacdd1bdf7119a23670f6fb/lib" "/root/.conan/data/openssl/3.2.2/_/_/package/304480252b01879c8641f79a653b593b8f26cf9f/lib" "/root/.conan/data/zlib/1.3.1/_/_/package/dfbe50feef7f3c6223a476cd5aeadb687084a646/lib")
list(PREPEND CMAKE_INCLUDE_PATH "/root/.conan/data/libcurl/8.8.0/_/_/package/cc81a4ac0f53bb34dfacdd1bdf7119a23670f6fb/include" "/root/.conan/data/openssl/3.2.2/_/_/package/304480252b01879c8641f79a653b593b8f26cf9f/include" "/root/.conan/data/zlib/1.3.1/_/_/package/dfbe50feef7f3c6223a476cd5aeadb687084a646/include")



if (DEFINED ENV{PKG_CONFIG_PATH})
set(ENV{PKG_CONFIG_PATH} "/home/ubuntu/devsecops/conan/OTACauth:$ENV{PKG_CONFIG_PATH}")
else()
set(ENV{PKG_CONFIG_PATH} "/home/ubuntu/devsecops/conan/OTACauth:")
endif()




# Variables
# Variables  per configuration


# Preprocessor definitions
# Preprocessor definitions per configuration
