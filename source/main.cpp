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
#include "em_rtc.h"
#include "em_i2c.h"

static uint64_t g_ticks = 0;

/**************************************************************************//**
 * @brief Delays number of msTick Systicks (typically 1 ms)
 * @param dlyTicks Number of ticks to delay
 *****************************************************************************/
void TIMER0_IRQHandler()
{
    g_ticks ++;

    if(g_ticks % 1000 == 0)
    {
        GPIO_PinOutToggle(LED_PORT, LED_PIN);
    }
}

/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{
    I2C_Init_TypeDef t2c_init = I2C_INIT_DEFAULT;

    I2C_Init()

    CHIP_Init();

    /* Initialize LED driver */
    GPIO_PinModeSet(LED_PORT, LED_PIN, gpioModePushPull, 0);
    GPIO_PinOutSet(LED_PORT, LED_PIN);

    CMU_IntClear(~0);
    CMU_IntEnable(TIMER1_IRQn);
    CMU_ClockEnable(cmuClock_TIMER1, true);


    for(;;)
    {
        EMU_EnterEM1();
    }

}



