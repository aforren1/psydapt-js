cmake_minimum_required(VERSION 3.9)
project(psydapt-js)
set(CMAKE_CXX_STANDARD 17) # std::optional
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CheckIPOSupported)
check_ipo_supported()

add_subdirectory(psydapt)

add_executable(psydapt-js src/psydapt.cpp)
set_property(TARGET psydapt-js PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
target_link_libraries(psydapt-js PUBLIC psydapt
"-O3"
"--bind"
"-s STRICT=1"
"--no-entry"
"-s WASM=1"
"-s DISABLE_EXCEPTION_CATCHING=1"
"-s ALLOW_MEMORY_GROWTH=1"
"-s EXPORT_NAME='createPsydapt'"
"-s MODULARIZE=1"
"-s MALLOC=emmalloc"
"-s EXPORT_ES6=1"
"-s FILESYSTEM=0"
"-s SINGLE_FILE=1"
"--closure 1"
"-flto"
"-o psydapt-es6.js"
#"--extern-post-js ''"
)
