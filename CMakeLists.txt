cmake_minimum_required(VERSION 3.0)
project(boost_asio_client_server)
add_compile_options(-std=c++17)
#add_compile_options(-static-libstdc++)

#Flags: -lc++abi -std=c++11
#For clang: -stdlib=libc++
#set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -stdlib=libc++")

if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
endif()

add_executable(asio_server asio_server.cpp)
target_link_libraries(asio_server ${CONAN_LIBS})

add_executable(asio_client asio_client.cpp)
target_link_libraries(asio_client ${CONAN_LIBS})

