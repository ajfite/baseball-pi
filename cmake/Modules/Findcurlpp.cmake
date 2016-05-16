include(FindPkgConfig)
include(FindPackageHandleStandardArgs)

# Use pkg-config to get hints about paths
pkg_check_modules(curlpp_PKGCONF REQUIRED curlpp)

# Include dir
find_path(curlpp_INCLUDE_DIR
        NAMES curlpp/cURLpp.hpp
        PATHS ${curlpp_PKGCONF_INCLUDE_DIRS}
        )

# Finally the library itself
find_library(curlpp_LIBRARY
        NAMES curlpp
        PATHS ${curlpp_PKGCONF_LIBRARY_DIRS}
        )

FIND_PACKAGE_HANDLE_STANDARD_ARGS(curlpp DEFAULT_MSG curlpp_LIBRARY curlpp_INCLUDE_DIR)


if(curlpp_PKGCONF_FOUND)
    set(curlpp_LIBRARIES ${curlpp_LIBRARY} ${curlpp_PKGCONF_LIBRARIES})
    set(curlpp_INCLUDE_DIRS ${curlpp_INCLUDE_DIR} ${curlpp_PKGCONF_INCLUDE_DIRS})
    set(curlpp_FOUND yes)
else()
    set(curlpp_LIBRARIES)
    set(curlpp_INCLUDE_DIRS)
    set(curlpp_FOUND no)
endif()
