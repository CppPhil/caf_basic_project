cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(CAF_basic_project VERSION 1.0.0)

add_executable(executable main.cpp)

set(CAF_URL https://github.com/actor-framework/actor-framework/archive/0.17.3.tar.gz)

set(TAR_PATH ${CAF_basic_project_SOURCE_DIR}/external/libcaf.tar.gz)

file(
    DOWNLOAD ${CAF_URL}
    ${TAR_PATH}
    STATUS status
)    

list(GET status 0 status_code)

if (NOT status_code EQUAL 0)
    message(FATAL_ERROR "error: downloading '${CAF_URL}' failed")
endif()

execute_process(
    COMMAND ${CMAKE_COMMAND} -E tar xfz ${TAR_PATH}
    WORKING_DIRECTORY ${CAF_basic_project_SOURCE_DIR}/external
    RESULT_VARIABLE rv
)

if (NOT rv EQUAL 0)
    message(FATAL_ERROR "error: could not extract libcaf!")
endif()                

execute_process(
    COMMAND bash ${CAF_basic_project_SOURCE_DIR}/build_caf.sh    
)
                   

set(CMAKE_MODULE_PATH ${CAF_basic_project_SOURCE_DIR}/cmake)
set(CAF_ROOT_DIR ${CAF_basic_project_BINARY_DIR}/external/libcaf)
find_package(CAF COMPONENTS core io)

target_include_directories(executable PRIVATE ${CAF_INCLUDE_DIRS})
target_link_libraries(executable ${CMAKE_DL_LIBS} ${CAF_LIBRARIES})

