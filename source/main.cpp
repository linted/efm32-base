//EFM32 blink test

#ifndef LED_PIN
#define LED_PIN     4
#endif
#ifndef LED_PORT
#define LED_PORT    gpioPortA
#endif

#include <stdint.h>
#include <stdbool.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "em_rtcc.h"
#include "em_i2c.h"

static uint64_t g_ticks = 0;

void RTCC_IRQHandler() {
    ++g_ticks;
    RTCC_StatusClear();
}

/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{
    RTCC_Init_TypeDef rtcc_init = RTCC_INIT_DEFAULT;

    CHIP_Init();

    RTCC_Init(&rtcc_init);
    RTCC_StatusClear();

    CMU_IntEnable(RTCC_IRQn);

    RTCC_Enable(true);


    for(;;)
    {
        EMU_EnterEM1();
    }

}



