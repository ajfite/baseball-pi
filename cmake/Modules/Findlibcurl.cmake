include(FindPkgConfig)
include(FindPackageHandleStandardArgs)

# Use pkg-config to get hints about paths
pkg_check_modules(libcurl_PKGCONF REQUIRED libcurl)

# Include dir
find_path(libcurl_INCLUDE_DIR
        NAMES curl/curl.h
        PATHS ${libcurl_PKGCONF_INCLUDE_DIRS}
        )

# Finally the library itself
find_library(libcurl_LIBRARY
        NAMES libcurl libcurl4 libcurl4-openssl curl
        PATHS ${libcurl_PKGCONF_LIBRARY_DIRS}
        )

FIND_PACKAGE_HANDLE_STANDARD_ARGS(libcurl DEFAULT_MSG libcurl_LIBRARY libcurl_INCLUDE_DIR)


if(libcurl_PKGCONF_FOUND)
    set(libcurl_LIBRARIES ${libcurl_LIBRARY} ${libcurl_PKGCONF_LIBRARIES})
    set(libcurl_INCLUDE_DIRS ${libcurl_INCLUDE_DIR} ${libcurl_PKGCONF_INCLUDE_DIRS})
    set(libcurl_FOUND yes)
else()
    set(libcurl_LIBRARIES)
    set(libcurl_INCLUDE_DIRS)
    set(libcurl_FOUND no)
endif()
