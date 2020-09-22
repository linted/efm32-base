project(protocol)

string(TOLOWER ${DEVICE} DEVICE_L)

set(BLE_LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/bluetooth/ble_stack/linker/GCC/${DEVICE_L}.ld")

if (NOT EXISTS ${BLE_LINKER_SCRIPT})
    message("No bluetooth specific linker script defined, skipping protocol")
    set(HAS_PROTOCOL FALSE PARENT_SCOPE)
    return()
endif ()

set(HAS_PROTOCOL TRUE PARENT_SCOPE)

message("Found bluetooth specific linker script, using this instead:\n before: ${LINKER_SCRIPT}\n after: ${BLE_LINKER_SCRIPT}")

set(LINKER_SCRIPT ${BLE_LINKER_SCRIPT} PARENT_SCOPE)

add_library(${PROJECT_NAME} INTERFACE)

macro(import_lib target_name file)
    add_library(${target_name} STATIC IMPORTED)
    set_target_properties(${target_name}
        PROPERTIES
        IMPORTED_LOCATION ${file}
    )
    target_link_libraries(${target_name} INTERFACE emlib)
    target_link_libraries(${PROJECT_NAME} INTERFACE ${target_name})
endmacro()

import_lib(binapploader ${CMAKE_CURRENT_SOURCE_DIR}/bluetooth/lib/EFR32BG1B/GCC/binapploader.o)
import_lib(libbluetooth ${CMAKE_CURRENT_SOURCE_DIR}/bluetooth/lib/EFR32BG1B/GCC/libbluetooth.a)
import_lib(libmbedtls ${CMAKE_CURRENT_SOURCE_DIR}/bluetooth/lib/EFR32BG1B/GCC/libmbedtls.a)
import_lib(libpsstore ${CMAKE_CURRENT_SOURCE_DIR}/bluetooth/lib/EFR32BG1B/GCC/libpsstore.a)
import_lib(binapploader_nvm3 ${CMAKE_CURRENT_SOURCE_DIR}/bluetooth/lib/EFR32BG1B/GCC/binapploader_nvm3.o)
import_lib(libcoex ${CMAKE_CURRENT_SOURCE_DIR}/bluetooth/lib/EFR32BG1B/GCC/libcoex.a)
import_lib(libnvm3 ${CMAKE_CURRENT_SOURCE_DIR}/bluetooth/lib/EFR32BG1B/GCC/libnvm3.a)
import_lib(librail ${CMAKE_CURRENT_SOURCE_DIR}/bluetooth/lib/EFR32BG1B/GCC/librail.a)


target_link_libraries(libbluetooth INTERFACE sleep)

target_include_directories(${PROJECT_NAME} INTERFACE
        bluetooth/ble_stack/inc/common
        bluetooth/ble_stack/inc/soc)
