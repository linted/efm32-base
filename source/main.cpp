#include <stddef.h>
#include "rtcdriver.h"
#include "leddriver.h"

#include "native_gecko.h"

#include "em_chip.h"
#include "em_emu.h"
#include "em_cmu.h"

#define MAX_CONNECTIONS 1

static LEDDriver *led_driver;

static RTCDRV_TimerID_t id;
static bool on = 0;
static bool triggered = false;

void myCallback( RTCDRV_TimerID_t id, void * user )
{
    (void) user; // unused argument in this example
    (void) id;

    triggered = true;
}

static uint8_t bluetooth_stack_heap[DEFAULT_BLUETOOTH_HEAP(MAX_CONNECTIONS)];
static gecko_configuration_t g_gecko_config = {
    .config_flags = 0,
    .sleep.flags = SLEEP_FLAGS_DEEP_SLEEP_ENABLE,
    .bluetooth.max_connections = MAX_CONNECTIONS,
    .bluetooth.heap = bluetooth_stack_heap,
    .bluetooth.heap_size = sizeof(bluetooth_stack_heap),
    .bluetooth.sleep_clock_accuracy = 100, //ppm
    .gattdb=&bg_gattdb_data,
    .ota.flags = 0,
    .ota.device_name_len = 3,
    .ota.device_name_ptr = "OTA",
    .max_timers = 4,
};

int main( void )
{
    CHIP_Init(); // THIS MUST GO FIRST
    RTCDRV_Init();
    CMU_ClockEnable(cmuClock_GPIO, true); // Enable this so that we can write

    gecko_init(&g_gecko_config);
    

    LEDDriver _main_led_driver;
    led_driver = &_main_led_driver;

    RTCDRV_AllocateTimer( &id );
    RTCDRV_StartTimer( id, rtcdrvTimerTypePeriodic, 5000, myCallback, NULL );

    for (;;) {
        EMU_EnterEM1();

        if (triggered) {
            if (on) {
                led_driver->global_on(false);
                on = false;
            } else {
                led_driver->global_off(false);
                on = true;
            }
            triggered = false;
        }
    }
    return 0;
}
