#include <stddef.h>
#include "rtcdriver.h"
#include "leddriver.h"

#include "em_emu.h"

static LEDDriver led_driver;

RTCDRV_TimerID_t id;

void myCallback( RTCDRV_TimerID_t id, void * user )
{
    (void) user; // unused argument in this example
    (void) id;

    led_driver.toggle_led(1);
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
