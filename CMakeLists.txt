cmake_minimum_required(VERSION 2.6)
project(DOMLIB)

find_package(OpenMP REQUIRED)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")

if (DEFINED DEBUG OR DEFINED ASSERT)
  if (DEFINED DEBUG)
    add_definitions(-DDEBUG=${DEBUG})
    message("Debugging enabled")
  endif()
  if (DEFINED ASSERT)
    add_definitions(-DUSE_ASSERTS=${ASSERT})
    message("Assertions enabled")
  endif()
  set(CMAKE_BUILD_TYPE Debug)
  message("Building a debug release")
else()
  set(CMAKE_BUILD_TYPE Release)
  add_definitions(-DNDEBUG=1)
  message("Building an optimized release")
endif()

if (STATIC)
  set(DOMLIB_LIBRARY_TYPE STATIC)
else()
  set(DOMLIB_LIBRARY_TYPE SHARED)
endif()

if (DEFINED DEVEL AND NOT DEVEL EQUAL 0)
  message("Development mode enabled")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror") 
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall") 
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wextra") 
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wmissing-prototypes") 
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wmissing-declarations") 
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wstrict-aliasing") 
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-parameter") 
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-function") 
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic") 
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99") 

include_directories(.)

file(GLOB domlib_sources *.c)

add_library(domlib ${DOMLIB_LIBRARY_TYPE} 
  ${domlib_sources}
)

if (NOT WIN32)
  # use gnu directories
  include(GNUInstallDirs)

  install(TARGETS domlib
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )
endif()

# must be before including src
if (DEFINED TESTS AND NOT TESTS EQUAL 0)
  enable_testing()
  add_subdirectory("test")
endif()

