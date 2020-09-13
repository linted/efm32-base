#include <stddef.h>
#include "rtcdriver.h"
#include "leddriver.h"

#include "native_gecko.h"
#include "gecko_configuration.h"

#include "em_chip.h"
#include "em_emu.h"
#include "em_cmu.h"

#include "gatt_db.h"
#include "globals.h"

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
