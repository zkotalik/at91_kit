#include <led.h>
#include <AT91RM9200.h>

#define CYCLES_PER_MS   (1500)

/***********************************************************************
 *
 * Function: ledInit
 *
 * Description: Initialize GPIO pin that controls LED
 *
 * Notes: Function specific to AT91RM9200-EK board
 *
 * Returns: None
 *
 **********************************************************************/
void ledInit(void)
{

    /* Clock on PIOA and PIOB */
    *AT91C_PMC_PCER = (1 << AT91C_ID_PIOA) | (1 << AT91C_ID_PIOB);

    /* Turn pin voltage off, maybe this should be done before
     * pins are configured */
    *AT91C_PIOA_CODR = YELLOW_LED | RED_LED;
    *AT91C_PIOB_CODR = GREEN_LED;
    /* Enable PIO */
    *AT91C_PIOA_PER = YELLOW_LED | RED_LED;
    *AT91C_PIOB_PER = GREEN_LED;
    /* Enable output */
    *AT91C_PIOA_OER = YELLOW_LED | RED_LED;
    *AT91C_PIOB_OER = GREEN_LED;
}

/***********************************************************************
 *
 * Function: ledToggle
 *
 * Description: Toggle state of LED from arg.
 *
 * Notes: Function specific to AT91RM9200-EK board
 *
 * Returns: None
 *
 **********************************************************************/
void ledToggle(uint32_t leds)
{

    if(leds & YELLOW_LED)
    {
        if(*AT91C_PIOA_ODSR & YELLOW_LED)
            *AT91C_PIOA_CODR = YELLOW_LED;
        else
            *AT91C_PIOA_SODR = YELLOW_LED;
    }
    if(leds & RED_LED)
    {
        if(*AT91C_PIOA_ODSR & RED_LED)
            *AT91C_PIOA_CODR = RED_LED;
        else
            *AT91C_PIOA_SODR = RED_LED;
    }
    if(leds & GREEN_LED)
    {
        if(*AT91C_PIOB_ODSR & GREEN_LED)
            *AT91C_PIOB_CODR = GREEN_LED;
        else
            *AT91C_PIOB_SODR = GREEN_LED;
    }
}

/***********************************************************************
 *
 * Function: delay_ms
 *
 * Description: Busy-wait for requested number of ms
 *
 * Notes: Value of CYCLES_PER_MS is trial.
 *
 * Returns: None
 *
 **********************************************************************/
void delay_ms(int milliseconds)
{
    long volatile cycles = milliseconds * CYCLES_PER_MS;

    while(cycles--);
}

/***********************************************************************
 *
 * Function:    ledOn
 *
 * Description: Switch on selected leds.
 *
 * Notes:
 *
 * Returns:     None
 *
 **********************************************************************/
void ledOn(uint32_t leds)
{

    *AT91C_PIOA_CODR = leds & (YELLOW_LED | RED_LED);
    *AT91C_PIOB_CODR = leds & GREEN_LED;
}

/***********************************************************************
 *
 * Function:    ledOff
 *
 * Description: Switch off selected leds.
 *
 * Notes:
 *
 * Returns:     None
 *
 **********************************************************************/
void ledOff(uint32_t leds)
{

    *AT91C_PIOA_SODR = leds & (YELLOW_LED | RED_LED);
    *AT91C_PIOB_SODR = leds & GREEN_LED;
}
