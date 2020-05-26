# CMakeLists Template

```cmake
cmake_minimum_required(VERSION 3.10)

# ==============================
project(CMakeTemplate)
# project()指令会生成一些变量：
#     PROJECT_NAME
#     <projectname>_BINARY_DIR, <projectname>_SOURCE_DIR
#     PROJECT_BINARY_DIR, PROJECT_SOURCE_DIR
# 在内部编译时二者皆为工程路径，
# 在外部编译时SOURCE_DIR为指定的路径，BINARY_DIR为BINARY_DIR命令执行所在路径。


# 设置变量，使用变量 ${var}
set(Template_VERSION_MAJOR 0)
set(Template_VERSION_MINOR 1)

# 向终端传递信息
message(STATUS "Version is ${Template_VERSION_MAJOR}.${Template_VERSION_MINOR}")

# 指定C++标准
# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED True)


# ==============================
# 此外可以对编译后的可执行文件和库文件分别指定输出目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# 使用CMake进行编译控制的方法
# 在源代码中使用 #ifdef, #ifndef 控制不同环境下的代码编译
# 但是CMake无法理解cpp文件，需要设置一个它能理解的文件--in文件
# config.h.in中的内容
#cmakedefine USE_CUDA
# configure_file可以用in文件生成h文件，通过编写in文件可以改变源代码中的宏
# 这是一种文件内的编译控制
configure_file (
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_SOURCE_DIR}/src/config.h"
)
# 添加选项
option(USE_CUDA "Using CUDA" on) # 默认为开启
# 使用CMake的语法可以控制文件级的编译
if(USE_CUDA)
    # command of compiling control if USE_CUDA defined
else
    # command of compiling control if USE_CUDA not defined
endif(USE_CUDA)

# ==============================
# 设置工程的库的目录，前者为库的源文件目录，后者为库的编译目标目录(bin, lib)，后者可不设置
# src中也要含有CMakeLists.txt，不会改变 PROJECT_BINARY_DIR, PROJECT_SOURCE_DIR
add_subdirectory(extra_src extra_bin)

# CMakeLists文件会产生另外两个变量
# CMAKE_CURRENT_SOURCE_DIR，CMakeLists文件所在处
# CMAKE_CURRRENT_BINARY_DIR，内部编译时为CMakeLists文件所在处，外部编译时为编译目录

# 添加库，默认为static
# static 静态库，后会打包至可执行文件
aux_source_directory(${PROJECT_SOURCE_DIR}/extra_src STATIC_LIB_SOURCE_DIR)
add_library(static_lib ${STATIC_LIB_SOURCE_DIR})
# shared 动态库，作为单独的文件
aux_source_directory(${PROJECT_SOURCE_DIR}/extra_src SHARED_LIB_SOURCE_DIR)
add_library(shared_lib SHARED ${SHARED_LIB_SOURCE_DIR})
# object 中间库文件，可以链接到其他库
aux_source_directory(${PROJECT_SOURCE_DIR}/object_src OBJECT_LIB_SOURCE_DIR)
add_library(object_lib OBJECT ${OBJECT_LIB_SOURCE_DIR})
target_link_libraries(static_lib object_lib)

include_directories(${PROJECT_SOURCE_DIR}/include)
# 生成执行文件
file(GLOB SOURCE_DIR ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(CMakeTemplate ${SOURCE_DIR})

# 连接库
target_link_libraries(CMakeTemplate PUBLIC static_lib shared_lib)
target_include_directories(CMakeTemplate PUBLIC "${PROJECT_BINARY_DIR}")

# ==============================
# 使用外部库
find_package(OpenCV REQUIRED)
# 如果自己提供FindXXXX.cmake文件，需要使用如下指令增加文件查找目录./cmake/modules/
set(CMAKE_MODULE_PATH APPEND "${PROJECT_SOURCE_DIR}/cmake/modules/")
# 查找到外部库后会返回一些变量
# OpenCV_FOUND, OpenCV_INCLUDE_DIRS, OpenCV_LIBRARIES
if (OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
    target_link_libraries(SIFT ${OpenCV_LIBRARIES})
endif (OpenCV REQUIRED)

# ==============================
# 使用install可以将程序安装到系统中，多用于对外发布的程序或库
# 不想污染系统，可以使用install将程序和相关文件复制到同一个文件夹
# 分别将二进制而建、动态库、静态库安装到不同的目录下
install(TARGETS TargetName SharedLib StaticLib
        RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/release/bin
        LIBRARY DESTINATION ${CMAKE_BINARY_DIR}/release/lib
        ARCHIVE DESTINATION ${CMAKE_BINARY_DIR}/release/lib-static
)
# 安装普通文件
install(FILES README.md licence.txt DESTINATION ${CMAKE_BINARY_DIR}/release) # 权限644
# 安装脚本等可执行文件
install(PROGRAMS generator.sh DESTINATION ${CMAKE_BINARY_DIR}/release/bin) # 权限755
# 安装整个目录
install(DIRECTORY res/ DESTINATION ${CMAKE_BINARY_DIR}/release/res)
# 实际的安装要复杂的多，在长期项目中可以考虑维护一个较好的安装脚本，用于 night build

# 也可以使用add_custom_command
add_custom_command(TARGET TargetName POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${PROJECT_SOURCE_DIR}/lib/3rdparty.dll
        ${CMAKE_BINARY_DIR}/release/bin
)
```

