# Base EFM32 CMake file
#
# This can be used as is as a project base, or by adding the efm32-base
# repository as a submodule to another project, copying this CMakeLists file
# to the top level directory, and updating the BASE_LOCATION variable to reflect this
# change
#
## Copyright (c) 2016 Ryan Kurte
# This file is covered under the MIT license available at: https://opensource.org/licenses/MIT

###### Project Environment #####

# Set minimum CMake version
cmake_minimum_required(VERSION 2.8.4)

# Optional verbose mode, uncomment or pass in -DCMAKE_VERBOSE_MAKEFILE=ON
# set(CMAKE_VERBOSE_MAKEFILE ON)

set(BASE_LOCATION ${CMAKE_CURRENT_SOURCE_DIR})

# Set the compiler (must be prior to project setup)
include(${BASE_LOCATION}/toolchain/arm-gcc.cmake)

##### Project Setup #####

# Configure project and languages
project(efm32-test C CXX ASM)
set(DEVICE BGM113A256V2)
set(FLASH_ORIGIN 0x00000000)
set(FLASH_LENGTH 0x40000)
set(RAM_ORIGIN 0x20000000)
set(RAM_LENGTH 0x7bff)

# Set build
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE DEBUG)
endif ()

##### Modules #####

# Libraries can be added to the LIBS variable
# or manually included here.

# Add base libs (emlib, CMSIS, device files)
include(${BASE_LOCATION}/toolchain/efm32-base.cmake)
include(${BASE_LOCATION}/cmake/print_target_properties.cmake)

add_subdirectory(${BASE_LOCATION}/cmsis)
add_subdirectory(${BASE_LOCATION}/emlib)
add_subdirectory(${BASE_LOCATION}/device)
add_subdirectory(${BASE_LOCATION}/protocol)
add_subdirectory(${BASE_LOCATION}/hardware)

# This is normally set in efm32-base.cmake, but libraries may modify it so set
# it after libraries/subdirectories have been added
set(CMAKE_EXE_LINKER_FLAGS "${COMMON_DEFINITIONS} -Xlinker -T${LINKER_SCRIPT} -Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.map -Wl,--gc-sections -Wl,-v")

##### Files #####

# Add project headers
include_directories(${BASE_LOCATION}/include)

# Generate executable and link
add_executable(${PROJECT_NAME}
        source/main.c
        #source/randomnumgen.cpp
        #source/formula.cpp
        )

add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/libmain.a
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/rs_source/src/lib.rs
    COMMAND cargo build --target "thumbv7m-none-eabi" --target-dir ${CMAKE_CURRENT_BINARY_DIR}/rs_main -Z unstable-options --out-dir ${CMAKE_CURRENT_BINARY_DIR}/rs_artifacts
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/rs_source
    )

add_custom_target(rs_libmain_build
    DEPENDS ${CMAKE_BINARY_DIR}/libmain.a
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/rs_source/src/lib.rs
    )

add_library(rs_main STATIC IMPORTED)
set_target_properties(rs_main
    PROPERTIES
    IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/rs_artifacts/librs_source.a)

# Generate executable and link
add_dependencies(${PROJECT_NAME} rs_libmain_build)

efm32_configure_linker_addresses(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} ${LIBS} emlib cmsis device rs_main)

# print_target_properties(${PROJECT_NAME})

# Link optional libraries if available
if (${HAS_HARDWARE})
    target_link_libraries(${PROJECT_NAME} hardware)
endif ()

if (${HAS_PROTOCOL})
    target_link_libraries(${PROJECT_NAME} protocol)
endif ()

##### Post build #####

# Add post build commands
include(${BASE_LOCATION}/toolchain/post-build.cmake)

# Add JLink commands
include(${BASE_LOCATION}/toolchain/jlink.cmake)

##### CMake debug prints #####
if (CMAKE_VERBOSE_MAKEFILE)
    print_debug_info()
endif()
