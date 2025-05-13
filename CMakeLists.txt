cmake_minimum_required(VERSION 3.8)
project(Zefir-Engine)

set(CMAKE_CXX_STANDARD 20)

# Engine static library
add_subdirectory(Zefir)

# Apps directories
add_subdirectory(Sandbox)
add_subdirectory(PhysicsSandbox)
