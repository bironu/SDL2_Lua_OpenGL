cmake_minimum_required(VERSION 3.0.0)
project(sdl2_lua_opengl VERSION 0.1.0)

#include(CTest)
#enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

add_definitions(-DGL_GLEXT_PROTOTYPES)

#include(FindPkgConfig)
find_package(SDL2 REQUIRED)
# find_package(SDL2_image REQUIRED)
# find_package(SDL2_mixer REQUIRED)
# find_package(SDL2_ttf REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Lua51 REQUIRED)

include_directories(/usr/local/include/)
include_directories(${OPENGL_INCLUDE_DIRS})
#include_directories(${SDL2_INCLUDE_DIRS})
#include_directories(${SDL2_MIXER_INCLUDE_DIRS})
#include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
#include_directories(${SDL2_TTF_INCLUDE_DIRS})
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
 
# clang依存?
#set(CMAKE_CXX_FLAGS "-std=c++14 -stdlib=libc++")
#set(CMAKE_CXX_FLAGS "-std=c++14")
set(CMAKE_CXX_STANDARD 17)

# 実行ファイルを作る方法を指定
add_executable(${PROJECT_NAME} ${root_files})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/app)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/geo)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/gl)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/gl/widget)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/gl/view)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/resources)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/scene)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/scene/opening)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/scene/menu)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/scene/chapter05)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/sdl)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/task)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/math)
 
# リンクするライブラリを指定
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
#target_link_libraries(${PROJECT_NAME} ${SDL2_TTF_LIBRARIES})
#target_link_libraries(${PROJECT_NAME} ${SDL2_IMAGE_LIBRARIES})
#target_link_libraries(${PROJECT_NAME} ${SDL2_MIXER_LIBRARIES})
target_link_libraries(${PROJECT_NAME} "-L/usr/local/lib -lSDL2_image")
target_link_libraries(${PROJECT_NAME} "-L/usr/local/lib -lSDL2_mixer")
target_link_libraries(${PROJECT_NAME} "-L/usr/local/lib -lSDL2_ttf")
target_link_libraries(${PROJECT_NAME} ${LUA_LIBRARIES})

#libSDL2.a
#libSDL2_image.a
#libSDL2_mixer.a
#libSDL2_ttf.a

target_link_libraries(${PROJECT_NAME} app)
target_link_libraries(${PROJECT_NAME} geo)
target_link_libraries(${PROJECT_NAME} gl)
target_link_libraries(${PROJECT_NAME} gl_widget)
target_link_libraries(${PROJECT_NAME} gl_view)
target_link_libraries(${PROJECT_NAME} resources)
target_link_libraries(${PROJECT_NAME} scene)
target_link_libraries(${PROJECT_NAME} scene_opening)
#target_link_libraries(${PROJECT_NAME} scene_menu)
#target_link_libraries(${PROJECT_NAME} scene_chapter05)
target_link_libraries(${PROJECT_NAME} sdl)
target_link_libraries(${PROJECT_NAME} task)
#target_link_libraries(${PROJECT_NAME} math)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/app)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/gl)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/gl/widget)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/gl/view)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/resources)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/scene)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/scene/opening)
#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/scene/menu)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/scene/chapter05)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/sdl)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/task)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/math)
link_directories(/usr/local/lib)

