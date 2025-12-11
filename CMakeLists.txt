cmake_minimum_required(VERSION 3.14)
project(GatewayProtocol LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ---- Sources ----
# Adjust according to your actual files
set(SOURCES
    src/main.cpp
    src/Protocol.cpp
    src/Packet.cpp
    src/Router.cpp
    src/Logger.cpp
)

add_executable(gateway_protocol ${SOURCES})

target_include_directories(gateway_protocol PRIVATE include)

# If you simulate networking and use any extra libs, link them here.
# Example for POSIX sockets (if needed):
# if (UNIX)
#     target_link_libraries(gateway_protocol PRIVATE pthread)
# endif()
