cmake_minimum_required(VERSION 3.10)
project(SFMLProject)

set(CMAKE_CXX_STANDARD 17)

# set SFML path
set(SFML_DIR "C:/SFML/lib/cmake/SFML")

# find SFML library
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(SFMLProject main.cpp)

#link SFML library
target_link_libraries(SFMLProject sfml-graphics sfml-window sfml-system)
