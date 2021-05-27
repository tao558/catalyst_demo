cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(CATALYST_DEMO)

find_package(catalyst
  REQUIRED
  COMPONENTS SDK)

set(CMAKE_SKIP_BUILD_RPATH ON)
add_library(demo_implementation SHARED
 demo_implementation.cxx)
catalyst_library(TARGET demo_implementation)

set(data_dump_directory "${CMAKE_CURRENT_BINARY_DIR}/data_dumps")
file(MAKE_DIRECTORY ${data_dump_directory})


string(CONCAT setup_demo_content
              "export DEMO_IMPLEMENTATION_LIB_DIRECTORY=$<TARGET_FILE_DIR:demo_implementation>"
              "\n"
              "export DEMO_CATALYST_DATA_DUMP_DIRECTORY=${data_dump_directory}"
              "\n"
              "export OLD_LD_LIBRARY_PATH=$ENV{LD_LIBRARY_PATH}")

file(GENERATE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/setup_demo.sh"
     CONTENT ${setup_demo_content}
     )

add_executable(demo_driver demo_driver.cxx)

target_link_libraries(demo_driver
  PRIVATE
    catalyst::catalyst)
