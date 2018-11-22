cmake_minimum_required(VERSION 3.12)
project(SQLiteCppExample)

set(SQLITECPP_RUN_CPPCHECK OFF CACHE BOOL "" FORCE)
set(SQLITECPP_RUN_CPPLINT OFF CACHE BOOL "" FORCE)
set(MAIN_TARGET_NAME SQLiteCppExample)

add_subdirectory(SQLiteCpp)
add_executable(${MAIN_TARGET_NAME} src/main.cpp)

if(UNIX AND NOT APPLE)
  # Removed linking to pthread, more detail:
  # https://github.com/tstack/lnav/issues/153
  # https://stackoverflow.com/questions/33697072/why-is-pthread-necessary-for-usage-of-stdthread-in-gcc-and-clang
  target_link_libraries(${MAIN_TARGET_NAME} SQLiteCpp sqlite3 dl)
else()
  target_link_libraries(${MAIN_TARGET_NAME} SQLiteCpp sqlite3)
endif()
