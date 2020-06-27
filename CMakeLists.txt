cmake_minimum_required(VERSION 2.6)
project(DOMLIB)

if(CMAKE_C_COMPILER_ID MATCHES "Clang")
    # finding openmp fails for certain versions of clang
    set(OpenMP_C_FLAGS "-fopenmp")
else()
    find_package(OpenMP REQUIRED)
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")

if (DEFINED DEBUG OR DEFINED ASSERT)
  if (DEFINED DEBUG)
    add_definitions(-DDEBUG=${DEBUG})
    message("Debugging enabled")
  endif()
  if (DEFINED ASSERT)
    add_definitions(-DUSE_ASSERTS=${ASSERT})
    message("Assertions enabled")
  else()
    add_definitions(-DNDEBUG=1)
    add_definitions(-DNDEBUG2=1)
  endif()
  set(CMAKE_BUILD_TYPE Debug)
  message("Building a debug release")
else()
  set(CMAKE_BUILD_TYPE Release)
  add_definitions(-DNDEBUG=1)
  add_definitions(-DNDEBUG2=1)
  message("Building an optimized release")
endif()

if (DEFINED DEVEL AND NOT DEVEL EQUAL 0)
  message("Development warnings enabled")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror") 
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall") 
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wextra") 
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wmissing-prototypes") 
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wmissing-declarations") 
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wstrict-aliasing") 
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-parameter") 
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-function") 
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic") 
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fstrict-aliasing") 
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99") 

if ("${CMAKE_C_COMPILER_ID}" STREQUAL "Intel")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -no-ansi-alias")
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# build library
include_directories(.)
file(GLOB domlib_sources *.c)
add_library(domlib STATIC
  ${domlib_sources}
)
target_link_libraries(domlib m)

if (DEFINED TESTS AND NOT TESTS EQUAL 0)
  enable_testing()
  add_subdirectory(tests)
endif()


