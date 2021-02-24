cmake_minimum_required(VERSION 3.14)
project(Foo VERSION 0.1.0)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)


set(FOO_INSTALL_LIB_DIR ${CMAKE_INSTALL_LIBDIR}/foo)
set(FOO_INSTALL_CONFIG_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/foo)
set(FOO_INSTALL_INCLUDE_DIR ${CMAKE_INSTALL_INCLUDEDIR}/foo)

# if libraries are declared here, then the FooTargets.cmake has weird INTERFACE_LINK_LIBRARIES for 
# PRIVATE libraries

# add_library(Foo STATIC "")
# add_library(Foo::Foo ALIAS Foo)

add_subdirectory(src)

install(TARGETS Foo EXPORT Foo-export
  ARCHIVE DESTINATION ${FOO_INSTALL_LIB_DIR}
)

install(
  EXPORT Foo-export
  FILE FooTargets.cmake
  NAMESPACE apcl::
  DESTINATION ${FOO_INSTALL_CONFIG_DIR}
)

# create a version file with compatibility data
write_basic_package_version_file(
  "${PROJECT_BINARY_DIR}/FooConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY ExactVersion
)

# create the config file that will find dependencies and load the exported targets for use by a 
# downstream project
configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/FooConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/FooConfig.cmake
  INSTALL_DESTINATION ${FOO_INSTALL_CONFIG_DIR}
)

install(FILES 
  ${PROJECT_BINARY_DIR}/FooConfig.cmake
  ${PROJECT_BINARY_DIR}/FooConfigVersion.cmake
  DESTINATION ${FOO_INSTALL_CONFIG_DIR}
)