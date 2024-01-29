cmake_minimum_required(VERSION 3.5)
project(module LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} main.cpp)

# --- OpenCV start ---
set(OPENCV_PATH "../opencv")

# opencv2/opencv.hpp
include_directories("${OPENCV_PATH}/include")

# opencv.hpp for opencv2/opencv_modules.hpp
include_directories("${OPENCV_PATH}/build_wasm")

# opencv_modules.hpp for every module
file(GLOB opencv_include_modules "${OPENCV_PATH}/modules/*/include")
include_directories(${opencv_include_modules})

# Link opencv.js precompiled libraries
file(GLOB opencv_libs "${OPENCV_PATH}/build_wasm/lib/*.a")
target_link_libraries(${PROJECT_NAME} ${opencv_libs})

# There is an issue regarding the order in which libraries
# are passed to the compiler - pass libopencv_core.a last
file(GLOB opencv_lib_core "${OPENCV_PATH}/build_wasm/lib/libopencv_core.a")
target_link_libraries(${PROJECT_NAME} ${opencv_lib_core})
# --- OpenCV end ---

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
