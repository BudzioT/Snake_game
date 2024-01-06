cmake_minimum_required (VERSION 3.8)

project ("Snake_Game")

add_executable(Snake_Game "src/main.cpp" "src/headers/Game.h" "src/Game.cpp" "src/headers/assist.h" "src/assist.cpp"  "src/headers/Texture.h" "src/Texture.cpp")

find_package(SDL2 REQUIRED)
find_package(SDL2_IMAGE REQUIRED)

target_include_directories(Snake_Game PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(Snake_Game ${SDL2_LIBRARIES} SDL2_image::SDL2_image)