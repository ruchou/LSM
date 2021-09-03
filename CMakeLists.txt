cmake_minimum_required(VERSION 3.20)
project(LSM)

set(CMAKE_CXX_STANDARD 17)

add_executable(LSM main.cpp arr_util.cpp arr_util.h lsm_impl.cpp lsm_impl.h lsm_template.cpp lsm_template.h Node.cpp Node.h)
