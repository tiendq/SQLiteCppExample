cmake_minimum_required(VERSION 3.12)
project(SQLiteCppExample)

add_subdirectory(SQLiteCpp)
add_executable(${PROJECT_NAME} src/main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE SQLiteCpp/include)

if(UNIX AND NOT APPLE)
  # Removed linking to pthread, more detail:
  # https://github.com/tstack/lnav/issues/153
  # https://stackoverflow.com/questions/33697072/why-is-pthread-necessary-for-usage-of-stdthread-in-gcc-and-clang
  target_link_libraries(${PROJECT_NAME} SQLiteCpp sqlite3 dl)
else()
  target_link_libraries(${PROJECT_NAME} SQLiteCpp sqlite3)
endif()
