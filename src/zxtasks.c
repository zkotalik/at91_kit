/* application includes. */
#include "zxtasks.h"
#include "led.h"

/***********************************************************************
 *
 * Function:    vTask1
 *
 * Description: FRTOS task working with green led
 *
 * Notes:
 *
 * Returns:     None
 *
 **********************************************************************/
void vTask1( void *pvParameters )
{

   /* Infinited loop */
    for(;;)
    {
        ledToggle(GREEN_LED);
        delay_ms(500);
    }
}

/***********************************************************************
 *
 * Function:    vTask2
 *
 * Description: FRTOS task working with yellow led
 *
 * Notes:
 *
 * Returns:     None
 *
 **********************************************************************/
void vTask2( void *pvParameters )
{

        /* Infinited loop */
    for(;;)
    {
        ledToggle(YELLOW_LED);
        delay_ms(800);
    }
}

/***********************************************************************
 *
 * Function:    vTask3
 *
 * Description: FRTOS task working with red led
 *
 * Notes:
 *
 * Returns:     None
 *
 **********************************************************************/
void vTask3( void *pvParameters )
{

   /* Infinited loop */
    for(;;)
    {
        ledToggle(RED_LED);
        delay_ms(1200);
    }
}
