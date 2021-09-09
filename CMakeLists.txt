cmake_minimum_required(VERSION 3.20)
project(LSM)

set(CMAKE_CXX_STANDARD 17)

add_executable(LSM main.cpp src/Utilities/arr_util.cpp include/Utilities/arr_util.h src/lsm_impl.cpp include/lsm_impl.h src/lsm_template.cpp include/lsm_template.h src/Node.cpp include/Node.h src/FileSystem.cpp include/FileSystem.h src/Utilities/ArrayBasic.cpp include/Utilities/ArrayBasic.h src/Iris.cpp include/Iris.h)
