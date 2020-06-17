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

static uint64_t g_ticks = 0;

/**************************************************************************//**
 * @brief Delays number of msTick Systicks (typically 1 ms)
 * @param dlyTicks Number of ticks to delay
 *****************************************************************************/
void SysTick_Handler()
{
    g_ticks++;

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
    CHIP_Init();

    CMU_ClockEnable(cmuClock_GPIO, true);

    /* Setup SysTick Timer for 1 msec interrupts  */
    if (SysTick_Config(CMU_ClockFreqGet(cmuClock_CORE) / 1000)) while (1) ;

    /* Initialize LED driver */
    GPIO_PinModeSet(LED_PORT, LED_PIN, gpioModePushPull, 0);

    GPIO_PinOutSet(LED_PORT, LED_PIN);


    for(;;)
    {
        EMU_EnterEM1();
    }

}



