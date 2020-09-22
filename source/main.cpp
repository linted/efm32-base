#include <stddef.h>
#include "rtcdriver.h"
#include "leddriver.h"
#include "i2cdriver.h"

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
    led_driver->set_led(0x1, 0x00, 0x00, 0x00);
    led_driver->set_led(0x0, 0xff, 0xff, 0xff);


    RTCDRV_AllocateTimer( &id );
    RTCDRV_StartTimer( id, rtcdrvTimerTypePeriodic, 500, myCallback, NULL );

    for (;;) {
        EMU_EnterEM1();

        if (triggered) {
            led_driver->do_single_chase();
            triggered = false;
        }
    }
    return 0;
}
