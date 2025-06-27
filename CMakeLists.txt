
cmake_minimum_required(VERSION 3.22.1)
project(ecap-http-signatures VERSION 0.0.1
                 DESCRIPTION "eCAP module providing HTTP Message Signatures (RFC 9421)"
                 LANGUAGES CXX)

## Environment setup
include(GNUInstallDirs)
include_directories(${CMAKE_INSTALL_OLDINCLUDEDIR})
configure_file("src/config.h.in" "src/config.h")

## Shared library module
add_library(ecap-http-signatures MODULE
    src/Service.cc
    src/VerifyRequest.cc
)
set_target_properties(ecap-http-signatures PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
target_link_libraries(ecap-http-signatures PRIVATE ecap)
install(TARGETS ecap-http-signatures
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

## Squid configuration defaults
configure_file("src/ecap-http-signatures.conf.in" "ecap-http-signatures.conf")
install(FILES ecap-http-signatures.conf
    PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
    DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}/squid/conf.d/
)
