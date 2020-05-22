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

set( BLE_LIBRARIES
    ${CMAKE_CURRENT_SOURCE_DIR}/bluetooth/lib/EFR32BG1B/GCC/binapploader.o
    ${CMAKE_CURRENT_SOURCE_DIR}/bluetooth/lib/EFR32BG1B/GCC/libbluetooth.a
    ${CMAKE_CURRENT_SOURCE_DIR}/bluetooth/lib/EFR32BG1B/GCC/libmbedtls.a
    ${CMAKE_CURRENT_SOURCE_DIR}/bluetooth/lib/EFR32BG1B/GCC/libpsstore.a
    ${CMAKE_CURRENT_SOURCE_DIR}/bluetooth/lib/EFR32BG1B/GCC/binapploader_nvm3.o
    ${CMAKE_CURRENT_SOURCE_DIR}/bluetooth/lib/EFR32BG1B/GCC/libcoex.a
    ${CMAKE_CURRENT_SOURCE_DIR}/bluetooth/lib/EFR32BG1B/GCC/libnvm3.a
    ${CMAKE_CURRENT_SOURCE_DIR}/bluetooth/lib/EFR32BG1B/GCC/librail.a
)

target_link_libraries(${PROJECT_NAME} INTERFACE ${BLE_LIBRARIES})

target_include_directories(${PROJECT_NAME} INTERFACE
        bluetooth/ble_stack/inc/common
        protocol/bluetooth/ble_stack/inc/soc)