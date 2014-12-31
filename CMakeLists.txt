cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

IF(DEFINED CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE}
  CACHE STRING "Choose the type of build: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
ELSE()
  SET(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
  "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
ENDIF()

PROJECT(avx1int)

SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-mavx -Wall -Werror -g -O3")
SET(CMAKE_CXX_FLAGS_DEBUG "-Wall -Werror -mavx -O0 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "-mavx -O3 -g0 -DNDEBUG")

add_executable(test_avx1int
    avx1int.h
    test.cpp
)


