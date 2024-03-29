cmake_minimum_required(VERSION 3.9)
project(psydapt-js)
set(CMAKE_CXX_STANDARD 17) # std::optional
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CheckIPOSupported)
check_ipo_supported()

add_subdirectory(psydapt)

option(INCLUDE_ALL "Include all routines" ON)
option(INCLUDE_STAIRCASE "Include staircase" OFF)
option(INCLUDE_QP_WEIBULL "Include quest+ Weibull" OFF)
option(INCLUDE_QP_NORMCDF "Include quest+ NormCDF" OFF)
option(INCLUDE_QP_CSF "Include quest+ CSF" OFF)

set(SUFFIX "")
if(INCLUDE_ALL)
    message(STATUS "Including all routines")
    set(INCLUDE_STAIRCASE ON CACHE BOOL "" FORCE)
    set(INCLUDE_QP_WEIBULL ON CACHE BOOL "" FORCE)
    set(INCLUDE_QP_NORMCDF ON CACHE BOOL "" FORCE)
    set(INCLUDE_QP_CSF ON CACHE BOOL "" FORCE)
endif()

if(INCLUDE_STAIRCASE)
    if(NOT INCLUDE_ALL)
        set(SUFFIX "${SUFFIX}-staircase")
    endif()
    message(STATUS "Including staircase")
    add_definitions(-DUSE_STAIRCASE)
endif()

if(INCLUDE_QP_WEIBULL)
    if(NOT INCLUDE_ALL)
        set(SUFFIX "${SUFFIX}-qp_weibull")
    endif()
    message(STATUS "Including quest+ Weibull")
    add_definitions(-DUSE_QP_WEIBULL)
endif()

if(INCLUDE_QP_NORMCDF)
    if(NOT INCLUDE_ALL)
        set(SUFFIX "${SUFFIX}-qp_normcdf")
    endif()
    message(STATUS "Including quest+ NormCDF")
    add_definitions(-DUSE_QP_NORMCDF)
endif()

if(INCLUDE_QP_CSF)
    if(NOT INCLUDE_ALL)
        set(SUFFIX "${SUFFIX}-qp_csf")
    endif()
    message(STATUS "Including quest+ CSF")
    add_definitions(-DUSE_QP_CSF)
endif()

set(PSYDAPT_DISABLE_EXCEPTIONS ON CACHE BOOL "" FORCE)
set(PSYDAPT_FAST_MATH ON CACHE BOOL "" FORCE)
# makes code significantly larger?
#add_definitions(-DPSYDAPT_DISABLE_EXCEPTIONS)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-rtti -DEMSCRIPTEN_HAS_UNBOUND_TYPE_NAMES=0")

add_executable(psydapt-js src/psydapt.cpp)
set_property(TARGET psydapt-js PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
target_link_libraries(psydapt-js PUBLIC psydapt
"-O3"
"--bind"
"--no-entry"
"-s STRICT=1"
"-s WASM=1"
"-s DISABLE_EXCEPTION_CATCHING=1"
"-s ALLOW_MEMORY_GROWTH=1"
"-s EXPORT_NAME='createPsydapt'"
"-s MODULARIZE=1"
"-s EXPORT_ES6=1"
"-s MALLOC=emmalloc"
"-s FILESYSTEM=0"
"-s SINGLE_FILE=1"
"--closure 1"
"-flto"
#"-s USE_ES6_IMPORT_META=0" # ??
"-s ENVIRONMENT=web" # no size differences
"-o psydapt${SUFFIX}-es6.js"
)
