cmake_minimum_required (VERSION 2.6)
project (brightness)

set (CMAKE_CXX_STANDARD 14)

add_executable(brightness brightness.cpp)
target_link_libraries(brightness stdc++fs)

install(TARGETS brightness
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                    GROUP_READ GROUP_EXECUTE
                    WORLD_READ WORLD_EXECUTE
                    SETUID
        RUNTIME DESTINATION bin)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "-O3")
