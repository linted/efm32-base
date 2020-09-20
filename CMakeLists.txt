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
project(badge-firmware C CXX ASM)
set(DEVICE BGM113A256V2)
set(FLASH_ORIGIN 0x00000000)
set(FLASH_LENGTH 0x40000)
set(RAM_ORIGIN 0x20000000)
set(RAM_LENGTH 0x7bff)

## ${DEVICE} sets the target specific model name
#if (NOT DEVICE)
#    set(DEVICE EFM32G210F128)
#    # set(DEVICE BGM13P22F512GA)
#    # set(BOARD BRD4306A)
#    # set(BLE_LIB EFR32BG13P)
#endif ()

# ${JLINK_DEVICE} device model setting specifically for JLink. (Defaults to ${DEVICE} when not set)
# set(JLINK_DEVICE EFM32TG11BXXXF128)

# When ${JLINK_SERVER_IP} is set, JLink will try to connect over IP to a JLink server
# set(JLINK_SERVER_IP 127.0.0.1)

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
add_subdirectory(${BASE_LOCATION}/emdrv)

# This is normally set in efm32-base.cmake, but libraries may modify it so set
# it after libraries/subdirectories have been added
set(CMAKE_EXE_LINKER_FLAGS "${COMMON_DEFINITIONS} -Xlinker -T${LINKER_SCRIPT} -Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.map -Wl,--gc-sections -Wl,-v")

##### Files #####

# Add project headers
include_directories(${BASE_LOCATION}/include)

# Generate executable and link

set(C_SRCS
    source/gatt_db.c
    source/i2cspm.c
    source/globals.c)

set(CXX_SRCS
    source/main.cpp
    source/leddriver.cpp
    source/common_alloc.cpp
    source/bgmdevice.cpp
    source/i2cdriver.cpp
    source/i2cdevice.cpp
    source/i2csequence.cpp)

set_source_files_properties(${CXX_SRCS}
    PROPERTIES
    COMPILE_FLAGS "-fno-exceptions -fno-rtti -fno-unwind-tables -Wno-register")

add_executable(${PROJECT_NAME}
    ${C_SRCS}
    ${CXX_SRCS}
    )

target_compile_options(${PROJECT_NAME} PRIVATE    
    -Wall -Wextra -Werror
    -Wno-type-limits)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    CXX_STANDARD 17)

efm32_configure_linker_addresses(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} ${LIBS} cmsis device emlib rtcdrv )

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
