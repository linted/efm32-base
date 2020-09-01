#include <stddef.h>
#include "rtcdriver.h"
#include "leddriver.h"

#include "em_emu.h"

static LEDDriver led_driver;

static RTCDRV_TimerID_t id;
static bool on = 0;

void myCallback( RTCDRV_TimerID_t id, void * user )
{
    (void) user; // unused argument in this example
    (void) id;

    if (on) {
        led_driver.set_led(0, 100, 100, 0);
        on = false;
    } else {
        led_driver.set_led(0, 0, 0, 0);
        on = true;
    }
}

int main( void )
{
    RTCDRV_Init();

    RTCDRV_AllocateTimer( &id );
    RTCDRV_StartTimer( id, rtcdrvTimerTypePeriodic, 100, myCallback, NULL );

    for (;;) {
        EMU_EnterEM1();
    }
    return 0;
}
