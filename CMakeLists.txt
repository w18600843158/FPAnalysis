cmake_minimum_required(VERSION 3.10)
project(c)

set(CMAKE_CXX_STANDARD 11)

link_directories("./lib")
link_libraries(PassModule)

set(CMAKE_CXX_FLAGS "-fPIC -fno-rtti ${CMAKE_CXX_FLAGS}")
set(CMAKE_C_FLAGS  "-emit-llvm -g ${CMAKE_C_FLAGS}")

add_executable(atomic_condition_master
        src/communicator.h
        src/fpInterface.h
        src/fpUtil.cpp
        src/fpUtil.h
        src/solver.cpp
        src/handlers.cpp
        src/opcode.h
        src/target.h
        src/targetExample.c)

target_link_libraries(atomic_condition_master
        PassModule)