#include "gecko_configuration.h"
#include "gatt_db.h"
#include "native_gecko.h"

#include "globals.h"

static uint8_t bluetooth_stack_heap[DEFAULT_BLUETOOTH_HEAP(MAX_CONNECTIONS)];
const gecko_configuration_t g_gecko_config = {
    .config_flags = 0,
    .sleep = {.flags = SLEEP_FLAGS_DEEP_SLEEP_ENABLE},
    .bluetooth = {
        .max_connections = MAX_CONNECTIONS,
        .heap = bluetooth_stack_heap,
        .heap_size = sizeof(bluetooth_stack_heap),
        .sleep_clock_accuracy = 100, //ppm
    },
    .gattdb=&bg_gattdb_data,
    .ota = {
        .flags = 0,
        .device_name_len = 3,
        .device_name_ptr = "OTA",
    },
    .max_timers = 4,
    .rf = {
        .flags = (1 << 0),
        .antenna = 1,
    },
};
