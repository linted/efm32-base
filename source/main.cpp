#include <stddef.h>
#include "rtcdriver.h"
#include "leddriver.h"
#include "i2cdriver.h"

#include "native_gecko.h"

#include "em_chip.h"
#include "em_emu.h"
#include "em_cmu.h"

static LEDDriver *led_driver;

static RTCDRV_TimerID_t id;
static bool on = false;
static bool triggered = false;

#if 0
static const gecko_configuration_t g_gecko_config = {
  .config_flags = 0,
  .sleep.flags = SLEEP_FLAGS_DEEP_SLEEP_ENABLE,
  .bluetooth.max_connections = MAX_CONNECTIONS,
  .bluetooth.heap = g_bluetooth_heap,
  .bluetooth.heap_size = sizeof(g_bluetooth_heap),
  .bluetooth.sleep_clock_accuracy = 100,
  .gattdb = &bg_gattdb_data,
  .ota.flags = 0,
  .ota.device_name_len = 11,
  .ota.device_name_ptr = "BLETALK_OTA",
  .pa.config_enable = 1,
  .pa.input = GECKO_RADIO_PA_INPUT_DCDC,
};
#endif

void myCallback( RTCDRV_TimerID_t id, void * user )
{
    (void) user; // unused argument in this example
    (void) id;

    triggered = true;
}

int main( void )
{
    CHIP_Init(); // THIS MUST GO FIRST
    RTCDRV_Init();
    CMU_ClockEnable(cmuClock_GPIO, true); // Enable this so that we can write

    // gecko_configuration_t gecko_config;
    // memset(&gecko_config, 0, sizeof(gecko_config));

    // gecko_init(&gecko_config);
    

    LEDDriver _main_led_driver;
    led_driver = &_main_led_driver;
    led_driver->set_led(0x0, 0x00, 0x00, 0x00);
    led_driver->set_led(0x1, 0xff, 0xff, 0xff);


    RTCDRV_AllocateTimer( &id );
    RTCDRV_StartTimer( id, rtcdrvTimerTypePeriodic, 5000, myCallback, NULL );

    int blah = 0;
    for (;;) {
        EMU_EnterEM1();

        if (triggered) {
            if (on) {
                if (blah == 0) {
                    led_driver->select_all(204);
                    //led_driver->select_color0();
                    blah = 1;
                } else if (blah == 1) {
                    //led_driver->select_color0();
                    led_driver->select_all(170);
                    blah = 2;
                } else {
                    //led_driver->select_color0();
                    led_driver->select_all(153);
                    blah = 0;
                }
                led_driver->global_on(true);
                on = false;
            } else {
                led_driver->global_off(true);
                on = true;
            }
            triggered = false;
        }

        if (i2c::Driver::instance()->needs_processing()) {
            i2c::Driver::instance()->process();
        }
    }
    return 0;
}
