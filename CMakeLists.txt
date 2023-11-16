cmake_minimum_required(VERSION 3.5)

project(wasmd_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(wasmd_cpp main.cpp)

target_link_options(${PROJECT_NAME} PUBLIC
    "SHELL: -sALLOW_TABLE_GROWTH
    -sEXPORTED_RUNTIME_METHODS=\"['cwrap', 'addFunction', 'callMain']\"
    -sEXPORT_ES6=1
    -sMODULARIZE=1
    -sENVIRONMENT='web'")

set(wasmd_wasm_path "D:/Code/wasmd_web/src/wasm/")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.js" "${wasmd_wasm_path}${PROJECT_NAME}.js"
    COMMENT "Copy ${PROJECT_NAME}")
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.wasm" "${wasmd_wasm_path}${PROJECT_NAME}.wasm"
    COMMENT "Copy ${PROJECT_NAME}.wasm")
