# CMake Script

Makefile 可以控制编译的过程，但很难跨平台使用，CMake可以脱离平台，在不同平台上控制编译的过程。

cmake的命令行工具介绍如下：
```bash
# Don't build the project in the source path, make a new directory for building
$ mkdir build && cd build
$ cmake ..
$ make && make install # unix system 
$ cmake --build && cmake --install # windows system
```

## 不依赖外部库的项目
```cmake
# CMakeLists.txt
cmake_minimum_required(VERSION 3.0)
project(ProjectName) # 会生成一个变量 PROJECT_NAME

message("Start build the project.")

# 设置include文件夹，当有小型的3rdparty库时使用
include_directories(include)
# 设置lib文件夹，非自己构建的库文件会在这里查找
link_libraries(lib)
# 添加子文件夹，CMake会在子文件夹里寻找CMakeLists.txt
add_subdirectory(src/static)
add_subdirectory(src/shared)

# 设置目标文件存放位置
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

# CMake还有很多语法可以用：
#    - if()-elseif()-else()-endif()
#    - foreach(var items)-endforeach()
#    - foreach(var RANGE <start> <stop> [step])-endforeach()
#    - while()-endwhile()
#    - continue()-break()
#    - function(name [args ...])-return()-endfunction()

# 每个库的源文件都应放在自己专属的文件夹下，指令放在自己文件夹的CMakeLists.txt即可
# generate static library by default
aux_source_directory(src/statc STATIC_LIB_SRC_LIST)
add_library(StaticLibName ${STATIC_LIB_SRC_LIST})
# generate shared library
aux_source_directory(src/shared SHARED_LIB_SRC_LIST)
add_library(SharedLibName SHARED ${SHARED_LIB_SRC_LIST})
# generate object library
add_library(ObjectLibName OBJECT obj.cpp)
# object文件只是一种中间文件，但可以连接到其它类型的库上，使用target_link_libraries()
target_link_libraries(StaticLibName ObjectLibName)

# generate the executable file 
aux_source_library(src TARGET_SRC_LIST)
add_executable(TargetName ${TARGET_SRC_LIST})
# link
target_link_libraries(TargetName StaticLibName SharedLibName)
target_link_libraries(TargetName Lib3rdparty)
```

## 使用外部库
```cmake
# 在系统中查找依赖库，这种方式适合流行的大型库如OpenCV、scikit等
# find_package需要FindXXX.cmake文件的支持，该文件存放在modules文件夹中
set(CMAKE_MODULE_PATH APPEND "${PROJECT_SOURCE_DIR}/cmake/modules/")
# find_package会生成一系列和此库相关的变量如XXX_FOUND，具体的变量名称见FindXXX.cmake
find_package(XXX REQUIRED)
# CMake自带了很多查找外部库的命令，可以查阅使用

# 将外部库的内容添加到项目中
include_directories(XXX_INCLUDE_DIR)
link_directories(XXX_LIBRARY_DIR)
```

## 安装
```cmake
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