project(spin)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES library.cpp library.h Parttern/Maybe.h Parttern/Promise.h Parttern/Channel.h)
add_library(spin ${SOURCE_FILES})