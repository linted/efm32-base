#include <stddef.h>
#include "rtcdriver.h"
#include "i2cspm.h"

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
    I2CSPM_Init_TypeDef i2cspm_init = I2CSPM_INIT_DEFAULT;

    RTCDRV_Init();

    I2CSPM_Init(&i2cspm_init);

    RTCDRV_AllocateTimer( &id );
    RTCDRV_StartTimer( id, rtcdrvTimerTypeOneshot, 100, myCallback, NULL );
    return 0;
}
