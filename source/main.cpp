#include <stddef.h>
#include "rtcdriver.h"
#include "leddriver.h"

#include "em_chip.h"
#include "em_emu.h"
#include "em_cmu.h"

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
    CHIP_Init();
    RTCDRV_Init();

    LEDDriver _main_led_driver;
    led_driver = &_main_led_driver;

    CMU_ClockEnable(cmuClock_GPIO, true);

    RTCDRV_AllocateTimer( &id );
    RTCDRV_StartTimer( id, rtcdrvTimerTypePeriodic, 5000, myCallback, NULL );

    for (;;) {
        EMU_EnterEM1();

        if (triggered) {
            if (on) {
                led_driver->set_led(0, 100, 100, 0);
                on = false;
            } else {
                led_driver->set_led(0, 0, 0, 0);
                on = true;
            }
            triggered = false;
        }
    }
    return 0;
}
