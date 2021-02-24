
# # If libraries declared here, all is ok
# add_library(Foo STATIC "")
# add_library(Foo::Foo ALIAS Foo)

target_sources(Foo
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/Foo.hpp>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/Foo.hpp> 
  PRIVATE 
    Foo.cpp  
)

target_include_directories(Foo
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/Foo>    
)

target_link_libraries(Foo
  PUBLIC
    pthread
  PRIVATE
    avcodec  
    avformat
    avutil
    swscale
)