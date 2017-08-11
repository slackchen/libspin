project(spin)

set(CMAKE_CXX_STANDARD 11)

IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(UCONTEXT_SRC Parttern/ucontext.c Parttern/ucontext.h)
ENDIF()
set(SOURCE_FILES ${UCONTEXT_SRC} library.cpp library.h Parttern/Maybe.h Parttern/Promise.h Parttern/Channel.h Parttern/Coroutine.cpp Parttern/Coroutine.h)
add_library(spin ${SOURCE_FILES})