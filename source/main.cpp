#include "rtcdriver.h"
#include <stddef.h>

int i = 0;

RTCDRV_TimerID_t id;

void myCallback( RTCDRV_TimerID_t id, void * user )
{
    (void) user; // unused argument in this example
    i++;
    if ( i < 10 ) {
        // Restart timer
        RTCDRV_StartTimer( id, rtcdrvTimerTypeOneshot, 100, myCallback, NULL );
    }
}

int main( void )
{
    // Initialization of the RTCDRV driver.
    RTCDRV_Init();
    // Reserve a timer.
    RTCDRV_AllocateTimer( &id );
    // Start a oneshot timer with 100 millisecond timeout.
    RTCDRV_StartTimer( id, rtcdrvTimerTypeOneshot, 100, myCallback, NULL );
    return 0;
}
