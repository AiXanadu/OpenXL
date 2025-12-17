# CMake最低版本号要求
cmake_minimum_required(VERSION 3.20)


# 项目名称
set(PROJECT_VERSION_MAJOR 7)
set(PROJECT_VERSION_MINOR 8)
set(PROJECT_VERSION_PATCH 3)
project(OpenXL VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})


# 输出提示信息
message(STATUS "CMAKE_SYSTEM : ${CMAKE_SYSTEM}")
message(STATUS "CMAKE_INSTALL_PREFIX : ${CMAKE_INSTALL_PREFIX}")
message(STATUS "CMAKE_C_COMPILER : ${CMAKE_C_COMPILER}")
message(STATUS "CMAKE_CXX_COMPILER : ${CMAKE_CXX_COMPILER}")


# 设置模块搜索路径
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_INSTALL_PREFIX}/lib/cmake)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ENV_SDK_LIBRARY}/cmake)
if (WIN32 AND CMAKE_SIZEOF_VOID_P EQUAL 4)
	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} $ENV{DIR_QT_DLL_x86}/lib/cmake)
else ()
	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} $ENV{DIR_QT_DLL_x64}/lib/cmake)
endif ()
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_MODULE_PATH})
message(STATUS "CMAKE_MODULE_PATH : ${CMAKE_MODULE_PATH}")
message(STATUS "CMAKE_PREFIX_PATH : ${CMAKE_PREFIX_PATH}")


# C++支持
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)


 # 配置文件
configure_file("${CMAKE_SOURCE_DIR}/config/VersionInfo.rc.in" "${CMAKE_BINARY_DIR}/VersionInfo.rc")


# 添加资源文件
set(CMAKE_RC_DIR ${PROJECT_SOURCE_DIR}/resources)
set(QRC_SOURCE_FILES ${CMAKE_RC_DIR}/main.qrc)
set(WRC_SOURCE_FILES ${CMAKE_RC_DIR}/main.rc)


# 设置编译环境
if (MSVC)
	add_compile_options(/utf-8 /W4 /WX /wd4125 /wd4505)
else()
	add_compile_options(-Wall)
endif()
message(STATUS "CMAKE_CXX_FLAGS_DEBUG : ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "CMAKE_CXX_FLAGS_RELEASE : ${CMAKE_CXX_FLAGS_RELEASE}")


# 设置忽略路径
set(CMAKE_IGNORE_PATH ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME})
message(STATUS "CMAKE_IGNORE_PATH : ${CMAKE_IGNORE_PATH}")


# 项目依赖
include_directories(${PROJECT_SOURCE_DIR}/include)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)


# 设置自动生成QT文件
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMATIC ON)
set(CMAKE_AUTODOC ON)
set(CMAKE_AUTOCRAT ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


# 设置宏
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_definitions(-DXL_BUILD_DEBUG)
else ()
	add_definitions(-DXL_BUILD_RELEASE)
endif ()


# 头文件搜索目录
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${ENV_SDK_INCLUDE})
include_directories(${CMAKE_INSTALL_PREFIX}/include)


# 链接库搜索目录
link_directories(${ENV_SDK_LIBRARY})
link_directories(${CMAKE_INSTALL_PREFIX}/lib)


# 包含源文件
file(GLOB_RECURSE SRC_SOURCE "${PROJECT_SOURCE_DIR}/source/*.cpp")
if(MSVC)
	list(APPEND SRC_RC ${CMAKE_BINARY_DIR}/VersionInfo.rc)
endif()


# 指定可执行程序输出目录
set(EXE_RUNTIME_DIRECTORY ${PROJECT_SOURCE_DIR}/binary)
if(WIN32)
	if(CMAKE_SIZEOF_VOID_P EQUAL 4)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${EXE_RUNTIME_DIRECTORY}/winnt-x86/debug)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${EXE_RUNTIME_DIRECTORY}/winnt-x86/release)
	else()
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${EXE_RUNTIME_DIRECTORY}/winnt-x64/debug)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${EXE_RUNTIME_DIRECTORY}/winnt-x64/release)
	endif()
elseif(APPLE)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${EXE_RUNTIME_DIRECTORY}/darwin-x64/debug/${PROJECT_NAME}.app/Contents/MacOS)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${EXE_RUNTIME_DIRECTORY}/darwin-x64/release/${PROJECT_NAME}.app/Contents/MacOS)
elseif(UNIX)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${EXE_RUNTIME_DIRECTORY}/linux-x64/debug)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${EXE_RUNTIME_DIRECTORY}/linux-x64/release)
endif()


# 链接库
if (WIN32)
	link_libraries(Ws2_32.lib)
	link_libraries(Dwmapi.lib)
	link_libraries(urlmon.lib)
	link_libraries(wininet.lib)
	link_libraries(Shlwapi.lib)
elseif (MINGW)
	link_libraries(Ws2_32)
	link_libraries(Dwmapi)
	link_libraries(urlmon)
	link_libraries(wininet)
	link_libraries(Shlwapi)
endif ()
link_libraries(Qt5::Core)
link_libraries(Qt5::Gui)
link_libraries(Qt5::Widgets)
link_libraries(Qt5::Network)


# 设置Mac RPATH
if (APPLE)
	set(CMAKE_INSTALL_RPATH "@executable_path/../Frameworks")
	set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)
endif ()


# 以下为 VS 参数
# /MANIFEST /NXCOMPAT /DEBUG /MACHINE:X86 /SAFESEH /INCREMENTAL /SUBSYSTEM:WINDOWS /MANIFESTUAC:"level='requireAdministrator' uiAccess='false'"
# /ManifestFile:"Debug\ShaLouD.exe.intermediate.manifest" /ERRORREPORT:PROMPT /NOLOGO /TSAWARE /LIBPATH:"\lib" /TLBID:1
# 设置 Windows 链接标志
message(STATUS "CMAKE_EXE_LINKER_FLAGS : ${CMAKE_EXE_LINKER_FLAGS}")
if (WIN32)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:\"mainCRTStartup\"")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\"")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /TSAWARE")
endif ()
message(STATUS "CMAKE_EXE_LINKER_FLAGS : ${CMAKE_EXE_LINKER_FLAGS}")



# 构建
add_executable(${PROJECT_NAME} WIN32 ${SRC_SOURCE} ${SRC_RC} ${QRC_SOURCE_FILES} ${WRC_SOURCE_FILES})


# 设置项目属性
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX -d)


# 设置安装文件(可执行文件)
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
