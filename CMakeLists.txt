cmake_minimum_required(VERSION 3.1)
project(psydapt-js)
set(CMAKE_CXX_STANDARD 17) # std::optional
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(psydapt)

add_executable(psydapt-js psydapt.cpp)
target_link_libraries(psydapt-js PUBLIC psydapt
"-O3"
"--bind"
"-s WASM=1"
"-s DISABLE_EXCEPTION_CATCHING=0"
"-s ALLOW_MEMORY_GROWTH=1"
"-s EXPORT_NAME='psydapt'"
"-s MODULARIZE=1"
"-s MALLOC=emmalloc"
"-s EXPORT_ES6=1"
"-s FILESYSTEM=0"
"-s SINGLE_FILE=1"
"-o psydapt.js"
)
