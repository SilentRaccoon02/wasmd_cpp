cmake_minimum_required(VERSION 3.5)

project(wasmd_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(wasmd_cpp main.cpp)

include(GNUInstallDirs)
install(TARGETS wasmd_cpp
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
