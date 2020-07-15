# CMakeLists Template

随着项目源文件增多，以及外部库、跨平台等需求，会使 makefile 越来越复杂。CMake 工具可以很好的解决这个问题，通过 CMakeLists.txt 文件中的设置项，CMake 可以自动生产 makefile 等控制编译的文件，然后可以使用 make 对项目进行编译。

下面以一个模板介绍 CMake 中的常用设置项。

```cmake
# ============================================================
# 一个最小的 CMakeLists.txt 文件包含以下内容
cmake_minimum_required(VERSION 3.10)
project(project_name)
add_executable(main main.cc)  # 这里指明由 main.cc 生成可执行文件 main
# ============================================================

# ============================================================
# 下面是一份关于 CMake 常用功能的详细介绍
# 对 CMake 程序的最小版本需求
cmake_minimum_required(VERSION 3.10)

# ========== 基础的设置 ==========
# 设置项目名称
project(CMakeTemplate)
# project()指令会生成一些变量：
#     PROJECT_NAME
#     <projectname>_BINARY_DIR, <projectname>_SOURCE_DIR
#     PROJECT_BINARY_DIR, PROJECT_SOURCE_DIR
# 在内部编译时二者皆为工程路径，
# 在外部编译时 SOURCE_DIR 为指定的路径，BINARY_DIR 为 cmake 命令执行所在路径。
# 这里的内部编译指在 CMakeLists 文件所在目录进行编译。
# 实际上多采用外部编译，先在项目文件夹下建立 build 文件夹，在 build 文件夹中执行 cmake .. 命令。
# 此时的 PROJECT_BINARY_DIR 指 build 文件夹。

# 设置变量，使用变量的方法：${var}
set(Template_VERSION_MAJOR 0)
set(Template_VERSION_MINOR 1)

# 指定 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置 C/C++ 的编译选项
# set(CMAKE_C_FLAGS -g)
# set(CMAKE_CXX_FLAGS -g)

# 向终端传递信息
message(STATUS "Version is ${Template_VERSION_MAJOR}.${Template_VERSION_MINOR}")

# 引入其他的 CMakeLists 文件
include(filename)
# =============================


# ========== 项目设置 ==========
# 使用 CMake 进行编译控制的方法
# 在 c/c++ 源代码中使用 #ifdef, #ifndef 控制不同环境下的代码编译，
# 但是 CMake 无法理解 c/cpp/h 文件，需要使用 in 文件保存设置。
# 例如 config.h.in 中的内容
#cmakedefine USE_CUDA
# configure_file() 可以用 in 文件生成 h 文件，通过编写 in 文件可以控制 c/c++ 源代码中的宏
configure_file (
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_SOURCE_DIR}/config.h"
)

# 直接添加选项
option(USE_CUDA "Using CUDA" on) # 默认为开启
# 使用 CMake 的语法可以控制文件级的编译
if(USE_CUDA)
    # command of compiling control if USE_CUDA defined
else
    # command of compiling control if USE_CUDA not defined
endif(USE_CUDA)
# ==========================


# ========== 生成 ==========
# 设置工程的子目录
add_subdirectory(src bin)  # src 中必须也有 CMakeLists.txt，实现了嵌套。
# src为源文件目录，bin为编译目标目录(bin, lib)，后者可不设置。
# src中的编译，通过其内的 CMakeLists.txt 控制，
# 进入子目录的 CMakeLists.txt, 不会改变 PROJECT_BINARY_DIR, PROJECT_SOURCE_DIR，
# 但 CMakeLists.txt 产生的另外两个变量会改变。
# CMAKE_CURRENT_SOURCE_DIR，CMakeLists.txt 所在处
# CMAKE_CURRRENT_BINARY_DIR，内部编译时为 CMakeLists.txt 所在处，外部编译时为编译目录

# 此外可以对编译后的可执行文件和库文件分别指定输出目录
#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
#set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# 添加库，默认为 static
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
# aux_source_directory() 的作用是将目录下的所有源文件保存为一个变量。
# aux_source_directory() 的替代方案是使用 file(GLOB)
#file(GLOB SOURCE_DIR ${PROJECT_SOURCE_DIR}/src/*.cpp)
# 该指令将所有符合模式的文件名保存在变量中

# CMake 有一些默认的头文件、库文件的搜索路径，也就是环境变量，保存在 CMAKE_INCLUDE_PATH 和 CMAKE_LIBRARY_PATH 中，可以使用 set() 进行修改。
# 但通常项目内部的头文件、库文件的搜索路径可以使用下面的指令设定。
# 指定头文件的搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)
# 指定库文件的搜索路径
# link_directories(${PROJECT_SOURCE_DIR}/lib)

# 生成执行文件
aux_source_directory(${PROJECT_SOURCE_DIR}/src SOURCE_DIR)
add_executable(CMakeTemplate ${SOURCE_DIR})

# 连接库
target_link_libraries(CMakeTemplate PUBLIC static_lib shared_lib)

# 其它为 target 指定的内容
# 为某个 target 指定头文件搜索目录，前面的 include_directories() 可以被所有的 target 使用
target_include_directories(CMakeTemplate "${PROJECT_BINARY_DIR}"/include)
# 为某个 target 指定库文件搜索目录，前面的 link_directories() 可以被所有的 target 使用
target_link_directories(CMakeTemplate "${PROJECT_BINARY_DIR}"/lib)
# 注意这两条指令都必须放在 target 被声明之后。
# ===============================


# ========== 使用外部库 ==========
# 使用外部库
find_package(OpenCV REQUIRED)
# find_package() 会读取 FindXXXX.cmake 等文件来设置外部库的属性。
# CMake 自带了很多常用库的 FindXXXX.cmake 文件；
# 如果自己提供 FindXXXX.cmake 文件，需要使用如下指令增加该文件查找目录，如 ./cmake/modules/
set(CMAKE_MODULE_PATH APPEND "${PROJECT_SOURCE_DIR}/cmake/modules/")
# 很显然 CMAKE_MODULE_PATH 存放了 .cmake 文件的搜索路径。

# 查找到外部库后会返回一些变量
# OpenCV_FOUND, OpenCV_INCLUDE_DIRS, OpenCV_LIBRARIES
if (OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
    target_link_libraries(SIFT ${OpenCV_LIBRARIES})
endif (OpenCV REQUIRED)
# ==============================


# ========== 安装 ==========
# 使用 install 可以将程序安装到系统中，多用于对外发布的程序或库。
# 不对外不发布的程序可以不写 install 部分；
# 或者如果不想把系统弄乱，也可以使用 install 将程序和相关文件复制到某个文件夹中。
# cmake 命令的参数 -DCMAKE_INSTALL_PREFIX 用于知道安装路径，默认为 /usr/local/

# 安装目标文件——二进制文件、动态库、静态库
install(TARGETS TargetName SharedLib StaticLib
        RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/release/bin
        LIBRARY DESTINATION ${CMAKE_BINARY_DIR}/release/lib
        ARCHIVE DESTINATION ${CMAKE_BINARY_DIR}/release/lib-static
)
# TARGETS 后跟随的名称，都是前面通过 add_executable() 或 add_library() 生成的目标。
# 注意这里会对库的文件名增加前缀，如 StaticLib 对应的文件为 libStaticLib.a。
# DESTINATION 为安装路径。

# 安装普通文件
install(FILES README.md licence.txt DESTINATION ${CMAKE_BINARY_DIR}/release)
# 默认文件权限 644
# 安装库对应的头文件也是用该指令。

# 安装脚本等可执行文件，这些文件不是前面使用 add_executable() 或 add_library() 生成的
install(PROGRAMS generator.sh DESTINATION ${CMAKE_BINARY_DIR}/release/bin)
# 默认文件权限 755，这是它与 install(FILE) 的不同之处。

# 安装整个目录
install(DIRECTORY res/ DESTINATION ${CMAKE_BINARY_DIR}/release/res)

# 实际的安装控制可能要复杂的多，在长期项目中可以考虑维护一个较好的安装脚本，用于 night build
# ==============================
# ============================================================
```

以上内容只是 CMake 的部分内容，其它的内容可以参考[官文文档](https://cmake.org/cmake/help/v3.18/)。
