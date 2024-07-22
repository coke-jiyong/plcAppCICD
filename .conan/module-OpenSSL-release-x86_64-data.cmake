########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

list(APPEND openssl_COMPONENT_NAMES OpenSSL::Crypto OpenSSL::SSL)
list(REMOVE_DUPLICATES openssl_COMPONENT_NAMES)
list(APPEND openssl_FIND_DEPENDENCY_NAMES ZLIB)
list(REMOVE_DUPLICATES openssl_FIND_DEPENDENCY_NAMES)
set(ZLIB_FIND_MODE "MODULE")

########### VARIABLES #######################################################################
#############################################################################################
set(openssl_PACKAGE_FOLDER_RELEASE "/root/.conan/data/openssl/3.2.2/_/_/package/304480252b01879c8641f79a653b593b8f26cf9f")
set(openssl_BUILD_MODULES_PATHS_RELEASE "${openssl_PACKAGE_FOLDER_RELEASE}/lib/cmake/conan-official-openssl-variables.cmake")


set(openssl_INCLUDE_DIRS_RELEASE "${openssl_PACKAGE_FOLDER_RELEASE}/include")
set(openssl_RES_DIRS_RELEASE )
set(openssl_DEFINITIONS_RELEASE )
set(openssl_SHARED_LINK_FLAGS_RELEASE )
set(openssl_EXE_LINK_FLAGS_RELEASE )
set(openssl_OBJECTS_RELEASE )
set(openssl_COMPILE_DEFINITIONS_RELEASE )
set(openssl_COMPILE_OPTIONS_C_RELEASE )
set(openssl_COMPILE_OPTIONS_CXX_RELEASE )
set(openssl_LIB_DIRS_RELEASE "${openssl_PACKAGE_FOLDER_RELEASE}/lib")
set(openssl_LIBS_RELEASE ssl crypto)
set(openssl_SYSTEM_LIBS_RELEASE dl pthread rt)
set(openssl_FRAMEWORK_DIRS_RELEASE )
set(openssl_FRAMEWORKS_RELEASE )
set(openssl_BUILD_DIRS_RELEASE "${openssl_PACKAGE_FOLDER_RELEASE}/lib/cmake")

# COMPOUND VARIABLES
set(openssl_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${openssl_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${openssl_COMPILE_OPTIONS_C_RELEASE}>")
set(openssl_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${openssl_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${openssl_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${openssl_EXE_LINK_FLAGS_RELEASE}>")


set(openssl_COMPONENTS_RELEASE OpenSSL::Crypto OpenSSL::SSL)
########### COMPONENT OpenSSL::SSL VARIABLES ############################################

set(openssl_OpenSSL_SSL_INCLUDE_DIRS_RELEASE "${openssl_PACKAGE_FOLDER_RELEASE}/include")
set(openssl_OpenSSL_SSL_LIB_DIRS_RELEASE "${openssl_PACKAGE_FOLDER_RELEASE}/lib")
set(openssl_OpenSSL_SSL_RES_DIRS_RELEASE )
set(openssl_OpenSSL_SSL_DEFINITIONS_RELEASE )
set(openssl_OpenSSL_SSL_OBJECTS_RELEASE )
set(openssl_OpenSSL_SSL_COMPILE_DEFINITIONS_RELEASE )
set(openssl_OpenSSL_SSL_COMPILE_OPTIONS_C_RELEASE "")
set(openssl_OpenSSL_SSL_COMPILE_OPTIONS_CXX_RELEASE "")
set(openssl_OpenSSL_SSL_LIBS_RELEASE ssl)
set(openssl_OpenSSL_SSL_SYSTEM_LIBS_RELEASE dl pthread)
set(openssl_OpenSSL_SSL_FRAMEWORK_DIRS_RELEASE )
set(openssl_OpenSSL_SSL_FRAMEWORKS_RELEASE )
set(openssl_OpenSSL_SSL_DEPENDENCIES_RELEASE OpenSSL::Crypto)
set(openssl_OpenSSL_SSL_SHARED_LINK_FLAGS_RELEASE )
set(openssl_OpenSSL_SSL_EXE_LINK_FLAGS_RELEASE )
# COMPOUND VARIABLES
set(openssl_OpenSSL_SSL_LINKER_FLAGS_RELEASE
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${openssl_OpenSSL_SSL_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${openssl_OpenSSL_SSL_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${openssl_OpenSSL_SSL_EXE_LINK_FLAGS_RELEASE}>
)
set(openssl_OpenSSL_SSL_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${openssl_OpenSSL_SSL_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${openssl_OpenSSL_SSL_COMPILE_OPTIONS_C_RELEASE}>")
########### COMPONENT OpenSSL::Crypto VARIABLES ############################################

set(openssl_OpenSSL_Crypto_INCLUDE_DIRS_RELEASE "${openssl_PACKAGE_FOLDER_RELEASE}/include")
set(openssl_OpenSSL_Crypto_LIB_DIRS_RELEASE "${openssl_PACKAGE_FOLDER_RELEASE}/lib")
set(openssl_OpenSSL_Crypto_RES_DIRS_RELEASE )
set(openssl_OpenSSL_Crypto_DEFINITIONS_RELEASE )
set(openssl_OpenSSL_Crypto_OBJECTS_RELEASE )
set(openssl_OpenSSL_Crypto_COMPILE_DEFINITIONS_RELEASE )
set(openssl_OpenSSL_Crypto_COMPILE_OPTIONS_C_RELEASE "")
set(openssl_OpenSSL_Crypto_COMPILE_OPTIONS_CXX_RELEASE "")
set(openssl_OpenSSL_Crypto_LIBS_RELEASE crypto)
set(openssl_OpenSSL_Crypto_SYSTEM_LIBS_RELEASE dl rt pthread)
set(openssl_OpenSSL_Crypto_FRAMEWORK_DIRS_RELEASE )
set(openssl_OpenSSL_Crypto_FRAMEWORKS_RELEASE )
set(openssl_OpenSSL_Crypto_DEPENDENCIES_RELEASE ZLIB::ZLIB)
set(openssl_OpenSSL_Crypto_SHARED_LINK_FLAGS_RELEASE )
set(openssl_OpenSSL_Crypto_EXE_LINK_FLAGS_RELEASE )
# COMPOUND VARIABLES
set(openssl_OpenSSL_Crypto_LINKER_FLAGS_RELEASE
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${openssl_OpenSSL_Crypto_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${openssl_OpenSSL_Crypto_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${openssl_OpenSSL_Crypto_EXE_LINK_FLAGS_RELEASE}>
)
set(openssl_OpenSSL_Crypto_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${openssl_OpenSSL_Crypto_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${openssl_OpenSSL_Crypto_COMPILE_OPTIONS_C_RELEASE}>")