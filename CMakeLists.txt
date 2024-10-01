cmake_minimum_required(VERSION 3.10)

project(DBMS)

set(CMAKE_CXX_STANDARD 17)

# Include Directories
include_directories(include)

# Add Source Files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Find and Link PSQL
find_package(PostgreSQL REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets) 

add_executable(DBMS ${SOURCES})
target_link_libraries(DBMS Qt6::Widgets PostgreSQL::PostgreSQL)


