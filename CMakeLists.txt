cmake_minimum_required(VERSION 3.16)
project(Aviation_Proj LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(apps/dashboard)
add_subdirectory(libs/telemetry_core)