cmake_minimum_required(VERSION 3.5)
project(module LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} main.cpp)

target_link_options(${PROJECT_NAME} PUBLIC
    "SHELL:
    -sENVIRONMENT='web'
    -sEXPORTED_FUNCTIONS=\"['_add', '_run']\"
    -sEXPORTED_RUNTIME_METHODS=\"['cwrap', 'addFunction']\"
    -sALLOW_TABLE_GROWTH
    -sEXPORT_ES6=1
    -sMODULARIZE=1")

set(web_path "../../wasmd_web/src/wasm/")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.js" "${web_path}${PROJECT_NAME}.js"
    COMMENT "Copy ${PROJECT_NAME}.js")
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.wasm" "${web_path}${PROJECT_NAME}.wasm"
    COMMENT "Copy ${PROJECT_NAME}.wasm")
