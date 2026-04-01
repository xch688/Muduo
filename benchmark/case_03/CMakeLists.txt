cmake_minimum_required(VERSION 4.0)
project(benchmark_case03)

function(force_redefine_file_macro_for_sources targetname)
    get_target_property(source_files "${targetname}" SOURCES)
    foreach (sourcefile ${source_files})
        # Get source file's current list of compile definitions.
        get_property(defs SOURCE "${sourcefile}"
                PROPERTY COMPILE_DEFINITIONS)
        # Get the relative path of the source file in project directory
        get_filename_component(filepath "${sourcefile}" ABSOLUTE)
        string(REPLACE ../.. "" relpath ${filepath})
        list(APPEND defs "__FILE__=\"${relpath}\"")
        # Set the updated compile definitions on the source file.
        set_property(
                SOURCE "${sourcefile}"
                PROPERTY COMPILE_DEFINITIONS ${defs}
        )
    endforeach ()
endfunction()


set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -std=c++20 -O2 -ggdb -Wall -Werror -Wno-unused-result")

# -rdynamic: 将所有符号都加入到符号表中，便于使用 dlopen 或 backtrace 追踪到符号
# -fPIC: 生成位置无关的代码，便于动态链接
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -rdynamic -fPIC")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

# -Wno-unused-function: 不要警告未使用函数
# -Wno-builtin-macro-redefined: 不要警告内置宏重定义，用于重定义内置的 __FILE__ 宏
# -Wno-deprecated: 不要警告过时的特性
# -Wno-deprecated-declarations: 不要警告使用带 deprecated 属性的变量、类型、函数
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}   \
    -Wno-unused-function                  \
    -Wno-builtin-macro-redefined          \
    -Wno-deprecated                       \
    -Wno-deprecated-declarations"
)
set(CMAKE_BUILD_TYPE Debug)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # 强制开启颜色和标准诊断格式
    add_compile_options(-fdiagnostics-color=always)
endif ()

find_package(benchmark REQUIRED)

aux_source_directory(${CMAKE_SOURCE_DIR}/sylar LOG_SRCS)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRCS)

add_compile_options(-g -gdwarf-4 -fno-omit-frame-pointer)

add_executable(${PROJECT_NAME} ${SRCS} ${LOG_SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR})

# 注意：Benchmark 依赖 pthread（线程库），必须一起链接
target_link_libraries(${PROJECT_NAME} benchmark::benchmark pthread)
force_redefine_file_macro_for_sources(${PROJECT_NAME})

set(OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY}"
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIRECTORY}"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIRECTORY}"
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${OUTPUT_DIRECTORY}"
        RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${OUTPUT_DIRECTORY}"
)