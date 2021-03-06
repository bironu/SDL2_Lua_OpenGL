cmake_minimum_required(VERSION 3.0.0)
project(sdl2_lua_opengl VERSION 0.1.0)

#include(CTest)
#enable_testing()

#add_executable(sdl2_lua_opengl
# main.cpp
# )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)

#include(FindPkgConfig)
#pkg_search_module(SDL2 REQUIRED sdl2)
#pkg_search_module(SDL2Image REQUIRED SDL2_image>=2.0.0)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Lua51 REQUIRED)


include_directories(SYSTEM)
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_MIXER_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_TTF_INCLUDE_DIRS})
include_directories(${LUA_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

# コンパイル対象のソース一覧を作成
#file(GLOB util_files src/util/*.cpp)
#file(GLOB project_files src/${PROJECT_NAME}/*.cpp src/${PROJECT_NAME}/*/*.cpp)
file(GLOB root_files ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
 
# オブジェクトファイルを作るソースを指定
#add_library(util OBJECT ${util_files})
#add_library(project OBJECT ${project_files})
#add_library(root OBJECT ${root_files})
 
# Mac依存
#link_directories(/usr/local/lib)
# clang依存?
#set(CMAKE_CXX_FLAGS "-std=c++14 -stdlib=libc++")
#set(CMAKE_CXX_FLAGS "-std=c++14")
set(CMAKE_CXX_STANDARD 17)

# 実行ファイルを作る方法を指定
add_executable(${PROJECT_NAME}
 ${root_files}
# $<TARGET_OBJECTS:root>
#$<TARGET_OBJECTS:project>
# $<TARGET_OBJECTS:util>
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/app)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/gl)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/gl/widget)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/resource)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/scene)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/scene/opening)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/scene/menu)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/sdl)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/sdl/widget)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/task)
 
# リンクするライブラリを指定
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SDL2_TTF_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SDL2_MIXER_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${LUA_LIBRARIES})

target_link_libraries(${PROJECT_NAME} app)
target_link_libraries(${PROJECT_NAME} gl)
target_link_libraries(${PROJECT_NAME} gl_widget)
target_link_libraries(${PROJECT_NAME} resource)
target_link_libraries(${PROJECT_NAME} scene)
target_link_libraries(${PROJECT_NAME} scene_opening)
target_link_libraries(${PROJECT_NAME} scene_menu)
target_link_libraries(${PROJECT_NAME} sdl)
target_link_libraries(${PROJECT_NAME} sdl_widget)
target_link_libraries(${PROJECT_NAME} task)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/app)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/gl)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/gl/widget)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/resource)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/scene)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/scene/opening)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/scene/menu)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/sdl)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/sdl/widget)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/task)
