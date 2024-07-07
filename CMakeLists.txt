cmake_minimum_required(VERSION 3.21)

option(GOTHIC_API_G1  "This option compiles Gothic API for Gothic I. By default this option is set to ON" ON)
option(GOTHIC_API_G1A "This option compiles Gothic API for Gothic Sequel (Gothic I Addon). By default this option is set to ON" ON)
option(GOTHIC_API_G2  "This option compiles Gothic API for Gothic II Classic. By default this option is set to ON" ON)
option(GOTHIC_API_G2A "This option compiles Gothic API for Gothic II Night of the Raven. By default this option is set to ON" ON)

project(GothicAPI VERSION "1.0.0")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(gothic_api INTERFACE)
target_include_directories(gothic_api INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ZenGin/Gothic_UserAPI>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}include/ZenGin/Gothic_UserAPI>
)
target_link_directories(gothic_api INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}include>
)
target_sources(gothic_api INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ZenGin/zGothicAPI.cpp>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}include/ZenGin/zGothicAPI.cpp>
)

if(${GOTHIC_API_G1})
    target_compile_definitions(gothic_api INTERFACE __G1)
endif()
if(${GOTHIC_API_G1A})
    target_compile_definitions(gothic_api INTERFACE __G1A)
endif()
if(${GOTHIC_API_G2})
    target_compile_definitions(gothic_api INTERFACE __G2)
endif()
if(${GOTHIC_API_G2A})
    target_compile_definitions(gothic_api INTERFACE __G2A)
endif()

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ZenGin DESTINATION include)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/GothicAPIConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/GothicAPIConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/GothicAPIConfig.cmake"
    INSTALL_DESTINATION "cmake/GothicAPI"
)
install(FILES 
    "${CMAKE_CURRENT_BINARY_DIR}/GothicAPIConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/GothicAPIConfigVersion.cmake"
    DESTINATION "cmake/GothicAPI"
)
install(TARGETS gothic_api
    EXPORT gothic_apiTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(EXPORT gothic_apiTargets 
    FILE GothicAPITargets.cmake
    DESTINATION "cmake/GothicAPI"
)